#include "csvgraph.h"
#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include <QDir>
#include <QDebug>
#include <QMessageBox>

CsvGraph::CsvGraph()
{}

CsvGraph::CsvGraph(QCustomPlot * graph)
{
    this->graph = graph;
    this->graph->addGraph();
    this->graph->graph(0)->setScatterStyle(QCPScatterStyle::ssCircle);
    this->graph->graph(0)->rescaleAxes();
    this->graph->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    this->graph->xAxis->setRange(0.0, 50);
    this->graph->yAxis->setRangeLower(0.0);
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

bool CsvGraph::isANumber(QString string)
{
    bool validate;
    string.toDouble(&validate);
    return validate;
}
