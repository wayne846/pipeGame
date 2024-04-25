/***********************************************************************
 * File: pipeshape.h
 * Author: B112150536 B11215058
 * Create Date: 2024/04/24
 * Editor: B11215036
 * Update Date: 2024/04/25
 * Description: display pipe on the screen
***********************************************************************/

#ifndef PIPESHAPE_H
#define PIPESHAPE_H

#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QObject>

class MainWindow;

class PipeShape : public QGraphicsPixmapItem, public QObject
{
    private:
        //information of the pipeShape
        //almost same like Pipe
        int type;
        int dir;
        int x;
        int y;
        bool hasWater;

        MainWindow *window;

        //for animation
        QTimer *timer;
        int targetDir; //when rotate to target dir, animation stop
        void rotateAnimationEnd(); //called by rotateAnimation() when animation end

    private slots:
        //for rotate animation, start when clecked
        void rotateAnimation(); 

    protected:
        //mouse event
        void mousePressEvent(QGraphicsSceneMouseEvent *event);

    public:
        //constructor
        PipeShape(int type, int dir, int x, int y, MainWindow *window);

        //rotate 90 degree clockwise
        void rotate();

        //behavior when clicked
        void clicked();

        //setter, they will change image
        void setWater(bool b);
        void setDir(int d);
};

#endif // PIPESHAPE_H
