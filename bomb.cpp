// bomb.cpp
#include "bomb.h"
#include <QPixmap>
#include <QTimer>
#include "explosion.h"
#include "block.h"
#include "field.h"
#include "player.h"
#include "mainwindow.h"

Bomb::Bomb(Player* owner, MainWindow* mainWindow) : explosionRadius(50), ownerPlayer(owner), mainWindow(mainWindow)
{
    setPixmap(QPixmap(":/img/bomb.png"));

    QTimer* timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(explode()));
    timer->start(2000);
}

Bomb::~Bomb() {}

void Bomb::explode()
{
    // ... (same explosion logic)

    for (int dx = -explosionRadius; dx <= explosionRadius; dx += 50) {
        for (int dy = -explosionRadius; dy <= explosionRadius; dy += 50) {
            if (dx != 0 && dy != 0) {
                continue;
            }

            int cellX = x() + dx;
            int cellY = y() + dy;

            // Detect and handle collisions with blocks
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
    }

    // Reset the owner player's parameters after bomb explosion
    ownerPlayer->setHasBomb(false);
    ownerPlayer->setCanPlaceBomb(true);

    scene()->removeItem(this);
    delete this;
}
