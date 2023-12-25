// bomb.h
#ifndef BOMB_H
#define BOMB_H

#include <QGraphicsPixmapItem>
#include <QObject>

class Player;
class MainWindow;

class Bomb : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Bomb(Player* owner, MainWindow* );  // Pass the owner player and MainWindow to the Bomb constructor
    ~Bomb();

public slots:
    void explode();

private:
    int explosionRadius;
    Player* ownerPlayer;
    MainWindow* mainWindow;  // Reference to the MainWindow
    void handleExplosionDirection(int cellX, int cellY, int dx, int dy);
    void handleExplosionCell(int cellX, int cellY);
    bool canContinueExplosion(int cellX, int cellY);
    bool exploded;
};

#endif // BOMB_H
