#include "abstractlivedatagraph.h"

AbstractLiveDataGraph::AbstractLiveDataGraph(QCustomPlot * graph, QObject *parent) : QObject(parent)
{
    live_graph = new LiveDataGraph(graph);
}

void AbstractLiveDataGraph::handleNewMessageFromServer(QString message)
{
    QStringList splitString = message.split(",");
    QString xVal = splitString.first();
    QString yVal = splitString.last() == "" ? "0" : splitString.last();
    if(isANumber(xVal) && isANumber(yVal)) {
        live_graph->newDataHandler(xVal.toDouble(), yVal.toDouble());
    }
}

bool AbstractLiveDataGraph::isANumber(QString string)
{
    bool validate;
    string.toDouble(&validate);
    return validate;
}
