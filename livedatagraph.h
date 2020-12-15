#ifndef LIVEDATAGRAPH_H
#define LIVEDATAGRAPH_H
#include "qcustomplot.h"
#include "socketconnection.h"
#include <QObject>

class LiveDataGraph : public QObject
{
    Q_OBJECT
public:
    explicit LiveDataGraph(SocketConnection * socket, QObject *parent = nullptr);
    QVBoxLayout * getGraphWidgetLayout();

private:
    QCustomPlot * graph;
    bool isANumber(QString string);
    QVector<double> qv_x_file, qv_y_file;
    void addValueToGraph(double xVal, double yVal);
    QVBoxLayout *vLayout = new QVBoxLayout;
    QString displayAttribute;
    QComboBox * attributeListBox;
    QPushButton * removeGraphButton;

signals:
    void removeGraphFromLayout(QLayoutItem * layoutToRemove);

public slots:
    void handleNewMessageFromServer(QString message);
    void changeDisplayAttribute(QString newAttribute);
    void deleteGraph();

};

#endif // LIVEDATAGRAPH_H
