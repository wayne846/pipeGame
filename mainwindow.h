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
        const int BASIC_SQUARE_WIDTH = 70;
        const QColor TILE_DEFAULT_COLOR = QColor(176,212,229);
        const QColor TILE_PATH_COLOR = QColor(146, 200, 224);
        const QColor TILE_HOVER_COLOR = QColor(204, 220, 227);

        int squareWidth = 70;
        int windowWidth = 1000;
        int windowHeight = 600;
        bool isfinish = false; //I do not want to use isEnd again
        QPixmap* images[5][2];
        vector<vector<PipeShape*>> pipeShapes;

        //I am tired to use 2d vector
        vector<BackgroundTile*> tiles;

        QGraphicsScene *scene = NULL;
        GameManager *gameManager = NULL;

        void update();

        MainWindow(QWidget *parent = nullptr);
        ~MainWindow();

    private slots:
        void on_pushButton_random_clicked();

        void on_pushButton_file_clicked();

        void on_actionbackToMenu_triggered();

        void on_actionvolume0_triggered();

        void on_actionvolume30_triggered();

        void on_actionvolume50_triggered();

        void on_actionvolume70_triggered();

        void on_actionvolume100_triggered();

    private:
        PipeShape *inputPipe = NULL;
        PipeShape *outputPipe = NULL;
        QGraphicsTextItem *text_finish = NULL;

        void startInit(); //called after gameManager has setted

        Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
