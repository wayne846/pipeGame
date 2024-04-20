#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QScreen>
#include "gamemanager.h"
#include "pipeshape.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //set images
    images[0][0] = new QPixmap(":/I");
    images[0][1] = new QPixmap(":/IW");
    images[1][0] = new QPixmap(":/T");
    images[1][1] = new QPixmap(":/TW");
    images[2][0] = new QPixmap(":/+");
    images[2][1] = new QPixmap(":/+W");
    images[3][0] = new QPixmap(":/L");
    images[3][1] = new QPixmap(":/LW");
    images[4][0] = new QPixmap(":/IO");
    images[4][1] = new QPixmap(":/IOW");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::update(){
    bool flag = gameManager->isEnd();
    for(int i = 0; i < gameManager->getHeight(); i++){
        for(int j = 0; j < gameManager->getWidth(); j++){
            pipeShapes[i][j]->setWater(gameManager->getPipe(j, i)->hasWater);
        }
    }
}

void MainWindow::on_pushButton_random_clicked()
{
    int height = ui->spinBox_height->value();
    int width = ui->spinBox_width->value();

    //set all value about size
    squareWidth = 700 / min(height, width);
    windowWidth = squareWidth * (width + 2);
    windowHeight = squareWidth * height;

    //hide all ui
    ui->pushButton_random->hide();
    ui->pushButton_file->hide();
    ui->label_width->hide();
    ui->label_height->hide();
    ui->label__title->hide();
    ui->spinBox_height->hide();
    ui->spinBox_width->hide();

    //set scene
    scene = new QGraphicsScene(this);
    scene->setSceneRect(0, 0, windowWidth, windowHeight);
    this->setGeometry(0, 0, windowWidth, windowHeight + 20);
    QRect screenSize = this->screen()->geometry();
    this->move(screenSize.width()/2 - windowWidth/2, screenSize.height()/2 - windowHeight/2);

    //set view
    ui->graphicsView->setFixedSize(windowWidth, windowHeight);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // text_hello = scene->addText("Hello", QFont("Arial", 20));
    // text_hello->setPos(0, 0);

    ui->graphicsView->setScene(scene);

    //init pipeShapes
    for(int i = 0; i < height; i++){
        vector<PipeShape*> row;
        for(int j = 0; j < width; j++){
            row.push_back(NULL);
        }
        pipeShapes.push_back(row);
    }

    //create map
    gameManager = new GameManager(height, width);

    //set pipeShapes
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            Pipe* pipe = gameManager->getPipe(j, i);
            pipeShapes[i][j] = new PipeShape(pipe->type, pipe->dir, j, i, this);
        }
    }
    inputPipe = new PipeShape(4, 0, -1, gameManager->getStartY(), this);
    inputPipe->setWater(true);
    outputPipe = new PipeShape(4, 0, width, gameManager->getEndY(), this);

    update();
}

