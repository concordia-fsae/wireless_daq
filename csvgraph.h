#ifndef CSVGRAPH_H
#define CSVGRAPH_H
#include "qcustomplot.h"

class CsvGraph
{
public:
    CsvGraph();
    CsvGraph(QCustomPlot * graph);
    void LoadCsvFile();

private:
    QCustomPlot * graph;
    bool isANumber(QString);
};

#endif // CSVGRAPH_H
