#include "livedatagraph.h"

/*!
  \class LiveDataGraph
  \brief The LiveDataGraph class displays live data coming from a TCP server in real time

  Live data graphs take a TCP socket as a pointer and displays the data coming from the server in real time.

  It handles:
  1. Adding the graph to the UI
  2. Changing the display depending on the attribute wanted (gear, launch, etc)
  3. Ability to delete the graph
 */
LiveDataGraph::LiveDataGraph(SocketConnection * socket, QObject *parent) : QObject(parent)
{
    // Basic setup of the live graph
    this->socket = socket;
    this->graph =  new QCustomPlot;
    this->graph->addGraph();
    this->graph->graph(0)->rescaleAxes();
    this->graph->update();
    this->displayAttribute = "Select Attribute";

    // Add title to graph
    QCPTextElement *graphTitle = new QCPTextElement(this->graph, "Live Graph", QFont("sans", 17, QFont::Bold));
    this->graph->plotLayout()->insertRow(0);
    this->graph->plotLayout()->addElement(0, 0, graphTitle);

    // Adds dropdown element box
    QStringList commands = { "Select_Attribute", "Gear", "Launch", "Traction", "Autoshift", "RPM", "Voltage", "F_Press", "O_Temp", "C_Temp", "O_Press" };
    this->attributeListBox = new QComboBox();
    this->attributeListBox->addItems(commands);

    // Adds the 'remove graph' button
    removeGraphButton = new QPushButton("Remove Graph");

    //  --- Event Listeners ---

    // Listens for when if a different attribute was selected in the dropdown
    QObject::connect( this->attributeListBox, SIGNAL(currentTextChanged(QString)), this, SLOT(changeDisplayAttribute(QString)), Qt::AutoConnection);

    // Listens for a new message from the TCP server
    QObject::connect(socket, SIGNAL(newGraphPointFromServer(GraphDataPoint)), this, SLOT(handleNewDataPointFromServer(GraphDataPoint)),Qt::AutoConnection);

    // Listens for if the remove graph button was clicked
    QObject::connect(this->removeGraphButton, SIGNAL(clicked()), this, SLOT(deleteGraph()));
}

/*!
 * \brief LiveDataGraph::handleNewDataPointFromServer
 * \param newDataPoint
 *
 * Takes in a new data point from the server and decodes it to graph viewable values depending on the attribute selected
 */
void LiveDataGraph::handleNewDataPointFromServer(GraphDataPoint newDataPoint)
{
    QDateTime initialTimeValue = this->socket->GetInitialDataPoint().getTimestamp();

    // decodes the new data point that comes from the server
    double relativeTimeValue = newDataPoint.getRelativeTimestamp(initialTimeValue);
    double decodedBinaryValue = newDataPoint.getAttributeValue(this->displayAttribute);

    // adds decoded values to graph
    addValueToGraph(relativeTimeValue, decodedBinaryValue);
}

/*!
 * \brief LiveDataGraph::addValueToGraph
 * \param xVal xvalue of the graph
 * \param yVal yvalue of the graph
 *
 * Adds points to the graph
 */
void LiveDataGraph::addValueToGraph(double xVal, double yVal)
{
    qv_x_file.append(xVal);
    qv_y_file.append(yVal);
    this->updateGraph();
}

/*!
 * \brief LiveDataGraph::updateGraph
 *
 * Updates the graph when data points are added / removed and rescales the graph
 */
void LiveDataGraph::updateGraph()
{
    this->graph->graph(0)->setData(qv_x_file, qv_y_file);
    this->graph->xAxis->rescale(true);
    this->graph->yAxis->rescale(true);
    this->graph->replot();
    this->graph->update();
}

/*!
 * \brief LiveDataGraph::getGraphWidgetLayout
 * \return The UI elements to display regarding the live graph
 */
QVBoxLayout * LiveDataGraph::getGraphWidgetLayout()
{
    QHBoxLayout * buttonsLayout = new QHBoxLayout();
    buttonsLayout->addWidget(this->attributeListBox);
    buttonsLayout->addWidget(this->removeGraphButton);
    this->vLayout->addWidget(this->graph);
    this->vLayout->addLayout(buttonsLayout);
    return vLayout;
}

/*!
 * \brief LiveDataGraph::changeDisplayAttribute
 * \param newAttribute the new attribute that was selected
 *
 * When a different attribute is selected, it will clear the graph and re-add all the points with the newly selected attribute
 */
void LiveDataGraph::changeDisplayAttribute(QString newAttribute)
{
    // Clears all the data points from the graph
    qv_x_file.clear();
    qv_y_file.clear();
    this->updateGraph();
    QVector<GraphDataPoint> allExistingData = this->socket->GetAllServerData();

    QDateTime firstTimePoint = this->socket->GetInitialDataPoint().getTimestamp();

    // Adds all the data points for the new attribute selected
    for(GraphDataPoint point: allExistingData) {
        double relativeTimeValue = point.getRelativeTimestamp(firstTimePoint);
        double decodedBinaryValue = point.getAttributeValue(newAttribute);
        qv_x_file.insert(qv_x_file.begin(), relativeTimeValue);
        qv_y_file.insert(qv_y_file.begin(), decodedBinaryValue);
    }
    this->updateGraph();
    this->displayAttribute = newAttribute;
}

/*!
 * \brief LiveDataGraph::deleteGraph
 *
 * Removes the graph from the UI
 */
void LiveDataGraph::deleteGraph()
{
    this->deleteLater();
    emit removeGraphFromLayout(this->getGraphWidgetLayout());
}

//! Utility function
bool LiveDataGraph::isANumber(QString string)
{
    bool validate;
    string.toDouble(&validate);
    return validate;
}
