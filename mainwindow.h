#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "cfileparser.h"
#include "comparedialog.h"

#include <QMainWindow>
#include <QGraphicsView>
#include <QChart>
#include <qsplineseries.h>
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

    void drawGraph();
    void SetUpAxis(QChart *chart);
    void SetupSeries(QChart *chart);
    void ClearDataSets();

    void SetSingleFileDataSet(QVector<CGraphData*> data);

    void SetFirstCompareSet(QVector<CGraphData*> data);
    void SetSecondCompareSet(QVector<CGraphData*> data);

    void on_compareButton_clicked();


private:
    Ui::MainWindow *ui;

    compareDialog *cmpDialog;

    CFileParser parser;

    // temp_vapor, bt18, bt19, bt20, temp_waste, temp_in, temp_room, tot_elec, alarmsnro, calc_supply, bt1_avg, relay_base, prio

    // Graph series
    QSplineSeries *CircleWaterInSeries = new QSplineSeries();
    QSplineSeries *CircleWaterOutSeries = new QSplineSeries();
    QSplineSeries *TempRoomSeries = new QSplineSeries();
    QSplineSeries *UseWaterUpSeries = new QSplineSeries();
    QSplineSeries *UseWaterDownSeries = new QSplineSeries();
    QSplineSeries *OutsideTempSeries = new QSplineSeries();
    QSplineSeries *WasteTempSeries = new QSplineSeries();
    QSplineSeries *IntakeTempSeries = new QSplineSeries();
    QSplineSeries *VaporTempSeries = new QSplineSeries();
    QSplineSeries *TotElecSeries = new QSplineSeries();
    QLineSeries *PrioritySeries = new QLineSeries();

    QSplineSeries *CircleWaterInSeries2 = new QSplineSeries();
    QSplineSeries *CircleWaterOutSeries2 = new QSplineSeries();
    QSplineSeries *TempRoomSeries2 = new QSplineSeries();
    QSplineSeries *UseWaterUpSeries2 = new QSplineSeries();
    QSplineSeries *UseWaterDownSeries2 = new QSplineSeries();
    QSplineSeries *OutsideTempSeries2 = new QSplineSeries();
    QSplineSeries *WasteTempSeries2 = new QSplineSeries();
    QSplineSeries *IntakeTempSeries2 = new QSplineSeries();
    QSplineSeries *VaporTempSeries2 = new QSplineSeries();
    QSplineSeries *TotElecSeries2 = new QSplineSeries();
    QLineSeries *PrioritySeries2 = new QLineSeries();

    QSplineSeries *TimeSeries = new QSplineSeries();

    bool compareFiles;
};
#endif // MAINWINDOW_H
