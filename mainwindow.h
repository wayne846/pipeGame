/***********************************************************************
 * File: mainwindow.h
 * Author: B112150536 B11215058
 * Create Date: 2024/04/24
 * Editor: B11215036
 * Update Date: 2024/04/25
 * Description: control the game flow, and display
***********************************************************************/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <vector>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

using namespace std;

class GameManager;
class PipeShape;
class BackgroundTile;

class MainWindow : public QMainWindow
{
        Q_OBJECT

    public:
        //constants
        //square size
        const int BASIC_SQUARE_WIDTH = 70;
        //colors for background
        const QColor TILE_DEFAULT_COLOR = QColor(176,212,229);
        const QColor TILE_PATH_COLOR = QColor(146, 200, 224);
        const QColor TILE_HOVER_COLOR = QColor(204, 220, 227);

        //size
        int squareWidth = 70;
        int windowWidth = 1000;
        int windowHeight = 600;
        //if the game is over
        bool isfinish = false; //I do not want to use isEnd again

        //the pointer of images, for pipeshape to display
        QPixmap* images[5][2];
        //the pointer of pipeShapes, same size of pipe
        vector<vector<PipeShape*>> pipeShapes;
        //Background, I am tired to use 2d vector
        vector<BackgroundTile*> tiles;

        //the pointer of scene, all display elements will be added to the scene
        QGraphicsScene *scene = NULL;

        //the pointer of gameManager, it will create the map
        GameManager *gameManager = NULL;

        //make sure the pipeShape is in the right position
        void update();

        MainWindow(QWidget *parent = nullptr);
        ~MainWindow();

    private slots:
        //buttons event
        void on_pushButton_random_clicked();

        void on_pushButton_file_clicked();

        void on_actionbackToMenu_triggered();

        void on_actionvolume0_triggered();

        void on_actionvolume30_triggered();

        void on_actionvolume50_triggered();

        void on_actionvolume70_triggered();

        void on_actionvolume100_triggered();

    private:
        //input and output pipe, individual for other pipe
        PipeShape *inputPipe = NULL;
        PipeShape *outputPipe = NULL;

        //finish text
        QGraphicsTextItem *text_finish = NULL;

        //init the game, called after gameManager has setted
        void startInit();

        Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
