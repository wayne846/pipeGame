#ifndef PIPESHAPE_H
#define PIPESHAPE_H

#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QObject>
#include <QMediaPlayer>
#include <QAudioOutput>

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

        //sound effact
        //use static because I do not want everyone has these guy
        static QMediaPlayer *mediaPlayer;
        static QAudioOutput *audioOutput;

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
