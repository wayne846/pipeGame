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

class MainWindow : public QMainWindow
{
        Q_OBJECT

    public:
        const int BASIC_SQUARE_WIDTH = 70;

        int squareWidth = 70;
        int windowWidth = 1000;
        int windowHeight = 800;
        QPixmap* images[5][2];
        vector<vector<PipeShape*>> pipeShapes;

        QGraphicsScene *scene;
        GameManager *gameManager;

        void update();

        MainWindow(QWidget *parent = nullptr);
        ~MainWindow();

    private slots:
        void on_pushButton_random_clicked();

    private:

        QGraphicsTextItem *text_hello;

        PipeShape *inputPipe;
        PipeShape *outputPipe;

        Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
