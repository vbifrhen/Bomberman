// player.h

#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsPixmapItem>
#include <QObject>

class Player : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Player(int playerNumber);

    int getPlayerNumber() const;
    int getExplosionRadius() const;

    bool canPlaceBomb() const;
    void increaseBombCount();
    void decreaseBombCount();

    void activateBombPowerUp();
    void activateExplosionPowerUp();

    ~Player();

private:
    int bombCount;
    int explosionRadius;
    int playerNumber;
};

#endif // PLAYER_H
