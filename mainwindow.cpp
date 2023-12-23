    #include <QMainWindow>
    #include <QGraphicsScene>
    #include <QKeyEvent>  // For handling key events
    #include <QGraphicsItem>
    #include <QList>

    // Include other necessary headers for your project

    #include "field.h"
    #include "bomb.h"
    #include "block.h"

    #include "mainwindow.h"
    #include "./ui_mainwindow.h"

    MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent)
        , ui(new Ui::MainWindow)
    {
        ui->setupUi(this);
        ui->textEdit->hide();
        ui->label->hide();

        // Create a QGraphicsScene
        scene = new QGraphicsScene(this);

        // Set the scene to the QGraphicsView
        ui->graphicsView->setScene(scene);
        minX = 0;
        minY = 0;
        maxX = 750;
        maxY = 800;
        ui->graphicsView->setSceneRect(0, 0, maxX, maxY);

        // Create the map
        createMap();

        // Create players and add them to the scene
        player1 = new Player(1);
        player1->setPos(50, 50);
        scene->addItem(player1);

        player2 = new Player(2);
        player2->setPos(maxX - player2->boundingRect().width() - 100, maxY - player2->boundingRect().height() - 100);
        scene->addItem(player2);
        gameTimer = new QTimer(this);
        connect(gameTimer, &QTimer::timeout, this, &MainWindow::updateTimer);
        gameTimer->start(1000);  // Update every 1000 milliseconds (1 second)
        // Set the focus policy for the QGraphicsView
        ui->graphicsView->setFocusPolicy(Qt::StrongFocus);
        ui->graphicsView->setFocus(); // This line was added to set focus initially
    }


    void MainWindow::updateTimer()
    {
        static int remainingTimeInSeconds = 5 * 2;  // 5 minutes

        if (remainingTimeInSeconds > 0) {
            remainingTimeInSeconds--;

            int minutes = remainingTimeInSeconds / 60;
            int seconds = remainingTimeInSeconds % 60;

            ui->timerLabel->setText(QString("%1:%2").arg(minutes, 2, 10, QLatin1Char('0')).arg(seconds, 2, 10, QLatin1Char('0')));
        } else {
            // Timer has reached 0, handle the end of the game or reset the timer as needed
            // For example, you can stop the timer and display a message
            gameTimer->stop();
            ui->timerLabel->setText("Game Over!");
            fillUnbreakableBlocks();
        }
    }

    void MainWindow::fillUnbreakableBlocks()
    {
        // Use a single timer for filling unbreakable blocks
        fillTimer = new QTimer(this);
        connect(fillTimer, &QTimer::timeout, this, &MainWindow::addUnbreakableBlock);
        fillTimer->start(500);  // Add a new block every 500 milliseconds
    }

    void MainWindow::addUnbreakableBlock()
    {
        const int colStart = 1, colEnd = 14, rowEnd = 14;

        if (rowNow <= rowEnd)
        {
            if (indicator == 0)
            {
                checkBlock(rowNow, colNow);
                colNow++;
                if (colNow == colEnd + 1)
                {
                    indicator = 1;
                    rowNow++;
                    colNow = colEnd;
                }
            }
            else if (indicator == 1)
            {
                checkBlock(rowNow, colNow);
                colNow--;
                if (colNow == colStart - 1)
                {
                    indicator = 0;
                    rowNow++;
                    colNow = colStart;
                }
            }
        }
        else
        {
            // Stop the timer when the entire map is filled
            fillTimer->stop();
            delete fillTimer;
        }
    }

    void MainWindow::checkBlock(int minY, int minX) {
        qreal x = minY * 50;
        qreal y = minX * 50;

        QList<QGraphicsItem*> items = scene->items(QRectF(x, y, 1, 1), Qt::IntersectsItemBoundingRect);


            for (QGraphicsItem* item : items) {
                if (item == player1 || item == player2) {
                    // Player is at the position, destroy the player
                    destroyPlayer(dynamic_cast<Player*>(item));
                    return;  // Exit the function after destroying the player
                }
            }
            QGraphicsItem* item = scene->itemAt(x, y, QTransform());
                // Remove the existing item if it's not a field
                scene->removeItem(item);
                delete item;

                // Add an unbreakable block
                Block* block = new Block(false); // Unbreakable
                block->setPos(x, y);
                scene->addItem(block);

    }






    void MainWindow::createMap()
    {
        // Sample Bomberman game map
        char gameMap[15][15] = {
            {'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U'},
            {'U', 'O', 'O', 'O', 'B', 'B', 'B', 'B', 'B', 'B', 'B', 'O', 'O', 'O', 'U'},
            {'U', 'O', 'U', 'B', 'U', 'B', 'U', 'B', 'U', 'B', 'U', 'B', 'U', 'O', 'U'},
            {'U', 'O', 'U', 'B', 'B', 'B', 'B', 'B', 'B', 'B', 'B', 'B', 'U', 'O', 'U'},
            {'U', 'B', 'U', 'B', 'U', 'B', 'U', 'B', 'U', 'B', 'U', 'B', 'U', 'B', 'U'},
            {'U', 'B', 'B', 'B', 'B', 'B', 'B', 'B', 'B', 'B', 'B', 'B', 'B', 'B', 'U'},
            {'U', 'B', 'U', 'B', 'U', 'B', 'U', 'U', 'U', 'B', 'U', 'B', 'U', 'B', 'U'},
            {'U', 'B', 'B', 'B', 'B', 'B', 'B', 'O', 'B', 'B', 'B', 'B', 'B', 'B', 'U'},
            {'U', 'B', 'U', 'B', 'U', 'B', 'U', 'U', 'U', 'B', 'U', 'B', 'U', 'B', 'U'},
            {'U', 'B', 'B', 'B', 'B', 'B', 'B', 'B', 'B', 'B', 'B', 'B', 'B', 'B', 'U'},
            {'U', 'B', 'U', 'B', 'U', 'B', 'U', 'B', 'U', 'B', 'U', 'B', 'U', 'B', 'U'},
            {'U', 'O', 'U', 'B', 'B', 'B', 'B', 'B', 'B', 'B', 'B', 'B', 'U', 'O', 'U'},
            {'U', 'O', 'U', 'B', 'U', 'B', 'U', 'B', 'U', 'B', 'U', 'B', 'U', 'O', 'U'},
            {'U', 'O', 'O', 'O', 'B', 'B', 'B', 'B', 'B', 'B', 'B', 'O', 'O', 'O', 'U'},
            {'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U'}
        };


        // Convert the character map to QGraphicsItems and add them to the scene
        for (int i = 0; i < 15; ++i)
        {
            for (int j = 0; j < 15; ++j)
            {
                if (gameMap[i][j] == 'U')
                {
                    Block *block = new Block(false); // Unbreakable
                    block->setPos(j * 50, i * 50);  // Adjust position based on the new size
                    scene->addItem(block);
                }
                else if (gameMap[i][j] == 'B')
                {
                    Block *block = new Block(true); // Specify whether it's breakable
                    block->setPos(j * 50, i * 50);  // Adjust position based on the new size
                    scene->addItem(block);
                }
                else if (gameMap[i][j] == 'O')
                {
                    Field *field = new Field();
                    field->setPos(j * 50, i * 50);
                    scene->addItem(field);
                }
            }
        }
    }




    // Handle key press events for player movement
    void MainWindow::keyPressEvent(QKeyEvent *event)
    {
        setFocus();
        int step = 50; // Adjust the step size as needed
        switch (event->key()) {
        case Qt::Key_A:
            // Check for collisions before moving
            if (canMove(player1, -step, 0))
                player1->setPos(player1->x() - step, player1->y());
            break;
        case Qt::Key_D:
            // Check for collisions before moving
            if (canMove(player1, step, 0))
                player1->setPos(player1->x() + step, player1->y());
            break;
        case Qt::Key_W:
            // Check for collisions before moving
            if (canMove(player1, 0, -step))
                player1->setPos(player1->x(), player1->y() - step);
            break;
        case Qt::Key_S:
            // Check for collisions before moving
            if (canMove(player1, 0, step))
                player1->setPos(player1->x(), player1->y() + step);
            break;
        case Qt::Key_Left:
            // Check for collisions before moving
            if (canMove(player2, -step, 0))
                player2->setPos(player2->x() - step, player2->y());
            break;
        case Qt::Key_Right:
            // Check for collisions before moving
            if (canMove(player2, step, 0))
                player2->setPos(player2->x() + step, player2->y());
            break;
        case Qt::Key_Up:
            // Check for collisions before moving
            if (canMove(player2, 0, -step))
                player2->setPos(player2->x(), player2->y() - step);
            break;
        case Qt::Key_Down:
            // Check for collisions before moving
            if (canMove(player2, 0, step))
                player2->setPos(player2->x(), player2->y() + step);
            break;
        case Qt::Key_E:
            // Place a bomb for player1 when the space bar is pressed
            if (player1->canPlaceBomb()) {
                Bomb *bomb1 = new Bomb(player1, this);
                bomb1->setPos(player1->x(), player1->y());
                scene->addItem(bomb1);

                // Set hasBomb and canPlaceBomb to false for player1
                player1->setHasBomb(true);
                player1->setCanPlaceBomb(false);
            }
            break;
        case Qt::Key_0:
            // Place a bomb for player1 when the space bar is pressed
            if (player2->canPlaceBomb()) {
                Bomb *bomb2 = new Bomb(player2, this);
                bomb2->setPos(player2->x(), player2->y());
                scene->addItem(bomb2);

                // Set hasBomb and canPlaceBomb to false for player2
                player2->setHasBomb(true);
                player2->setCanPlaceBomb(false);
            }
            break;
        }
        player1->setZValue(1);
        player2->setZValue(1);
    }

    bool MainWindow::canMove(QGraphicsItem *item, int dx, int dy)
    {
        // Calculate the new position
        qreal newX = item->x() + dx;
        qreal newY = item->y() + dy;

        // Create a temporary item representing the new position
        QGraphicsRectItem tempItem(newX, newY, item->boundingRect().width(), item->boundingRect().height());

        // Check for collisions with walls, blocks, and bomb blocks
        QList<QGraphicsItem *> collidingItems = scene->items(tempItem.rect(), Qt::IntersectsItemBoundingRect);
        for (QGraphicsItem *collidingItem : collidingItems) {
            if (collidingItem != item && (dynamic_cast<Block*>(collidingItem)))
                return false; // Collision detected
        }

        // Check if the new position is within the game area
        if (newX < minX || newY < minY || newX > maxX || newY > maxY)
            return false;

        return true; // No collision
    }



    void MainWindow::destroyPlayer(Player* player)
    {
        /*qDebug() << "Player destroyed. Showing GameOverOverlay.";
        // In your MainWindow constructor
        gameOverOverlay = new GameOverOverlay(this);

        // Create a QGraphicsProxyWidget and set it as a proxy for the scene
        overlayProxy = scene->addWidget(gameOverOverlay);

        // Set the Z value to ensure it appears above other items in the scene
        overlayProxy->setZValue(10);

        // Set the position of the overlay to cover the entire view
        overlayProxy->setPos(ui->graphicsView->mapToScene(0, 0));

        // Set the geometry to cover the entire view
        overlayProxy->setGeometry(QRectF(0, 0, ui->graphicsView->width(), ui->graphicsView->height()));

        gameOverOverlay->setWinnerMessage(QString("Player %1 Lose!").arg(player->getPlayerNumber()));
        gameOverOverlay->show();*/

        ui->textEdit->setStyleSheet("background-color: black; color: white;");
        ui->label->setStyleSheet("color: white;");
        ui->label->setText(QString("Player %1 Wins!").arg((player == player1) ? 2 : 1));
        ui->textEdit->show();
        ui->label->show();
        scene->removeItem(player);
    }



    MainWindow::~MainWindow()
    {
        delete ui;
    }

