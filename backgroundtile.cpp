#include "backgroundtile.h"
#include "mainwindow.h"
#include "pipeshape.h"

BackgroundTile::BackgroundTile(int x, int y, bool isDefaultPath, MainWindow *window)
{
    this->x = x;
    this->y = y;
    this->isDefaultPath = isDefaultPath;
    this->window = window;
    this->isActive = true;

    //set rectangle
    this->setRect(window->squareWidth * (x + 1), window->squareWidth * y, window->squareWidth, window->squareWidth);
    if(isDefaultPath){
        normal_color = window->TILE_PATH_COLOR;
    }else{
        normal_color = window->TILE_DEFAULT_COLOR;
    }
    this->setBrush(normal_color);
    this->setPen(normal_color);
    this->setAcceptHoverEvents(true);
    this->setZValue(-1);

    window->scene->addItem(this);
}

void BackgroundTile::setIsActive(bool b){
    isActive = b;
    this->setAcceptHoverEvents(isActive);
    this->setBrush(normal_color);
    this->setPen(normal_color);
}

void BackgroundTile::mousePressEvent(QGraphicsSceneMouseEvent *event){
    if(!isActive) return;
    window->pipeShapes[y][x]->clicked();
}
void BackgroundTile::hoverEnterEvent(QGraphicsSceneHoverEvent *event){
    if(window->isfinish){
        setIsActive(false);
        return;
    }

    this->setBrush(window->TILE_HOVER_COLOR);
    this->setPen(window->TILE_HOVER_COLOR);
}
void BackgroundTile::hoverLeaveEvent(QGraphicsSceneHoverEvent *event){
    if(window->isfinish){
        setIsActive(false);
        return;
    }

    this->setBrush(normal_color);
    this->setPen(normal_color);
}
