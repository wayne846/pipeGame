#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QScreen>
#include <QDebug>
#include "gamemanager.h"
#include "pipeshape.h"
#include "backgroundtile.h"
#include <QGraphicsTextItem>
#include <QDir>

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

    //set finish text
    text_finish = new QGraphicsTextItem("Stage Clear!");
    text_finish->setFont(QFont("Arial", 40));
    text_finish->setZValue(1);
    text_finish->hide();

    //set sound
    //bgm
    mediaPlayer_bgm = new QMediaPlayer;
    audioOutput_bgm = new QAudioOutput;
    mediaPlayer_bgm->setAudioOutput(audioOutput_bgm);
    mediaPlayer_bgm->setSource(BGM_SOUND);
    mediaPlayer_bgm->setLoops(QMediaPlayer::Infinite);
    audioOutput_bgm->setVolume(40);
    //finish
    mediaPlayer_finish = new QMediaPlayer;
    audioOutput_finish = new QAudioOutput;
    mediaPlayer_finish->setAudioOutput(audioOutput_finish);
    mediaPlayer_finish->setSource(FINISH_SOUND);
    audioOutput_finish->setVolume(50);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::update(){
    bool flag = gameManager->isEnd();
    for(int i = 0; i < gameManager->getHeight(); i++){
        for(int j = 0; j < gameManager->getWidth(); j++){
            Pipe *pipe = gameManager->getPipe(j, i);
            pipeShapes[i][j]->setWater(pipe->hasWater);
            pipeShapes[i][j]->setDir(pipe->dir);
        }
    }

    //finish game
    if(flag){
        outputPipe->setWater(true);
        isfinish = true;
        qDebug() << "Stage Clear!";
        //show ending text
        text_finish->setPos(windowWidth / 2 - text_finish->boundingRect().width() / 2, windowHeight / 2 - text_finish->boundingRect().height() / 2);
        scene->addItem(text_finish);
        text_finish->show();
        //play finish sound
        mediaPlayer_finish->play();
    }
}

void MainWindow::on_pushButton_random_clicked()
{
    int height = ui->spinBox_height->value();
    int width = ui->spinBox_width->value();

    //set all value about size
    squareWidth = 700 / max(height, width);
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

    //set pipeShapes and background
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            Pipe* pipe = gameManager->getPipe(j, i);
            pipeShapes[i][j] = new PipeShape(pipe->type, pipe->dir, j, i, this);
            tiles.push_back(new BackgroundTile(j, i, pipe->isdefaultPath, this));
        }
    }
    inputPipe = new PipeShape(4, 0, -1, gameManager->getStartY(), this);
    inputPipe->setWater(true);
    outputPipe = new PipeShape(4, 0, width, gameManager->getEndY(), this);
    for(int i = 0; i < height; i++){
        BackgroundTile *tile1;
        BackgroundTile *tile2;
        tile1 = new BackgroundTile(-1, i, (i == gameManager->getStartY()), this);
        tile2 = new BackgroundTile(width, i, (i == gameManager->getEndY()), this);
        tile1->setIsActive(false);
        tile2->setIsActive(false);
        tiles.push_back(tile1);
        tiles.push_back(tile2);
    }

    mediaPlayer_bgm->play();
    update();
}

