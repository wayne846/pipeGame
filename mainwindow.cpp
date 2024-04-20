#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QScreen>
#include "gamemanager.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_random_clicked()
{
    int height = ui->spinBox_height->value();
    int width = ui->spinBox_width->value();

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

    text_hello = scene->addText("Hello", QFont("Arial", 20));
    text_hello->setPos(0, 0);
    ui->graphicsView->setScene(scene);

    gameManager = new GameManager(height, width);
}

