#include "socketconnection.h"

SocketConnection::SocketConnection(QObject *parent) : QObject(parent)
{

}

// Sets up the connection with the TCP server
void SocketConnection::Connect()
{
    socket = new QTcpSocket(this);
    connect(socket, SIGNAL(connected()), this, SLOT(connected()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));

    qDebug() << "Connecting...";
    socket->connectToHost("localhost",9898); //This connects to the mock server (must have it running)
    if(!socket->waitForConnected(1000))
    {
        qDebug() << "Error! " << socket->errorString();
    }
}

// When a connection is formed with the TCP server, this method will be called
void SocketConnection::connected()
{
    qDebug() << "Connected";
}

// When the socket is disconnected from the TCP serve, this method will be called
void SocketConnection::disconnected()
{
    qDebug() << "Disconnected";
}

// When a message comes from the TCP server, this method will handle it
void SocketConnection::readyRead()
{
    qDebug() << "Reading...";
    qDebug() << socket->readAll();
}
