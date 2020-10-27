#ifndef SOCKETCONNECTION_H
#define SOCKETCONNECTION_H

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

signals:

public slots:
    void connected();
    void disconnected();
    void readyRead();

private:
    QTcpSocket *socket;

};

#endif // SOCKETCONNECTION_H
