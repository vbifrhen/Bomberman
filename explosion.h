// explosion.h
#ifndef EXPLOSION_H
#define EXPLOSION_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QTimer>

class Explosion : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    Explosion();
    ~Explosion();

private slots:
    void extinguish();  // Slot to handle fire extinguishing

private:
    QTimer* extinguishTimer;  // Timer to control fire duration
};

#endif // EXPLOSION_H
