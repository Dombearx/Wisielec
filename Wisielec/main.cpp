#include "mainwindow.h"
#include <thread>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow* w = new MainWindow();
    w->show();

    std::thread(&MainWindow::waitForServer, w).detach();

    return a.exec();
}
