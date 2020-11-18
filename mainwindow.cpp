#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "csvgraph.h"
#include "livedatagraph.h"
#include "abstractlivedatagraph.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    csv_plot = CsvGraph(ui->excelPlot);
    SocketConnection * socket = new SocketConnection();
    socket->Connect();
    AbstractLiveDataGraph * q_live_data = new AbstractLiveDataGraph(ui->livePlot);
    QObject::connect(socket, SIGNAL(newMessageFromServer(QString)), q_live_data, SLOT(handleNewMessageFromServer(QString)),Qt::AutoConnection);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_loadFile_clicked()
{
    csv_plot.LoadCsvFile();
}


