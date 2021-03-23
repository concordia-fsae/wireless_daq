#ifndef SOCKETCONNECTION_H
#define SOCKETCONNECTION_H

#include "graphdatapoint.h"
#include <QObject>
#include <QTcpSocket>
#include <QDebug>
#include <QAbstractSocket>

class SocketConnection : public QObject
{
    Q_OBJECT
public:
    explicit SocketConnection(QObject *parent = nullptr);
    void Connect();
    void GetMessages();
    QVector<GraphDataPoint> GetAllServerData();
    GraphDataPoint GetInitialDataPoint();

public slots:
    void connected();
    void disconnected();
    void readyRead();

signals:
    void newMessageFromServer(QString message);
    void newGraphPointFromServer(GraphDataPoint newDataPoint);

private:
    QTcpSocket *socket;
    QVector<GraphDataPoint> serverData;

};

#endif // SOCKETCONNECTION_H
