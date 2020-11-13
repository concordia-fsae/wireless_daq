#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "csvgraph.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    csv_plot = CsvGraph(ui->excelPlot);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_loadFile_clicked()
{
    csv_plot.LoadCsvFile();
}


