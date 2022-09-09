#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "cfileparser.h"
#include "comparedialog.h"

#include <QMainWindow>
#include <QGraphicsView>
#include <QChart>
#include <QLineSeries.h>
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

    void onCompareDialogAccepted();
    void onCompareDialogRejected();

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
    void on_CompareDayOneCheckBox_stateChanged();
    void on_CompareDayTwoCheckBox_stateChanged();
    void on_UseWaterCheckBox_2_stateChanged();
    void on_CircleWaterCheckBox_2_stateChanged();
    void on_RoomTempCheckBox_2_stateChanged();
    void on_WasteTempCheckBox_2_stateChanged();
    void on_OutsideTempCheckBox_2_stateChanged();
    void on_compareButton_clicked();
    void on_SaveImageButton_clicked();

private:

    void drawGraph();
    void setUpAxis(QChart *chart);
    void setupSeries(QChart *chart);
    void hideComparelegends(QChart *chart);
    void clearDataSets();
    void handleCompare(QStringList files);

    void setSingleFileDataSet(QVector<CGraphData*> data);
    void setFirstCompareSet(QVector<CGraphData*> data);
    void setSecondCompareSet(QVector<CGraphData*> data);

    void setCompareButtonsVisibility(bool value);
    void setDayOneButtons(bool value);

    void SaveImage();
private:
    Ui::MainWindow *ui;

    compareDialog *cmpDialog;

    CFileParser parser;

    QChart *chart;

    // Graph series
    QLineSeries *CircleWaterInSeries = new QLineSeries();
    QLineSeries *CircleWaterOutSeries = new QLineSeries();
    QLineSeries *TempRoomSeries = new QLineSeries();
    QLineSeries *UseWaterUpSeries = new QLineSeries();
    QLineSeries *UseWaterDownSeries = new QLineSeries();
    QLineSeries *OutsideTempSeries = new QLineSeries();
    QLineSeries *WasteTempSeries = new QLineSeries();
    QLineSeries *IntakeTempSeries = new QLineSeries();
    QLineSeries *VaporTempSeries = new QLineSeries();
    QLineSeries *TotElecSeries = new QLineSeries();
    QLineSeries *PrioritySeries = new QLineSeries();

    QLineSeries *CircleWaterInSeries2 = new QLineSeries();
    QLineSeries *CircleWaterOutSeries2 = new QLineSeries();
    QLineSeries *TempRoomSeries2 = new QLineSeries();
    QLineSeries *UseWaterUpSeries2 = new QLineSeries();
    QLineSeries *UseWaterDownSeries2 = new QLineSeries();
    QLineSeries *OutsideTempSeries2 = new QLineSeries();
    QLineSeries *WasteTempSeries2 = new QLineSeries();
    QLineSeries *IntakeTempSeries2 = new QLineSeries();
    QLineSeries *VaporTempSeries2 = new QLineSeries();
    QLineSeries *TotElecSeries2 = new QLineSeries();
    QLineSeries *PrioritySeries2 = new QLineSeries();

    QLineSeries *TimeSeries = new QLineSeries();

    bool compareFiles;
};
#endif // MAINWINDOW_H
