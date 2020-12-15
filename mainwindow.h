#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "csvgraph.h"
#include "livedatagraph.h"
#include "socketconnection.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_add_live_graph_clicked();
    void on_add_static_graph_clicked();
    void removeGraphFromLayout(QLayoutItem * layoutToRemove);

private:
    Ui::MainWindow *ui;
    QVBoxLayout *mainLayout;
    SocketConnection * socket;
    void updateUI();
};
#endif // MAINWINDOW_H
