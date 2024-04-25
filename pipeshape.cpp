/***********************************************************************
 * File: pipeshape.cpp
 * Author: B112150536 B11215058
 * Create Date: 2024/04/24
 * Editor: B11215036
 * Update Date: 2024/04/25
 * Description: display pipe on the screen
***********************************************************************/

#include "pipeshape.h"
#include "mainwindow.h"
#include "gamemanager.h"
#include "soundmanager.h"
#include <QTransform>
#include <QDebug>

//Intent: constructor
//Pre: basic information
//Post: initialize images and set the ui
PipeShape::PipeShape(int type, int dir, int x, int y, MainWindow *window)
{
    //set variable
    this->type = type;
    this->x = x;
    this->y = y;
    this->hasWater = false;
    this->window = window;

    //set image
    this->setPixmap(window->images[type][0]->scaled(QSize(window->squareWidth, window->squareWidth)));
    this->setPos(window->squareWidth*(x + 1), window->squareWidth*y);
    this->setTransformOriginPoint(window->squareWidth / 2.0, window->squareWidth / 2.0);
    this->setRotation(dir * 90);
    window->scene->addItem(this);

    //set timer
    timer = new QTimer(this);
    //it new syntax to me, I have totally no idea way it works
    QObject::connect(timer, &QTimer::timeout, this, &PipeShape::rotateAnimation);
}

//Intent: behavior when clicked
//Pre: nothing
//Post: rotate 90 degree, play sound
void PipeShape::clicked(){
    if(type == 4) return;
    if(window->isfinish) return;
    SoundManager::getInstance()->playClick();
    rotate();
}

//Intent: rotate 90 degree clockwise
//Pre: nothing
//Post: rotate animation start
void PipeShape::rotate(){
    targetDir = (int)(rotation() + 90) % 360;
    if(!timer->isActive()){
        timer->start(10);
    }else{
        timer->setInterval(10);
    }
}

//Intent: rotate animation
//Pre: start when rotate
//Post: rotate 10 degree every 10ms, when animation end, call rotateAnimationEnd
void PipeShape::rotateAnimation(){
    this->setRotation((int)(rotation() + 10) % 360);
    if(abs((int)rotation() - targetDir) < 3 ){
        timer->stop();
        rotateAnimationEnd();
    }
}

//Intent: called by rotateAnimation() when animation end
//Pre: rotate animation end
//Post: rotate the correspond pipe in GameManager::map, call MainWindow::update
void PipeShape::rotateAnimationEnd(){
    window->gameManager->getPipe(x, y)->rotate();
    window->update();
}

//Intent: set water
//Pre: bool
//Post: set water by bool b, set image
void PipeShape::setWater(bool b){
    if(hasWater == b) return;
    hasWater = b;
    int waterNum = hasWater ? 1 : 0;
    this->setPixmap(window->images[type][waterNum]->scaled(QSize(window->squareWidth, window->squareWidth)));
}

//Intent: set dir
//Pre: int
//Post: set dir to int d
void PipeShape::setDir(int d){
    d = d % 4;
    if(dir == d) return;
    dir = d;
    this->setRotation(dir * 90);
}

//Intent: mouse event
//Pre: be clicked
//Post: call clicked
void PipeShape::mousePressEvent(QGraphicsSceneMouseEvent *event){
    clicked();
}
