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
        int x;
        int y;
        bool isDefaultPath;
        bool isActive;

        MainWindow *window;

        QColor normal_color;

    protected:
        void mousePressEvent(QGraphicsSceneMouseEvent *event);
        void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
        void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

    public:
        BackgroundTile(int x, int y, bool isDefaultPath, MainWindow *window);

        void setIsActive(bool b);
};

#endif // BACKGROUNDTILE_H
