#include "pipeshape.h"
#include "mainwindow.h"
#include "gamemanager.h"
#include <QTransform>

PipeShape::PipeShape(int type, int dir, int x, int y, MainWindow *window)
{
    this->type = type;
    this->x = x;
    this->y = y;
    this->hasWater = false;

    this->window = window;
    this->setPixmap(window->images[type][0]->scaled(QSize(window->squareWidth, window->squareWidth)));
    this->setPos(window->squareWidth*(x + 1), window->squareWidth*y);
    this->setTransformOriginPoint(window->squareWidth / 2.0, window->squareWidth / 2.0);
    this->setRotation(dir * 90);
    window->scene->addItem(this);
}

void PipeShape::rotate(){
    this->setRotation((int)(rotation() + 90) % 360);
}

void PipeShape::setWater(bool b){
    if(hasWater == b) return;
    hasWater = b;
    int waterNum = hasWater ? 1 : 0;
    this->setPixmap(window->images[type][waterNum]->scaled(QSize(window->squareWidth, window->squareWidth)));
}

void PipeShape::clicked(){
    if(type == 4) return;
    rotate();
    window->gameManager->getPipe(x, y)->rotate();
    window->update();
}

void PipeShape::mousePressEvent(QGraphicsSceneMouseEvent *event){
    clicked();
}
