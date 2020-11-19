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
    void on_loadFile_clicked();

private:
    Ui::MainWindow *ui;
    CsvGraph csv_plot;
    LiveDataGraph * live_data;
};
#endif // MAINWINDOW_H
