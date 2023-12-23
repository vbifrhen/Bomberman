// gameoveroverlay.h

#ifndef GAMEOVEROVERLAY_H
#define GAMEOVEROVERLAY_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>

class GameOverOverlay : public QWidget
{
    Q_OBJECT

public:
    explicit GameOverOverlay(QWidget *parent = nullptr);
    void setWinnerMessage(const QString &message);

private:
    QLabel *messageLabel;
    QVBoxLayout *layout;
};

#endif // GAMEOVEROVERLAY_H
