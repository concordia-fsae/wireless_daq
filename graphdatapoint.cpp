#include "graphdatapoint.h"
#include <QDateTime>

/*!
 * \brief GraphDataPoint::GraphDataPoint
 * \param rawBinary
 * \class GraphDataPoint
 *
 * The data format coming back from the TCP connection. It will take the raw binary that comes from the server and decode it into graph readable format.
 */
GraphDataPoint::GraphDataPoint(QString rawBinary)
{
    this->timestamp = QDateTime::currentDateTime();
    this->rawBinary = rawBinary;
    uint8_t formattedBinary[8];

    for(int i = 0; i < 8; i ++) {
        formattedBinary[i] = atoi(this->rawBinary.mid(i*8, 8).toLocal8Bit().constData());
    }

    /*
     * This logic was taken from another project (Steering Wheel). It takes binary and turns it into a readable format.
     * Ideally this logic would be in a DBC file but for now it's ok.
     * The data is placed into a MAP data structure for easier access in the 'getAttributeValue' function
    */
    vehicleData.insert("Gear", (formattedBinary[0] & 0b11110000 >> 4) - 2);
    vehicleData.insert("Launch", (formattedBinary[0] & 0b00001000) >> 3);
    vehicleData.insert("Traction", (formattedBinary[0] & 0b00000100) >> 2);
    vehicleData.insert("Autoshift", (formattedBinary[1] & 0b11110000) >> 4);
    vehicleData.insert("RPM", (formattedBinary[2] * 60));
    vehicleData.insert("Voltage", (formattedBinary[3] / 10.0));
    vehicleData.insert("F_Press", (formattedBinary[4] * 4));
    vehicleData.insert("O_Temp", (formattedBinary[5] * 4));
    vehicleData.insert("C_Temp", (formattedBinary[6] * 4));
    vehicleData.insert("O_Press", (formattedBinary[7] * 4));
}

double GraphDataPoint::getAttributeValue(QString attribute)
{
    return vehicleData[attribute];
}

double GraphDataPoint::getRelativeTimestamp(QDateTime initialPoint)
{
    return initialPoint.secsTo(this->timestamp) / 1.00;
}

QDateTime GraphDataPoint::getTimestamp() {
    return this->timestamp;
}

QString GraphDataPoint::getRawBinary() {
    return this->rawBinary;
}
