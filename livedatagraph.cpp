#include "livedatagraph.h"

LiveDataGraph::LiveDataGraph()
{ }

LiveDataGraph::LiveDataGraph(QCustomPlot * graph)
{
    this->graph = graph;
    this->graph->addGraph();
    this->graph->graph(0)->setScatterStyle(QCPScatterStyle::ssCircle);
    this->graph->graph(0)->rescaleAxes();
    this->graph->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    this->graph->xAxis->setRange(0.0, 50);
    this->graph->yAxis->setRangeLower(0.0);
}

void LiveDataGraph::newDataHandler(double timeVal, double yVal){
    qv_x_file.append(timeVal);
    qv_y_file.append(yVal);
    this->graph->graph(0)->setData(qv_x_file, qv_y_file);
    this->graph->xAxis->rescale(true);
    this->graph->yAxis->rescale(true);
    this->graph->replot();
    this->graph->update();
}
