// gameoveroverlay.cpp

#include "gameoveroverlay.h"

GameOverOverlay::GameOverOverlay(QWidget *parent)
    : QWidget(parent)
{
    setAttribute(Qt::WA_TransparentForMouseEvents);
    setStyleSheet("background-color: rgba(0, 0, 0, 150);"); // Semi-transparent black background

    messageLabel = new QLabel(this);
    messageLabel->setStyleSheet("color: white; font-size: 24px;");

    layout = new QVBoxLayout(this);
    layout->addWidget(messageLabel);
    layout->setAlignment(Qt::AlignCenter);
}

void GameOverOverlay::setWinnerMessage(const QString &message)
{
    messageLabel->setText(message);
}
