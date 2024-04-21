#ifndef PIPESHAPE_H
#define PIPESHAPE_H

#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QObject>

class MainWindow;

class PipeShape : public QGraphicsPixmapItem, public QObject
{
    private:
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
        void rotateAnimation(); //start when clecked

    protected:
        void mousePressEvent(QGraphicsSceneMouseEvent *event);

    public:
        PipeShape(int type, int dir, int x, int y, MainWindow *window);
        void rotate();
        void clicked();

        //setter, they will change image
        void setWater(bool b);
        void setDir(int d);
};

#endif // PIPESHAPE_H
