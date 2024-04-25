/***********************************************************************
 * File: backgroundtile.cpp
 * Author: B112150536 B11215058
 * Create Date: 2024/04/24
 * Editor: B11215036
 * Update Date: 2024/04/25
 * Description: display background
***********************************************************************/

#include "backgroundtile.h"
#include "mainwindow.h"
#include "pipeshape.h"

//Intent: constructor
//Pre: basic information
//Post: initialize images and set the ui
BackgroundTile::BackgroundTile(int x, int y, bool isDefaultPath, MainWindow *window)
{
    //set variable
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

//Intent: set active or not
//Pre: b is bool
//Post: set isActive to b, set acceptHoverEvents to b, set color to normal_color
void BackgroundTile::setIsActive(bool b){
    isActive = b;
    this->setAcceptHoverEvents(isActive);

    //set color
    this->setBrush(normal_color);
    this->setPen(normal_color);
}

//Intent: behavior when clicked
//Pre: be clicked
//Post: call corresponding pipeShape::clicked
void BackgroundTile::mousePressEvent(QGraphicsSceneMouseEvent *event){
    if(!isActive) return;
    window->pipeShapes[y][x]->clicked();
}

//Intent: behavior when hover
//Pre: be hover
//Post: set color to TILE_HOVER_COLOR if not finish
void BackgroundTile::hoverEnterEvent(QGraphicsSceneHoverEvent *event){
    if(window->isfinish){
        setIsActive(false);
        return;
    }

    //set color
    this->setBrush(window->TILE_HOVER_COLOR);
    this->setPen(window->TILE_HOVER_COLOR);
}

//Intent: behavior when not hover
//Pre: be not hover
//Post: set color to normal_color if not finish
void BackgroundTile::hoverLeaveEvent(QGraphicsSceneHoverEvent *event){
    if(window->isfinish){
        setIsActive(false);
        return;
    }

    //set color
    this->setBrush(normal_color);
    this->setPen(normal_color);
}
