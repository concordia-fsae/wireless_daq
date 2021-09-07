#include "csvgraph.h"
#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include <QDir>
#include <QMessageBox>

/*!
 * \brief CsvGraph::CsvGraph
 * \param parent
 * \class CsvGraph
 *
 * Takes a csv file and plots it on a graph
 * Sample csv format: [Time, Speed]
 */
CsvGraph::CsvGraph(QObject *parent) : QObject(parent)
{
    // Handles the UI elements of the CSVGraph
    this->graph = new QCustomPlot;
    QCPTextElement *graphTitle = new QCPTextElement(this->graph, "Static Graph", QFont("sans", 17, QFont::Bold));
    this->graph->plotLayout()->insertRow(0);
    this->graph->plotLayout()->addElement(0, 0, graphTitle);
    this->graph->addGraph();
    this->graph->graph(0)->setScatterStyle(QCPScatterStyle::ssCircle);
    this->graph->graph(0)->rescaleAxes();
    this->graph->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    this->graph->xAxis->setRange(0.0, 50);
    this->graph->yAxis->setRangeLower(0.0);
    this->loadFileButton = new QPushButton("Load File");
    this->removeGraphButton = new QPushButton("Remove Graph");

    // --- Event Listeners ---

    // Listens when the 'load file' button is clicked and triggers a method
    QObject::connect(this->loadFileButton, SIGNAL(clicked()), this, SLOT(LoadCsvFile()));

    // Listens when the 'remove graph' button is clicked and the deleteGraph method is called
    QObject::connect(this->removeGraphButton, SIGNAL(clicked()), this, SLOT(deleteGraph()));
}

/*!
 * \brief CsvGraph::LoadCsvFile
 *
 * Opens and reads a csv file and updates the graph UI with it's data
 */
void CsvGraph::LoadCsvFile()
{
    QVector<double> qv_x_file, qv_y_file;
    QString file_name = QFileDialog::getOpenFileName(NULL, "Open file", QDir::homePath());

    QFile file(file_name);
    if(!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(NULL, "title", "file not open");
    }
    QTextStream in(&file);
    while(!in.atEnd()) {
        QString mText = in.readLine();
        QStringList splitString = mText.split(",");
        QString xVal = splitString.first();
        QString yVal = splitString.last() == "" ? "0" : splitString.last();
        if(isANumber(xVal) && isANumber(yVal)) {
            qv_x_file.append(xVal.toDouble());
            qv_y_file.append(yVal.toDouble());
        } else {
            this->graph->xAxis->setLabel(xVal);
            this->graph->yAxis->setLabel(yVal);
        }
    }

    // Sets the all the data into the graph and updates it
    this->graph->graph(0)->setData(qv_x_file, qv_y_file);
    this->graph->xAxis->rescale(true);
    this->graph->yAxis->rescale(true);
    this->graph->replot();
    this->graph->update();
}

/*!
 * \brief CsvGraph::getGraphWidgetLayout
 * \return
 *
 * Gets the CsvGraph UI ready for display
 */
QVBoxLayout * CsvGraph::getGraphWidgetLayout()
{
    QVBoxLayout * vLayout = new QVBoxLayout;
    QHBoxLayout * buttonsLayout = new QHBoxLayout();
    buttonsLayout->addWidget(this->loadFileButton);
    buttonsLayout->addWidget(this->removeGraphButton);
    vLayout->addWidget(this->graph);
    vLayout->addLayout(buttonsLayout);
    return vLayout;
}

void CsvGraph::deleteGraph()
{
    this->deleteLater();
    emit removeGraphFromLayout(this->getGraphWidgetLayout());
}

bool CsvGraph::isANumber(QString string)
{
    bool validate;
    string.toDouble(&validate);
    return validate;
}
