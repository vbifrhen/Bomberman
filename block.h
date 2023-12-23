// block.h
#ifndef BLOCK_H
#define BLOCK_H

#include <QGraphicsPixmapItem>

class Block : public QGraphicsPixmapItem
{
public:
    Block(bool breakable); // Pass true for breakable, false for unbreakable
    bool isBreakable() const;
private:
    bool breakablebl; // Add a member variable to store the breakable property
};
#endif // BLOCK_H
