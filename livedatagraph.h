#ifndef LIVEDATAGRAPH_H
#define LIVEDATAGRAPH_H
#include "qcustomplot.h"
#include <QObject>

class LiveDataGraph : public QObject
{
    Q_OBJECT
public:
    explicit LiveDataGraph(QCustomPlot * graph, QObject *parent = nullptr);

private:
    bool isANumber(QString string);
    QCustomPlot * graph;
    QVector<double> qv_x_file, qv_y_file;
    void addValueToGraph(double xVal, double yVal);

signals:

public slots:
    void handleNewMessageFromServer(QString message);

};

#endif // LIVEDATAGRAPH_H
