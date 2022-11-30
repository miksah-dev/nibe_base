#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "cfileparser.h"
#include "comparedialog.h"

#include <QMainWindow>
#include <QGraphicsView>
#include <QChart>
#include <qlineseries.h>
#include <QLineSeries>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_pushButton_clicked();
    void on_UseWaterCheckBox_stateChanged();
    void on_CircleWaterCheckBox_stateChanged();
    void on_RoomTempCheckBox_stateChanged();
    void on_WasteTempCheckBox_stateChanged();
    void on_OutsideTempCheckBox_stateChanged();
    void on_IntakeTempCheckBox_stateChanged();
    void on_dateEdit_userDateChanged(const QDate &date);
    void on_VaporTempCheckBox_stateChanged();
    void on_ElecCheckBox_stateChanged();
    void on_PriorityCheckbox_stateChanged();
    void on_SaveImageButton_clicked();

private:

    void drawGraph();
    void setUpAxis(QChart *chart);
    void setupSeries(QChart *chart);

    void clearDataSets();
    void setSingleFileDataSet(QVector<CGraphData*> data);
    void calculatePowerCon(QVector<CGraphData*> data);
    void setDayOneButtons(bool value);

    void SaveImage();
private:
    Ui::MainWindow *ui;

    compareDialog *cmpDialog;

    CFileParser parser;

    QChart *chart;

    // Graph series
    QLineSeries *CircleWaterInSeries;
    QLineSeries *CircleWaterOutSeries;
    QLineSeries *TempRoomSeries;
    QLineSeries *UseWaterUpSeries;
    QLineSeries *UseWaterDownSeries;
    QLineSeries *OutsideTempSeries;
    QLineSeries *WasteTempSeries;
    QLineSeries *IntakeTempSeries;
    QLineSeries *VaporTempSeries;
    QLineSeries *TotElecSeries;
    QLineSeries *PrioritySeries;
    QLineSeries *AlarmSeries;

    QLineSeries *TimeSeries;

    bool compareFiles;
};
#endif // MAINWINDOW_H
