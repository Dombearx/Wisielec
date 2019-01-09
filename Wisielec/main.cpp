#include "mainwindow.h"
#include <thread>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow* w = new MainWindow();
    w->show();

    cout << "NO ELO" << endl;

    std::thread(&MainWindow::waitForServer, w).detach();
    //std::thread tserver(&MainWindow::waitForServer, w);

    return a.exec();
}
