/***********************************************************************
 * File: backgroundtile.h
 * Author: B112150536 B11215058
 * Create Date: 2024/04/24
 * Editor: B11215036
 * Update Date: 2024/04/25
 * Description: display background
***********************************************************************/

#ifndef BACKGROUNDTILE_H
#define BACKGROUNDTILE_H

#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSceneEvent>
#include <QHoverEvent>

class MainWindow;

class BackgroundTile : public QGraphicsRectItem
{
    private:
        // information of the tile
        int x;
        int y;
        bool isDefaultPath;
        bool isActive; //if the tile is active, it can be clicked

        MainWindow *window;

        QColor normal_color;

    protected:
        //mouse event
        void mousePressEvent(QGraphicsSceneMouseEvent *event);
        void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
        void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

    public:
        //constructor
        BackgroundTile(int x, int y, bool isDefaultPath, MainWindow *window);

        //set active or not
        void setIsActive(bool b);
};

#endif // BACKGROUNDTILE_H
