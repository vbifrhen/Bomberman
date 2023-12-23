// player.cpp

#include "player.h"

Player::Player(int playerNumber) : playerNumber(playerNumber), hasBomb_(false), canPlaceBomb_(true)
{
    setPixmap(QPixmap(":/img/player_front.png"));
    setFlag(QGraphicsItem::ItemIsFocusable);
}

int Player::getPlayerNumber() const
{
    return playerNumber;
}

bool Player::hasBomb() const
{
    return hasBomb_;
}

void Player::setHasBomb(bool value)
{
    hasBomb_ = value;
}

bool Player::canPlaceBomb() const
{
    return canPlaceBomb_;
}

void Player::setCanPlaceBomb(bool value)
{
    canPlaceBomb_ = value;
}

Player::~Player() {}
