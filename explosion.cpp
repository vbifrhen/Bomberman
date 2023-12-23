// explosion.cpp
#include "explosion.h"
#include "qgraphicsscene.h"

Explosion::Explosion()
{
    setPixmap(QPixmap(":/img/fire.png"));

    // Initialize the extinguish timer
    extinguishTimer = new QTimer(this);

    // Connect the timer to the extinguish slot
    connect(extinguishTimer, &QTimer::timeout, this, &Explosion::extinguish);

    // Set the duration of the fire in milliseconds (e.g., 1000 ms for 1 second)
    extinguishTimer->start(500);
}

Explosion::~Explosion()
{
    // Implement the destructor if necessary
    // ...
}

void Explosion::extinguish()
{
    // Stop the timer
    extinguishTimer->stop();

    // Remove the explosion/fire
    scene()->removeItem(this);
    delete this;
}
