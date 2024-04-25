/***********************************************************************
 * File: main.cpp
 * Author: B112150536 B11215058
 * Create Date: 2024/04/24
 * Editor: B11215036
 * Update Date: 2024/04/25
 * Description: Pipe game
***********************************************************************/
#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    //create the game, show the main window
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
