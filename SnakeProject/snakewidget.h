#ifndef SNAKEWIDGET_H
#define SNAKEWIDGET_H

#include <QWidget>
#include <QKeyEvent>
#include <QTimer>
#include <QPainter>
#include <QImage>
#include <QRandomGenerator>

class SnakeWidget : public QWidget {
    Q_OBJECT

public:
    SnakeWidget(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void timerEvent(QTimerEvent *event) override;

private:
    // Игровые константы
    static const int DOT_WIDTH = 10;
    static const int FIELD_WIDTH = 600;
    static const int FIELD_HEIGHT = 600;
    
    // Игровые переменные
    int timerId;
    QImage dot;
    QImage head;
    QImage apple;
    
    // Состояние игры
    QVector<QPoint> snake;
    QPoint applePos;
    int xDir, yDir;
    bool inGame;
    
    void loadImages();
    void initGame();
    void locateApple();
    void move();
    void checkCollision();
    void gameOver(QPainter &painter);
};

#endif
