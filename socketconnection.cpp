#include "socketconnection.h"
#include "graphdatapoint.h"

/*!
 * \brief SocketConnection::SocketConnection
 * \param parent
 * \class SocketConnection
 *
 * The socket class handles the connection to an external server that will feed it binary data.
 */
SocketConnection::SocketConnection(QObject *parent) : QObject(parent)
{}

/*!
 * \brief SocketConnection::Connect
 *
 * Sets up the connection with the TCP server
 */
void SocketConnection::Connect()
{
    socket = new QTcpSocket(this);
    // These event listeners bind to the QTcpSocket class and call methods when the TCP connection is: establish, recieves a new message or disconnects
    connect(socket, SIGNAL(connected()), this, SLOT(connected()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));

    qDebug() << "Connecting...";

    // This connects to the mock server (must have it running)
    // The 'connectToHost' method parameters will change when connecting to real prod environment
    socket->connectToHost("localhost",9898); // TO CHANGE FOR PROD
    if(!socket->waitForConnected(1000))
    {
        qDebug() << "Error! " << socket->errorString();
    }
}

/*!
 * \brief SocketConnection::connected
 *
 * When a connection is formed with the TCP server, this method will be called
 */
void SocketConnection::connected()
{
    qDebug() << "Connected";
    this->serverData.clear(); //This might be changed in the future if we add reconnection capability
    emit newMessageFromServer("connected");
}

/*!
 * \brief SocketConnection::disconnected
 *
 * When the socket is disconnected from the TCP serve, this method will be called
 */
void SocketConnection::disconnected()
{
    qDebug() << "Disconnected";
}

/*!
 * \brief SocketConnection::readyRead
 *
 * When a message comes from the TCP server, this method will be called
 */
void SocketConnection::readyRead()
{
    qDebug() << "Reading...";
    // This will have the new message coming from the server
    QString messages = QString(socket->readAll()); // This will be binary
    qDebug() << messages;
    GraphDataPoint newDataPoint = GraphDataPoint(messages);
    // holds all the data that came from the server in this class
    this->serverData.append(newDataPoint);
    // brodcasts to all listening classes (LiveDataGraph) that a new data point came in
    emit newGraphPointFromServer(newDataPoint);
}

QVector<GraphDataPoint> SocketConnection::GetAllServerData()
{
    return this->serverData;
}

/*!
 * \brief SocketConnection::GetInitialDataPoint
 * \return
 *
 * This class helps display relative time on a graph
 */
GraphDataPoint SocketConnection::GetInitialDataPoint()
{
    return this->serverData.front();
}

