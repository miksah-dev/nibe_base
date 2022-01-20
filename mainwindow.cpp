#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QChart>
#include <QSplineSeries>
#include <QDateTimeAxis>
#include <QCategoryAxis>
#include <QChartView>
#include <QValueAxis>
#include <QPointF>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->dateEdit->setDate(QDate::currentDate());

    // connect(ui->compareButton, &QPushButton::clicked, [this]() { onCompareButtonClicked(); });

    compareFiles = false;

    CircleWaterInSeries->setName("Circle Water In");
    CircleWaterOutSeries->setName("Circle Water Out");
    TempRoomSeries->setName("Room Temp");
    UseWaterUpSeries->setName("Water tank Up");
    UseWaterDownSeries->setName("Water tank Down");
    OutsideTempSeries->setName("Outside temp");
    WasteTempSeries->setName("Waste temp");
    IntakeTempSeries->setName("Intake Temp");
    VaporTempSeries->setName("Vapor temp");
    TotElecSeries->setName("total elec");
    PrioritySeries->setName("Priority");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    clearDataSets();
    QStringList files = parser.SelectFile();
    if (files[0] != "default")
    {
        compareFiles = false;
        QVector<CGraphData*> data = parser.ParseFile(files[0]);
        setSingleFileDataSet(data);
        drawGraph();
    }
}

void MainWindow::clearDataSets()
{
    // clear series for new data
    CircleWaterInSeries->clear();
    CircleWaterOutSeries->clear();
    TempRoomSeries->clear();
    UseWaterUpSeries->clear();
    UseWaterDownSeries->clear();
    OutsideTempSeries->clear();
    WasteTempSeries->clear();
    IntakeTempSeries->clear();
    VaporTempSeries->clear();
    TotElecSeries->clear();
    TimeSeries->clear();
    PrioritySeries->clear();

    CircleWaterInSeries2->clear();
    CircleWaterOutSeries2->clear();
    TempRoomSeries2->clear();
    UseWaterUpSeries2->clear();
    UseWaterDownSeries2->clear();
    OutsideTempSeries2->clear();
    WasteTempSeries2->clear();
    IntakeTempSeries2->clear();
    VaporTempSeries2->clear();
    TotElecSeries2->clear();
    PrioritySeries2->clear();
}

void MainWindow::drawGraph()
{

    QChart *chart = new QChart();

    setupSeries(chart);

    setUpAxis(chart);

    QString title = "Data from date: ";
    chart->setTitle(title);
    // title.append(data[0]->GetDate().toString())


    QMargins marg = chart->margins();
    marg.setLeft(40);
    chart->setMargins(marg);

    ui->BaseView->setChart(chart);
    ui->BaseView->setRenderHint(QPainter::Antialiasing);

    this->show();
}

void MainWindow::setUpAxis(QChart *chart)
{
    QDateTimeAxis *axisX = new QDateTimeAxis;
    axisX->setTickCount(10);
    axisX->setFormat("HH:MM");
    axisX->setTitleText("Time");
    chart->addAxis(axisX, Qt::AlignBottom);
    TimeSeries->attachAxis(axisX);
    TimeSeries->setVisible(false);

    QCategoryAxis *axisC = new QCategoryAxis;
    axisC->setMin(0);
    axisC->setMax(60);
    axisC->setStartValue(25);
    axisC->append("Idle/thawing", 20);
    axisC->append("Water", 30);
    axisC->append("Heating", 50);
    axisC->append("Transfer", 60);
    // chart->addAxis(axisC, Qt::AlignLeft);

    QValueAxis *axisY = new QValueAxis;
    axisY->setRange(-25, 60);
    axisY->setTickAnchor(0);
    axisY->setTickType(QValueAxis::TicksDynamic);
    axisY->setTickInterval(10);
    axisY->setLabelFormat("%.2f");
    axisY->setMax(60);
    axisY->setMin(-25);
    chart->addAxis(axisY, Qt::AlignRight);

    CircleWaterInSeries->attachAxis(axisY);
    CircleWaterOutSeries->attachAxis(axisY);
    TempRoomSeries->attachAxis(axisY);
    OutsideTempSeries->attachAxis(axisY);
    WasteTempSeries->attachAxis(axisY);
    UseWaterDownSeries->attachAxis(axisY);
    UseWaterUpSeries->attachAxis(axisY);
    IntakeTempSeries->attachAxis(axisY);
    VaporTempSeries->attachAxis(axisY);
    TotElecSeries->attachAxis(axisY);
    PrioritySeries->setPen(QPen(Qt::black, 3, Qt::DashDotLine, Qt::RoundCap, Qt::RoundJoin));
    PrioritySeries->attachAxis(axisY);
}

void MainWindow::setupSeries(QChart *chart)
{
    if (!compareFiles)
    {
        chart->addSeries(CircleWaterInSeries);
        chart->addSeries(CircleWaterOutSeries);
        chart->addSeries(TempRoomSeries);
        chart->addSeries(UseWaterDownSeries);
        chart->addSeries(UseWaterUpSeries);
        chart->addSeries(OutsideTempSeries);
        chart->addSeries(WasteTempSeries);
        chart->addSeries(IntakeTempSeries);
        chart->addSeries(VaporTempSeries);
        chart->addSeries(TotElecSeries);
        chart->addSeries(TimeSeries);
        chart->addSeries(PrioritySeries);
    }
}

