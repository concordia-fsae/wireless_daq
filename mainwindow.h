#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    bool isANumber(QString string);

private slots:
    void on_loadFile_clicked();

private:
    Ui::MainWindow *ui;
    QVector<double> qv_x_file, qv_y_file;
};
#endif // MAINWINDOW_H
