// player.cpp

#include "player.h"

Player::Player(int playerNumber) : playerNumber(playerNumber), bombCount(1), explosionRadius(1)
{
    setPixmap(QPixmap(":/img/player_front.png"));
    setFlag(QGraphicsItem::ItemIsFocusable);
    setZValue(1);
}

int Player::getPlayerNumber() const
{
    return playerNumber;
}

int Player::getExplosionRadius() const
{
    return explosionRadius;
}

bool Player::canPlaceBomb() const
{
    return bombCount > 0;  // Проверка, что у игрока есть доступные бомбы
}


void Player::increaseBombCount()
{
    bombCount++;
}

void Player::decreaseBombCount()
{
    bombCount = qMax(0, bombCount - 1);
}

void Player::activateBombPowerUp()
{
    increaseBombCount();  // Увеличение количества бомб
}

void Player::activateExplosionPowerUp()
{
    explosionRadius++;
}

Player::~Player() {}
