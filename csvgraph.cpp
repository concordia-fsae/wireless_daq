#include "csvgraph.h"
#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include <QDir>
#include <QMessageBox>

CsvGraph::CsvGraph(QObject *parent) : QObject(parent)
{
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
    QObject::connect(this->loadFileButton, SIGNAL(clicked()), this, SLOT(LoadCsvFile()));
    QObject::connect(this->removeGraphButton, SIGNAL(clicked()), this, SLOT(deleteGraph()));
}

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
    this->graph->graph(0)->setData(qv_x_file, qv_y_file);
    this->graph->xAxis->rescale(true);
    this->graph->yAxis->rescale(true);
    this->graph->replot();
    this->graph->update();
}

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
