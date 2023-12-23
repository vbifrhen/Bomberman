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

    bool hasBomb() const;
    void setHasBomb(bool value);

    bool canPlaceBomb() const;
    void setCanPlaceBomb(bool value);

    int getPlayerNumber() const;  // Add this function declaration

    ~Player();

private:
    bool hasBomb_;
    bool canPlaceBomb_;
    int playerNumber;
};

#endif // PLAYER_H
