#include "Gamewindow.h"
#include <QPainter>
#include <QKeyEvent>

GameWindow::GameWindow(QWidget *parent) : QWidget(parent) {
    ballX = width() / 2;
    ballY = height() / 2;
    ballSpeedX = 5;
    ballSpeedY = 3;
    player1Y = height() / 2;
    player2Y = height() / 2;
    playerSpeed = 15;
    player1Score = 0;
    player2Score = 0;
    maxScore = 5;
    gameStarted = false;

    gameTimer = new QTimer(this);
    connect(gameTimer, &QTimer::timeout, this, &GameWindow::onGameTimer);
    gameTimer->start(16);
    resetGame();
}

void GameWindow::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    QPainter painter(this);
    drawGame(painter);
}

void GameWindow::keyPressEvent(QKeyEvent *event) {
    if (!gameStarted) {
        if (event->key() == Qt::Key_Space) {
            gameStarted = true;
        }
        return;
    }

    if (event->key() == Qt::Key_W) {
        player1Y -= playerSpeed;
    } else if (event->key() == Qt::Key_S) {
        player1Y += playerSpeed;
    } else if (event->key() == Qt::Key_Up) {
        player2Y -= playerSpeed;
    } else if (event->key() == Qt::Key_Down) {
        player2Y += playerSpeed;
    }
    update();
}

void GameWindow::onGameTimer() {
    if (!gameStarted) {
        return;
    }
    ballX += ballSpeedX;
    ballY += ballSpeedY;
    checkCollisions();
    update();
}

void GameWindow::resetGame() {
    ballX = width() / 2;
    ballY = height() / 2;
    player1Y = height() / 2;
    player2Y = height() / 2;
    player1Score = 0;
    player2Score = 0;
    gameStarted = false;
}

void GameWindow::updateGame() {

    if (player1Score >= maxScore || player2Score >= maxScore) {
        gameStarted = false;
    }
}

void GameWindow::checkCollisions() {

    if (ballY <= 0 || ballY >= height()) {
        ballSpeedY *= -1;
    }

    if (ballX <= 0) {
        player2Score++;
        resetGame();
    } else if (ballX >= width()) {
        player1Score++;
        resetGame();
    }

    if (ballX <= 20 && abs(ballY - player1Y) < 50) {
        ballSpeedX *= -1;
    } else if (ballX >= width() - 20 && abs(ballY - player2Y) < 50) {
        ballSpeedX *= -1;
    }
}

void GameWindow::drawGame(QPainter& painter) {
    painter.setBrush(Qt::black);
    painter.drawRect(0, 0, width(), height());

    painter.setBrush(Qt::white);
    painter.drawRect(10, player1Y - 50, 10, 100);
    painter.drawRect(width() - 20, player2Y - 50, 10, 100);

    painter.drawEllipse(QPoint(ballX, ballY), 10, 10);

    QFont font;
    font.setPointSize(20);
    painter.setFont(font);
    painter.setPen(Qt::white);

    if (!gameStarted) {
        painter.drawText(rect(), Qt::AlignCenter, "Presiona ESPACIO para comenzar");
    } else {
        painter.drawText(rect(), Qt::AlignCenter, QString("Jugador 1: %1   Jugador 2: %2").arg(player1Score).arg(player2Score));
    }
}
