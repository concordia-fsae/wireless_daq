#include "livedatagraph.h"

LiveDataGraph::LiveDataGraph(SocketConnection * socket, QObject *parent) : QObject(parent)
{
    this->graph =  new QCustomPlot;
    this->graph->addGraph();
    this->graph->graph(0)->rescaleAxes();
    this->graph->update();
    this->displayAttribute = "Select Attribute";

    //add title to graph
    QCPTextElement *graphTitle = new QCPTextElement(this->graph, "Live Graph", QFont("sans", 17, QFont::Bold));
    this->graph->plotLayout()->insertRow(0);
    this->graph->plotLayout()->addElement(0, 0, graphTitle);

    //adds dropdown element box
    QStringList commands = { "Select Attribute", "Speed", "RPM", "Breaking" };
    this->attributeListBox = new QComboBox();
    this->attributeListBox->addItems(commands);

    removeGraphButton = new QPushButton("Remove Graph");

    QObject::connect( this->attributeListBox, SIGNAL(currentTextChanged(QString)), this, SLOT(changeDisplayAttribute(QString)), Qt::AutoConnection);
    QObject::connect(socket, SIGNAL(newMessageFromServer(QString)), this, SLOT(handleNewMessageFromServer(QString)),Qt::AutoConnection);
    QObject::connect(this->removeGraphButton, SIGNAL(clicked()), this, SLOT(deleteGraph()));
}

void LiveDataGraph::handleNewMessageFromServer(QString message)
{
    QStringList splitString = message.split(",");
    QString xVal = splitString.first();
    QString yVal = splitString.last() == "" ? "0" : splitString.last();
    if(isANumber(xVal) && isANumber(yVal)) {
        addValueToGraph(xVal.toDouble(), yVal.toDouble());
    }
}

void LiveDataGraph::addValueToGraph(double xVal, double yVal)
{
    qv_x_file.append(xVal);
    qv_y_file.append(yVal);
    this->graph->graph(0)->setData(qv_x_file, qv_y_file);
    this->graph->xAxis->rescale(true);
    this->graph->yAxis->rescale(true);
    this->graph->replot();
    this->graph->update();
}

QVBoxLayout * LiveDataGraph::getGraphWidgetLayout()
{
    QHBoxLayout * buttonsLayout = new QHBoxLayout();
    buttonsLayout->addWidget(this->attributeListBox);
    buttonsLayout->addWidget(this->removeGraphButton);
    this->vLayout->addWidget(this->graph);
    this->vLayout->addLayout(buttonsLayout);
    return vLayout;
}

void LiveDataGraph::changeDisplayAttribute(QString newAttribute)
{
    this->displayAttribute = newAttribute;
}

void LiveDataGraph::deleteGraph()
{
    this->deleteLater();
    emit removeGraphFromLayout(this->getGraphWidgetLayout());
}

bool LiveDataGraph::isANumber(QString string)
{
    bool validate;
    string.toDouble(&validate);
    return validate;
}
