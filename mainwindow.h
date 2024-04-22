#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <vector>
#include <QSoundEffect>

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

        const QUrl CLICK_SOUND = QUrl("qrc:/click.mp3");
        const QUrl FINISH_SOUND = QUrl("qrc:/finish.mp3");
        const QUrl BGM_SOUND = QUrl("qrc:/prohibition.mp3");
        const QUrl CLICK_SOUND_WAV = QUrl("qrc:/click.wav");
        const QUrl FINISH_SOUND_WAV = QUrl("qrc:/finish.wav");
        const QUrl BGM_SOUND_WAV = QUrl("qrc:/prohibition.wav");

        int squareWidth = 70;
        int windowWidth = 1000;
        int windowHeight = 800;
        bool isfinish = false; //I do not want to use isEnd again
        QPixmap* images[5][2];
        vector<vector<PipeShape*>> pipeShapes;

        //I am tired to use 2d vector
        vector<BackgroundTile*> tiles;

        QGraphicsScene *scene;
        GameManager *gameManager;

        //sound
        QSoundEffect *soundEffect_bgm;
        QSoundEffect *soundEffect_finish;

        void update();

        MainWindow(QWidget *parent = nullptr);
        ~MainWindow();

    private slots:
        void on_pushButton_random_clicked();

        void on_pushButton_file_clicked();

    private:
        PipeShape *inputPipe;
        PipeShape *outputPipe;
        QGraphicsTextItem *text_finish;

        void startInit(); //called after gameManager has setted

        Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
