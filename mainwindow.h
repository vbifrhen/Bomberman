#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QTimer>
#include "gameoveroverlay.h"
#include "player.h"
#include <QGraphicsProxyWidget>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void keyPressEvent(QKeyEvent *event);
    bool canMove(QGraphicsItem *item, int dx, int dy);
    void destroyPlayer(Player* player);
    void updateTimer();

private slots:
    void addUnbreakableBlock();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    Player *player1;
    Player *player2;
    int minX;
    int minY;
    int maxX;
    int maxY;
    void createMap();
    QTimer *gameTimer;
    GameOverOverlay *gameOverOverlay;
    QGraphicsProxyWidget* overlayProxy;
    QPoint currentFillPosition;
    void fillUnbreakableBlocks();
    void checkBlock(int minY,int minX);
    int indicator = 0;
    int colNow = 1;
    int rowNow = 1;
    QTimer* fillTimer;
    void checkPowerUpCollision(Player *player);


};
#endif // MAINWINDOW_H
