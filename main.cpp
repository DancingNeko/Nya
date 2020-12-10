#include "mainwindow.h"

#include <QApplication>
#include<QFrame>

#include "utilities.h"

using namespace std;

int main(int argc, char *argv[])
{
    // save cout buffer
    utilitiesInitialize("temp.log");

    QApplication a(argc, argv);
    MainWindow w;
    w.resize(1280,720);
    w.setWindowTitle("Tile Puzzle");
    w.show();
    auto res = a.exec();

    // restore cout old buffer
    utilitiesUninitializePrint();

    return res;
}
