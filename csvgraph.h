#ifndef CSVGRAPH_H
#define CSVGRAPH_H
#include "qcustomplot.h"
#include <QObject>

class CsvGraph: public QObject
{
    Q_OBJECT
public:
    explicit CsvGraph(QObject *parent = nullptr);
    QVBoxLayout * getGraphWidgetLayout();

private:
    QCustomPlot * graph;
    bool isANumber(QString string);
    QPushButton * loadFileButton;
    QPushButton * removeGraphButton;

signals:
    void removeGraphFromLayout(QLayoutItem * layoutToRemove);

public slots:
    void LoadCsvFile();
    void deleteGraph();
};

#endif // CSVGRAPH_H
