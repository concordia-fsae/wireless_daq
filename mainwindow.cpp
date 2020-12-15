#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "csvgraph.h"
#include "livedatagraph.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->socket = new SocketConnection();
    this->socket->Connect();

    // add graph buttons
    QHBoxLayout *addGraphLayout = new QHBoxLayout();
    QPushButton *addLiveGraph = new QPushButton("Add Live Graph");
    QPushButton *addCsvGraph = new QPushButton("Add Static Graph");
    addGraphLayout->addWidget(addLiveGraph);
    addGraphLayout->addWidget(addCsvGraph);
    QObject::connect(addLiveGraph, SIGNAL(clicked()),this, SLOT(on_add_live_graph_clicked()));
    QObject::connect(addCsvGraph, SIGNAL(clicked()),this, SLOT(on_add_static_graph_clicked()));

    // add layouts to main layouts
    mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(addGraphLayout);

    // Sets all the UI components
    updateUI();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_add_live_graph_clicked()
{
    LiveDataGraph * graphToAdd = new LiveDataGraph(this->socket);
    mainLayout->addLayout(graphToAdd->getGraphWidgetLayout());
    QObject::connect(graphToAdd, SIGNAL(removeGraphFromLayout(QLayoutItem *)),this, SLOT(removeGraphFromLayout(QLayoutItem *)));
    updateUI();
}

void MainWindow::removeGraphFromLayout(QLayoutItem * layoutToRemove)
{
    mainLayout->removeItem(layoutToRemove);
    updateUI();
}

void MainWindow::on_add_static_graph_clicked()
{
    CsvGraph * newCsvGraph = new CsvGraph();
    mainLayout->addLayout(newCsvGraph->getGraphWidgetLayout());
    QObject::connect(newCsvGraph, SIGNAL(removeGraphFromLayout(QLayoutItem *)),this, SLOT(removeGraphFromLayout(QLayoutItem *)));
    updateUI();
}

void MainWindow::updateUI()
{
    QWidget *placeholderWidget = new QWidget;
    placeholderWidget->setLayout(mainLayout);
    setCentralWidget(placeholderWidget);
}


