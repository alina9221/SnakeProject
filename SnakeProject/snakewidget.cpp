#include "snakewidget.h"
#include <QDir>
#include <QApplication>

SnakeWidget::SnakeWidget(QWidget *parent) : QWidget(parent) {
    setFixedSize(FIELD_WIDTH, FIELD_HEIGHT);
    setStyleSheet("background-color: black;");
    
    loadImages();
    initGame();
}

void SnakeWidget::loadImages() {
    // Загрузка изображений (создайте эти файлы в папке images)
    QString binDir = QApplication::applicationDirPath();
    QString imgPath = binDir + "/images/";
    
    dot.load(imgPath + "dot.png");
    head.load(imgPath + "head.png"); 
    apple.load(imgPath + "apple.png");
    
    // Масштабирование до нужного размера
    dot = dot.scaled(DOT_WIDTH, DOT_WIDTH);
    head = head.scaled(DOT_WIDTH, DOT_WIDTH);
    apple = apple.scaled(DOT_WIDTH, DOT_WIDTH);
}

void SnakeWidget::initGame() {
    inGame = true;
    xDir = DOT_WIDTH;  // Начальное движение вправо
    yDir = 0;
    
    // Создание начальной змейки из 3 сегментов
    snake.clear();
    for (int i = 0; i < 3; ++i) {
        snake.append(QPoint(100 - i * DOT_WIDTH, 100));
    }
    
    locateApple();
    timerId = startTimer(100);  // Таймер на 100 мс
}

void SnakeWidget::locateApple() {
    // Случайное размещение яблока
    int x = QRandomGenerator::global()->bounded(FIELD_WIDTH / DOT_WIDTH) * DOT_WIDTH;
    int y = QRandomGenerator::global()->bounded(FIELD_HEIGHT / DOT_WIDTH) * DOT_WIDTH;
    applePos = QPoint(x, y);
}

void SnakeWidget::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    QPainter painter(this);
    
    if (inGame) {
        // Отрисовка яблока
        painter.drawImage(applePos, apple);
        
        // Отрисовка змейки
        for (int i = 0; i < snake.size(); ++i) {
            if (i == 0) {
                painter.drawImage(snake[i], head);  // Голова
            } else {
                painter.drawImage(snake[i], dot);   // Тело
            }
        }
    } else {
        gameOver(painter);
    }
}

void SnakeWidget::keyPressEvent(QKeyEvent *event) {
    int key = event->key();
    
    if (key == Qt::Key_Left && xDir == 0) {
        xDir = -DOT_WIDTH;
        yDir = 0;
    } else if (key == Qt::Key_Right && xDir == 0) {
        xDir = DOT_WIDTH;
        yDir = 0;
    } else if (key == Qt::Key_Up && yDir == 0) {
        xDir = 0;
        yDir = -DOT_WIDTH;
    } else if (key == Qt::Key_Down && yDir == 0) {
        xDir = 0;
        yDir = DOT_WIDTH;
    }
}

void SnakeWidget::timerEvent(QTimerEvent *event) {
    Q_UNUSED(event);
    
    if (inGame) {
        checkCollision();
        move();
    }
    repaint();
}

void SnakeWidget::move() {
    // Перемещение тела змейки
    for (int i = snake.size() - 1; i > 0; --i) {
        snake[i] = snake[i - 1];
    }
    
    // Перемещение головы
    snake[0].rx() += xDir;
    snake[0].ry() += yDir;
    
    // Проверка съедания яблока
    if (snake[0] == applePos) {
        snake.append(snake.last());  // Увеличение змейки
        locateApple();
    }
}

void SnakeWidget::checkCollision() {
    // Столкновение со стенами
    if (snake[0].x() >= FIELD_WIDTH || snake[0].x() < 0 ||
        snake[0].y() >= FIELD_HEIGHT || snake[0].y() < 0) {
        inGame = false;
    }
    
    // Столкновение с собой
    for (int i = 1; i < snake.size(); ++i) {
        if (snake[0] == snake[i]) {
            inGame = false;
            break;
        }
    }
    
    if (!inGame) {
        killTimer(timerId);
    }
}

void SnakeWidget::gameOver(QPainter &painter) {
    QString message = "Game Over";
    QFont font("Courier", 15, QFont::DemiBold);
    QFontMetrics fm(font);
    
    painter.setPen(Qt::white);
    painter.setFont(font);
    painter.drawText((width() - fm.horizontalAdvance(message)) / 2, 
                     height() / 2, message);
}
