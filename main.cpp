#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    OpenCV cv;
    MainWindow mainWindow(cv);
    return app.exec();
}