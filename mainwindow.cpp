#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "csvgraph.h"
#include "livedatagraph.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    // Starts connection to TCP server
    ui->setupUi(this);
    this->socket = new SocketConnection();
    this->socket->Connect();

    // Creates 'Add graph' buttons
    QHBoxLayout *addGraphLayout = new QHBoxLayout();
    QPushButton *addLiveGraph = new QPushButton("Add Live Graph");
    QPushButton *addCsvGraph = new QPushButton("Add Static Graph");

    // Adds the above buttons to the layout
    addGraphLayout->addWidget(addLiveGraph);
    addGraphLayout->addWidget(addCsvGraph);

    // --- Event Listeners --

    // When the 'add live graph' button is clicked, call 'on_add_live_graph_clicked' function
    QObject::connect(addLiveGraph, SIGNAL(clicked()),this, SLOT(on_add_live_graph_clicked()));
    // When the 'add static graph' button is clicked, call 'on_add_static_graph_clicked' function
    QObject::connect(addCsvGraph, SIGNAL(clicked()),this, SLOT(on_add_static_graph_clicked()));

    // Takes the button layout and adds it to the main layout
    mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(addGraphLayout);

    // Sets all the UI components
    updateUI();
}

MainWindow::~MainWindow()
{
    delete ui;
}

/*!
 * \brief MainWindow::on_add_live_graph_clicked
 *
 * Creats and adds a liveDataGraph to the UI
 */
void MainWindow::on_add_live_graph_clicked()
{
    LiveDataGraph * graphToAdd = new LiveDataGraph(this->socket);
    mainLayout->addLayout(graphToAdd->getGraphWidgetLayout());
    // Connects the event listener of the socket to the live graph class
    // This will listen if the remove graph button is clicked and removes the graph from the layout
    QObject::connect(graphToAdd, SIGNAL(removeGraphFromLayout(QLayoutItem *)),this, SLOT(removeGraphFromLayout(QLayoutItem *)));
    updateUI();
}

/*!
 * \brief MainWindow::removeGraphFromLayout
 * \param layoutToRemove
 *
 * removes either the csvGraph or livegraph from the main UI layout
 */
void MainWindow::removeGraphFromLayout(QLayoutItem * layoutToRemove)
{
    mainLayout->removeItem(layoutToRemove);
    updateUI();
}

/*!
 * \brief MainWindow::on_add_static_graph_clicked
 *
 * Creats and adds a csvDataGraph to the UI
 */
void MainWindow::on_add_static_graph_clicked()
{
    CsvGraph * newCsvGraph = new CsvGraph();
    mainLayout->addLayout(newCsvGraph->getGraphWidgetLayout());
    // This will listen if the remove graph button is clicked and removes the graph from the layout
    QObject::connect(newCsvGraph, SIGNAL(removeGraphFromLayout(QLayoutItem *)),this, SLOT(removeGraphFromLayout(QLayoutItem *)));
    updateUI();
}

void MainWindow::updateUI()
{
    QWidget *placeholderWidget = new QWidget;
    placeholderWidget->setLayout(mainLayout);
    setCentralWidget(placeholderWidget);
}


