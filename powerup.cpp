// powerup.cpp
#include "powerup.h"

PowerUp::PowerUp(std::string factor)
{
    if (factor == "bomb") {
        factorP = "bomb";
        setPixmap(QPixmap(":/img/bombPowerUp.png"));
    } else {
        factorP = "explosion";
        setPixmap(QPixmap(":/img/explosionPowerUp.png"));
    }
    setZValue(1);
}


std::string PowerUp::whichFactor() const
{
    return factorP;
}
