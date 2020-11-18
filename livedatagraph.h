#ifndef LIVEDATAGRAPH_H
#define LIVEDATAGRAPH_H
#include "qcustomplot.h"

class LiveDataGraph
{
public:
    LiveDataGraph();
    LiveDataGraph(QCustomPlot * graph);

private:
    QCustomPlot * graph;
    QVector<double> qv_x_file, qv_y_file;

public slots:
    void newDataHandler(double timeVal, double yVal);

};

#endif // LIVEDATAGRAPH_H
