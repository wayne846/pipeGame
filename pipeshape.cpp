#include "pipeshape.h"
#include "mainwindow.h"
#include "gamemanager.h"
#include <QTransform>
#include <QDebug>

QSoundEffect* PipeShape::soundEffect = new QSoundEffect;

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

    //set sound, actully it just need once
    soundEffect->setSource(window->CLICK_SOUND_WAV);
    soundEffect->setVolume(0.5);

}

void PipeShape::clicked(){
    if(type == 4) return;
    if(window->isfinish) return;
    soundEffect->stop();
    soundEffect->play();
    rotate();
}

void PipeShape::rotate(){
    targetDir = (int)(rotation() + 90) % 360;
    if(!timer->isActive()){
        timer->start(10);
    }else{
        timer->setInterval(10);
    }
}

void PipeShape::rotateAnimation(){
    this->setRotation((int)(rotation() + 10) % 360);
    if(abs((int)rotation() - targetDir) < 3 ){
        timer->stop();
        rotateAnimationEnd();
    }
}

void PipeShape::rotateAnimationEnd(){
    window->gameManager->getPipe(x, y)->rotate();
    window->update();
}

void PipeShape::setWater(bool b){
    if(hasWater == b) return;
    hasWater = b;
    int waterNum = hasWater ? 1 : 0;
    this->setPixmap(window->images[type][waterNum]->scaled(QSize(window->squareWidth, window->squareWidth)));
}

void PipeShape::setDir(int d){
    d = d % 4;
    if(dir == d) return;
    dir = d;
    this->setRotation(dir * 90);
}

void PipeShape::mousePressEvent(QGraphicsSceneMouseEvent *event){
    clicked();
}
