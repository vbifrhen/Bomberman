// block.cpp
#include "block.h"

Block::Block(bool breakable)
{
    if (breakable) {
        breakablebl = true;
        setPixmap(QPixmap(":/img/breakable_block.png"));
        setZValue(2);
    } else {
        breakablebl = false;
        setPixmap(QPixmap(":/img/unbreakable_block.png"));
    }
}


bool Block::isBreakable() const
{
    return breakablebl;
}
