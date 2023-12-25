// powerup.h
#ifndef POWERUP_H
#define POWERUP_H

#include <QGraphicsItem>

class PowerUp : public QGraphicsPixmapItem
{
public:
    PowerUp(std::string factor);
    std::string whichFactor() const;
private:
    std::string factorP; // Add a member variable to store the factor of PowerUp property
};
#endif // POWERUP_H
