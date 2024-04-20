#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsItem>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class GameManager;

class MainWindow : public QMainWindow
{
        Q_OBJECT

    public:
        const int BASIC_SQUARE_WIDTH = 70;

        int squareWidth;
        int windowWidth = 1000;
        int windowHeight = 800;

        MainWindow(QWidget *parent = nullptr);
        ~MainWindow();

    private slots:
        void on_pushButton_random_clicked();

    private:
        QGraphicsScene *scene;
        QGraphicsTextItem *text_hello;

        GameManager *gameManager;

        Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
