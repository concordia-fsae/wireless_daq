#include "mainwindow.h"
#include "socketconnection.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SocketConnection socket;
    socket.Connect();
    MainWindow w;
    w.show();
    return a.exec();
}
