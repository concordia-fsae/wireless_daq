#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QFileDialog>
#include <QDir>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->excelPlot->addGraph();
    ui->excelPlot->graph(0)->setScatterStyle(QCPScatterStyle::ssCircle);
    ui->excelPlot->graph(0)->rescaleAxes();
    ui->excelPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    ui->excelPlot->xAxis->setRange(0.0, 50);
    ui->excelPlot->yAxis->setRangeLower(0.0);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_loadFile_clicked()
{
    QString file_name = QFileDialog::getOpenFileName(this, "Open file", QDir::homePath());

    QFile file(file_name);
    if(!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, "title", "file not open");
    }

    QTextStream in(&file);
    while(!in.atEnd()) {
        QString mText = in.readLine();
        QStringList splitString = mText.split(",");
        QString xVal = splitString.first();
        QString yVal = splitString.last();
        if(isANumber(xVal) && isANumber(yVal)) {
            qv_x_file.append(xVal.toDouble());
            qv_y_file.append(yVal.toDouble());
        } else {
            ui->excelPlot->xAxis->setLabel(xVal);
            ui->excelPlot->yAxis->setLabel(yVal);
        }
    }
    ui->excelPlot->graph(0)->setData(qv_x_file, qv_y_file);
    ui->excelPlot->xAxis->rescale(true);
    ui->excelPlot->yAxis->rescale(true);
    ui->excelPlot->replot();
    ui->excelPlot->update();
}

bool MainWindow::isANumber(QString string)
{
    bool validate;
    string.toDouble(&validate);
    return validate;
}