void MainWindow::setSingleFileDataSet(QVector<CGraphData*> data)
{
    int ItemCount = data.count();

    ui->dateEdit->setDate(data[0]->getDate());

    // inser data to series
    for (int i = 0; i < ItemCount; i++)
    {
        QDateTime time;
        time.setTime(data[i]->getTime());

        CircleWaterInSeries->append(i, data[i]->getCircleWaterIn());
        CircleWaterOutSeries->append(i, data[i]->getCircleWaterOut());
        TempRoomSeries->append(i, data[i]->getTempRoom());
        UseWaterDownSeries->append(i, data[i]->getUseWaterDown());
        UseWaterUpSeries->append(i, data[i]->getUseWaterUp());
        OutsideTempSeries->append(i, data[i]->getTempOut());
        WasteTempSeries->append(i, data[i]->getTempWaste());
        IntakeTempSeries->append(i, data[i]->getTempIntake());
        VaporTempSeries->append(i, data[i]->getTempVapor());
        TotElecSeries->append(i, data[i]->getElecConsump());
        TimeSeries->append(time.toMSecsSinceEpoch(), i);
        PrioritySeries->append(i, data[i]->getPriority());
    }
}

void MainWindow::setFirstCompareSet(QVector<CGraphData*> data)
{
    int ItemCount = data.count();
    // inser data to series
    for (int i = 0; i < ItemCount; i++)
    {
        QDateTime time;
        time.setTime(data[i]->getTime());

        CircleWaterInSeries->append(i, data[i]->getCircleWaterIn());
        CircleWaterOutSeries->append(i, data[i]->getCircleWaterOut());
        TempRoomSeries->append(i, data[i]->getTempRoom());
        UseWaterDownSeries->append(i, data[i]->getUseWaterDown());
        UseWaterUpSeries->append(i, data[i]->getUseWaterUp());
        OutsideTempSeries->append(i, data[i]->getTempOut());
        WasteTempSeries->append(i, data[i]->getTempWaste());
        IntakeTempSeries->append(i, data[i]->getTempIntake());
        VaporTempSeries->append(i, data[i]->getTempVapor());
        TotElecSeries->append(i, data[i]->getElecConsump());
        TimeSeries->append(time.toMSecsSinceEpoch(), i);
        PrioritySeries->append(i, data[i]->getPriority());
    }
}

void MainWindow::setSecondCompareSet(QVector<CGraphData*> data)
{
    int ItemCount = data.count();
    // inser data to series
    for (int i = 0; i < ItemCount; i++)
    {
        QDateTime time;
        time.setTime(data[i]->getTime());

        CircleWaterInSeries2->append(i, data[i]->getCircleWaterIn());
        CircleWaterOutSeries2->append(i, data[i]->getCircleWaterOut());
        TempRoomSeries2->append(i, data[i]->getTempRoom());
        UseWaterDownSeries2->append(i, data[i]->getUseWaterDown());
        UseWaterUpSeries2->append(i, data[i]->getUseWaterUp());
        OutsideTempSeries2->append(i, data[i]->getTempOut());
        WasteTempSeries2->append(i, data[i]->getTempWaste());
        IntakeTempSeries2->append(i, data[i]->getTempIntake());
        VaporTempSeries2->append(i, data[i]->getTempVapor());
        TotElecSeries2->append(i, data[i]->getElecConsump());
        PrioritySeries2->append(i, data[i]->getPriority());
    }
}


/*
 * Handle checkboxes
 */
void MainWindow::on_UseWaterCheckBox_stateChanged()
{
        UseWaterUpSeries->setVisible(ui->UseWaterCheckBox->isChecked());
        UseWaterDownSeries->setVisible(ui->UseWaterCheckBox->isChecked());
 }


void MainWindow::on_CircleWaterCheckBox_stateChanged()
{

    CircleWaterInSeries->setVisible(ui->CircleWaterCheckBox->isChecked());
    CircleWaterOutSeries->setVisible(ui->CircleWaterCheckBox->isChecked());
}


void MainWindow::on_RoomTempCheckBox_stateChanged()
{
    TempRoomSeries->setVisible(ui->RoomTempCheckBox->isChecked());
}


void MainWindow::on_WasteTempCheckBox_stateChanged()
{
    WasteTempSeries->setVisible(ui->WasteTempCheckBox->isChecked());
}


void MainWindow::on_OutsideTempCheckBox_stateChanged()
{
    OutsideTempSeries->setVisible(ui->OutsideTempCheckBox->isChecked());
}


void MainWindow::on_IntakeTempCheckBox_stateChanged()
{
    IntakeTempSeries->setVisible(ui->IntakeTempCheckBox->isChecked());
}


void MainWindow::on_dateEdit_userDateChanged(const QDate &date)
{

}

void MainWindow::on_VaporTempCheckBox_stateChanged()
{
    VaporTempSeries->setVisible(ui->VaporTempCheckBox->isChecked());
}


void MainWindow::on_ElecCheckBox_stateChanged()
{
    TotElecSeries->setVisible(ui->ElecCheckBox->isChecked());
}


void MainWindow::on_PriorityCheckbox_stateChanged()
{
    PrioritySeries->setVisible(ui->PriorityCheckbox->isChecked());
}

void MainWindow::onCompareDialogAccepted()
{
    // QStringList fileList = cmpDialog->getFilenames();

    qDebug() << "MainWindow::onCompareDialogAccepted - filelist:";
}

void MainWindow::onCompareDialogRejected()
{
     qDebug() << "MainWindow::onCompareDialogRejected";
}



void MainWindow::on_compareButton_clicked()
{
    qDebug() << "MainWindow::onCompareButtonClicked " ;
    cmpDialog = new compareDialog(this);
    connect(cmpDialog, &compareDialog::compareDialogAccepted, this, &MainWindow::onCompareDialogAccepted);
    cmpDialog->show();
}

