#ifndef PIPESHAPE_H
#define PIPESHAPE_H

#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QObject>

class MainWindow;

class PipeShape : public QGraphicsPixmapItem, public QObject
{
    private:
        int type;
        int x;
        int y;
        bool hasWater;

        MainWindow *window;
        QTimer *timer;
        int targetDir;

    private slots:
        void rotateAnimation();

    protected:
        void mousePressEvent(QGraphicsSceneMouseEvent *event);

    public:
        PipeShape(int type, int dir, int x, int y, MainWindow *window);
        void rotate();
        void clicked();
        void setWater(bool b);

};

#endif // PIPESHAPE_H
