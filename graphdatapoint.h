#ifndef GRAPHDATAPOINT_H
#define GRAPHDATAPOINT_H

#include <QDateTime>
#include <QMap>
#include <QDebug>

class GraphDataPoint
{
public:
    GraphDataPoint(QString rawBinary);
    QDateTime getTimestamp();
    QString getRawBinary();
    double getAttributeValue(QString attribute);
    double getRelativeTimestamp(QDateTime initialPoint);
    QMap<QString, double> vehicleData;

private:
    QDateTime timestamp;
    QString rawBinary;
};
#endif // GRAPHDATAPOINT_H
