/***********************************************************************
 * File: mainwindow.cpp
 * Author: B112150536 B11215058
 * Create Date: 2024/04/24
 * Editor: B11215036
 * Update Date: 2024/04/25
 * Description: control the game flow, and display
***********************************************************************/
#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QScreen>
#include <QDebug>
#include "gamemanager.h"
#include "pipeshape.h"
#include "backgroundtile.h"
#include "soundmanager.h"
#include <QGraphicsTextItem>
#include <QDir>

//Intent: constructor
//Pre: nothing
//Post: initialize images and set the ui
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

//Intent: destructor
//Pre: nothing
//Post: delete ui
MainWindow::~MainWindow()
{
    delete ui;
}

//Intent: make sure the pipeShape is in the right position, check if the game is over
//Pre: nothing
//Post: all pipeShapes are in the right position, if the game is over, show the ending text
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
        text_finish = new QGraphicsTextItem("Stage Clear!");
        text_finish->setFont(QFont("Arial", 40));
        text_finish->setZValue(1);
        text_finish->hide();
        text_finish->setPos(windowWidth / 2 - text_finish->boundingRect().width() / 2, windowHeight / 2 - text_finish->boundingRect().height() / 2);
        scene->addItem(text_finish);
        text_finish->show();
        //play finish sound
        SoundManager::getInstance()->playFinish();
    }
}

//Intent: initialize the game
//Pre: gameManager has setted
//Post: all menu ui is hidden, set the window size, all pipeShapes and background are setted, start the game
void MainWindow::startInit(){
    int height = gameManager->getHeight();
    int width = gameManager->getWidth();

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

    //set scene and mainwindow
    scene = new QGraphicsScene(this);
    scene->setSceneRect(0, 0, windowWidth, windowHeight);
    this->setMinimumSize(0, 0);
    this->setMaximumSize(100000, 100000);
    this->setGeometry(0, 0, windowWidth, windowHeight + 20);
    this->setMinimumSize(this->size());
    this->setMaximumSize(this->size());
    QRect screenSize = this->screen()->geometry();
    this->move(screenSize.width()/2 - windowWidth/2, screenSize.height()/2 - windowHeight/2);

    //set view
    ui->graphicsView->setFixedSize(windowWidth, windowHeight);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setScene(scene);

    //init pipeShapes
    for(int i = 0; i < height; i++){
        vector<PipeShape*> row;
        for(int j = 0; j < width; j++){
            row.push_back(NULL);
        }
        pipeShapes.push_back(row);
    }

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

    SoundManager::getInstance()->playBgm();
    update();
}

//Intent: start the game by random map
//Pre: nothing
//Post: set the gameManager and call startInit
void MainWindow::on_pushButton_random_clicked()
{
    int height = ui->spinBox_height->value();
    int width = ui->spinBox_width->value();

    //create map
    gameManager = new GameManager(height, width);

    startInit();
}

//Intent: start the game by file
//Pre: nothing
//Post: set the gameManager and call startInit
void MainWindow::on_pushButton_file_clicked()
{
    gameManager = new GameManager();

    //if cannot open file, show error, not start the game
    if(!GameManager::isSuccess){
        delete(gameManager);
        gameManager = NULL;
        ui->pushButton_file->setText("Start by Default Map\n(test.txt)\nError: cannot open file");
        return;
    }

    startInit();
}

//Intent: back to menu
//Pre: nothing
//Post: show and hide ui, delete all object, set the window size
void MainWindow::on_actionbackToMenu_triggered()
{
    //show and hide ui
    ui->label__title->show();
    ui->label_height->show();
    ui->label_width->show();
    ui->spinBox_height->show();
    ui->spinBox_width->show();
    ui->spinBox_height->setValue(10);
    ui->spinBox_width->setValue(10);
    ui->pushButton_random->show();
    ui->pushButton_file->show();
    ui->pushButton_file->setText("Start by Default Map\n(test.txt)");

    //set mainwindow
    this->setMinimumSize(0, 0);
    this->setMaximumSize(100000, 100000);
    this->setGeometry(0, 0, 1000, 600);
    this->setMinimumSize(this->size());
    this->setMaximumSize(this->size());
    windowWidth = 1000;
    windowHeight = 600;
    QRect screenSize = this->screen()->geometry();
    this->move(screenSize.width()/2 - windowWidth/2, screenSize.height()/2 - windowHeight/2);

    //set view
    ui->graphicsView->setFixedSize(windowWidth, windowHeight);

    //delete all object
    for(int i = 0; i < pipeShapes.size(); i++){
        for(int j = 0; j < pipeShapes[i].size(); j++){
            if(pipeShapes[i][j] != NULL){
                delete(pipeShapes[i][j]);
                pipeShapes[i][j] = NULL;
            }
        }
    }
    pipeShapes.clear();
    for(int i = 0; i < tiles.size(); i++){
        if(tiles[i] != NULL){
            delete(tiles[i]);
            tiles[i] = NULL;
        }
    }
    tiles.clear();
    if(inputPipe != NULL){
        delete(inputPipe);
        inputPipe = NULL;
    }
    if(outputPipe != NULL){
        delete(outputPipe);
        outputPipe = NULL;
    }
    if(scene != NULL){
        delete(scene);
        scene = NULL;
    }
    if(gameManager != NULL){
        delete(gameManager);
        gameManager = NULL;
    }

    //set flag
    isfinish = false;
    GameManager::isSuccess = false;

    //stop bgm
    SoundManager::getInstance()->stopBgm();
}

//Intent: set volume
//Pre: nothing
//Post: set the volume to 0%
void MainWindow::on_actionvolume0_triggered()
{
    SoundManager::getInstance()->setVolume(0);
}

//Intent: set volume
//Pre: nothing
//Post: set the volume to 30%
void MainWindow::on_actionvolume30_triggered()
{
    SoundManager::getInstance()->setVolume(0.3);
}

//Intent: set volume
//Pre: nothing
//Post: set the volume to 50%
void MainWindow::on_actionvolume50_triggered()
{
    SoundManager::getInstance()->setVolume(0.5);
}

//Intent: set volume
//Pre: nothing
//Post: set the volume to 70%
void MainWindow::on_actionvolume70_triggered()
{
    SoundManager::getInstance()->setVolume(0.7);
}

//Intent: set volume
//Pre: nothing
//Post: set the volume to 100%
void MainWindow::on_actionvolume100_triggered()
{
    SoundManager::getInstance()->setVolume(1);
}

