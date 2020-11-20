#include "livedatagraph.h"

LiveDataGraph::LiveDataGraph(QCustomPlot * graph, QObject *parent) : QObject(parent)
{
    this->graph = graph;
    this->graph->addGraph();
    this->graph->graph(0)->rescaleAxes();
}

void LiveDataGraph::handleNewMessageFromServer(QString message)
{
    QStringList splitString = message.split(",");
    QString xVal = splitString.first();
    QString yVal = splitString.last() == "" ? "0" : splitString.last();
    if(isANumber(xVal) && isANumber(yVal)) {
        addValueToGraph(xVal.toDouble(), yVal.toDouble());
    }
}

void LiveDataGraph::addValueToGraph(double xVal, double yVal)
{
    qv_x_file.append(xVal);
    qv_y_file.append(yVal);
    this->graph->graph(0)->setData(qv_x_file, qv_y_file);
    this->graph->xAxis->rescale(true);
    this->graph->yAxis->rescale(true);
    this->graph->replot();
    this->graph->update();
}

bool LiveDataGraph::isANumber(QString string)
{
    bool validate;
    string.toDouble(&validate);
    return validate;
}
