// GameWindow.h
#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QWidget>
#include <QTimer>

class GameWindow : public QWidget {
    Q_OBJECT

public:
    explicit GameWindow(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

private:
    int ballX;
    int ballY;
    int ballSpeedX;
    int ballSpeedY;
    int player1Y;
    int player2Y;
    int playerSpeed;
    int player1Score;
    int player2Score;
    int maxScore;
    bool gameStarted;
    QTimer* gameTimer;


    void resetGame();
    void updateGame();
    void checkCollisions();
    void drawGame(QPainter& painter);

private slots:
    void onGameTimer();
};

#endif // GAMEWINDOW_H


