// bomb.cpp
#include "bomb.h"
#include <QPixmap>
#include <QTimer>
#include "explosion.h"
#include "block.h"
#include "field.h"
#include "player.h"
#include "mainwindow.h"

Bomb::Bomb(Player* owner, MainWindow* mainWindow) : explosionRadius(50), ownerPlayer(owner), mainWindow(mainWindow), exploded(false)
{
    setPixmap(QPixmap(":/img/bomb.png"));

    QTimer* timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(explode()));
    timer->start(2000);
}

Bomb::~Bomb() {}

void Bomb::explode()
{
    if (exploded) {
        return; // Already exploded, do nothing
    }

    exploded = true;
    handleExplosionCell(x(), y());  // Первая ячейка взрыва в центре бомбы
    handleExplosionDirection(x(), y(), 1, 0);
    handleExplosionDirection(x(), y(), -1, 0);
    handleExplosionDirection(x(), y(), 0, 1);
    handleExplosionDirection(x(), y(), 0, -1);

    ownerPlayer->increaseBombCount();
    scene()->removeItem(this);
    delete this;
}

void Bomb::handleExplosionCell(int cellX, int cellY) {
    QList<QGraphicsItem*> items = scene()->items(QRectF(cellX, cellY, 50, 50));
    for (QGraphicsItem* item : items) {
        if (Block* block = dynamic_cast<Block*>(item)) {
            if (block->isBreakable()) {
                scene()->removeItem(block);
                Field *field = new Field();
                field->setPos(cellX, cellY);
                scene()->addItem(field);
                Explosion* explosion = new Explosion();
                explosion->setPos(cellX, cellY);
                scene()->addItem(explosion);
                delete block;
            }
        }
        else if(Field* field = dynamic_cast<Field*>(item)) {
            Explosion* explosion = new Explosion();
            explosion->setPos(cellX, cellY);
            scene()->addItem(explosion);
        }
    }
    // Detect and handle collisions with players
    QList<QGraphicsItem*> players = scene()->items(QRectF(cellX, cellY, 50, 50), Qt::IntersectsItemBoundingRect);
    for (QGraphicsItem* playerItem : players) {
        if (Player* player = dynamic_cast<Player*>(playerItem)) {
            mainWindow->destroyPlayer(player);
        }
    }
}



void Bomb::handleExplosionDirection(int cellX, int cellY, int dx, int dy)
{
    int factor = ownerPlayer->getExplosionRadius();
    for (int distance = 1; distance <= factor; ++distance) {
        int currentCellX = cellX + dx * distance * explosionRadius;
        int currentCellY = cellY + dy * distance * explosionRadius;

        // Проверка, может ли взрыв продолжаться в данной ячейке
        if (!canContinueExplosion(currentCellX, currentCellY)) {
            break;
        }

        handleExplosionCell(currentCellX, currentCellY);
    }
}

bool Bomb::canContinueExplosion(int cellX, int cellY)
{
    // Проверка, может ли взрыв продолжаться в данной ячейке
    // Возвращает true, если взрыв может продолжаться, и false, если нужно остановиться
    QList<QGraphicsItem*> items = scene()->items(QRectF(cellX, cellY, 50, 50));
    for (QGraphicsItem* item : items) {
        if (Block* block = dynamic_cast<Block*>(item)) {
            if (!block->isBreakable()) {
                return false;
            }
        }
        else if (Bomb* bomb = dynamic_cast<Bomb*>(item)) {
            if (!bomb->exploded) {
                bomb->explode();
            }
            return false;
        }
    }
    return true;
}

