#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "csvgraph.h"
#include "livedatagraph.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    csv_plot = CsvGraph(ui->excelPlot);
    live_data = new LiveDataGraph(ui->livePlot);
    SocketConnection * socket = new SocketConnection();
    socket->Connect();
    QObject::connect(socket, SIGNAL(newMessageFromServer(QString)), live_data, SLOT(handleNewMessageFromServer(QString)),Qt::AutoConnection);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_loadFile_clicked()
{
    csv_plot.LoadCsvFile();
}


