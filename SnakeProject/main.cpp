#include <QApplication>
#include "snakewidget.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    
    SnakeWidget snakeGame;
    snakeGame.setWindowTitle("Snake Game");
    snakeGame.show();
    
    return app.exec();
}
