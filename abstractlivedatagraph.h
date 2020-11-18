#ifndef ABSTRACTLIVEDATAGRAPH_H
#define ABSTRACTLIVEDATAGRAPH_H

#include <QObject>
#include "livedatagraph.h"


class AbstractLiveDataGraph : public QObject
{
    Q_OBJECT
public:
    explicit AbstractLiveDataGraph(QCustomPlot * graph, QObject *parent = nullptr);

private:
    LiveDataGraph* live_graph = nullptr;
    bool isANumber(QString string);

signals:

public slots:
    void handleNewMessageFromServer(QString message);

};

#endif // ABSTRACTLIVEDATAGRAPH_H
