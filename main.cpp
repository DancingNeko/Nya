#include "mainwindow.h"

#include <QApplication>
#include<QFrame>

#include "utilities.h"

using namespace std;

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainWindow w;
    w.resize(1280,720);
    w.setWindowTitle("Tile Puzzle");
    w.show();
    auto res = a.exec();


    return res;
}
