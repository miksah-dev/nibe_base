#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QChart>
#include <QSplineSeries>
#include <QDateTimeAxis>
#include <QCategoryAxis>
#include <QChartView>
#include <QValueAxis>
#include <QPointF>
#include <QLegendMarker>
#include <QOpenGLWidget>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->dateEdit->setDate(QDate::currentDate());
    ui->dateEdit->setVisible(false);
    ui->SelectDateLabel->setVisible(false);

    CircleWaterInSeries = new QLineSeries();
    CircleWaterOutSeries = new QLineSeries();
    TempRoomSeries = new QLineSeries();
    UseWaterUpSeries = new QLineSeries();
    UseWaterDownSeries = new QLineSeries();
    OutsideTempSeries = new QLineSeries();
    WasteTempSeries = new QLineSeries();
    IntakeTempSeries = new QLineSeries();
    VaporTempSeries = new QLineSeries();
    TotElecSeries = new QLineSeries();
    PrioritySeries = new QLineSeries();
    AlarmSeries = new QLineSeries();;

    TimeSeries = new QLineSeries();

    // QVBoxLayout *layout = new QVBoxLayout(parent);

    chart = new QChart();

    ui->SaveImageButton->setVisible(false);

    CircleWaterInSeries->setName("Circle Water In");
    CircleWaterInSeries->setUseOpenGL(true);
    CircleWaterOutSeries->setName("Circle Water Out");
    CircleWaterOutSeries->setUseOpenGL(true);
    TempRoomSeries->setName("Room Temp");
    TempRoomSeries->setUseOpenGL(true);
    UseWaterUpSeries->setName("Water tank Up");
    UseWaterUpSeries->setUseOpenGL(true);
    UseWaterDownSeries->setName("Water tank Down");
    UseWaterDownSeries->setUseOpenGL(true);
    OutsideTempSeries->setName("Outside temp");
    OutsideTempSeries->setUseOpenGL(true);
    WasteTempSeries->setName("Waste temp");
    WasteTempSeries->setUseOpenGL(true);
    IntakeTempSeries->setName("Intake Temp");
    IntakeTempSeries->setUseOpenGL(true);
    VaporTempSeries->setName("Vapor temp");
    VaporTempSeries->setUseOpenGL(true);
    TotElecSeries->setName("total elec");
    TotElecSeries->setUseOpenGL(true);
    PrioritySeries->setName("Priority");
    PrioritySeries->setUseOpenGL(true);
    AlarmSeries->setName("Alarms");
    AlarmSeries->setUseOpenGL(true);
}

MainWindow::~MainWindow()
{
    delete ui;
    clearDataSets();
}

void MainWindow::on_pushButton_clicked()
{
    clearDataSets();
    QStringList files = parser.SelectFile();
    if (files[0] != "default")
    {
        compareFiles = false;
        QVector<CGraphData*> data;
        data.clear();
        data = parser.ParseFile(files[0]);
        if (data.size() > 0)
        {
        calculatePowerCon(data);
        setSingleFileDataSet(data);
        drawGraph();
        } else
        {
        printf("\nFile read ERROR: Nothing to print");
        }
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
    // AlarmSeries->clear();

    QList<QAbstractAxis *> axis = chart->axes();
    for (int i=0; i<axis.count(); i++)
    {
        chart->removeAxis(axis[i]);
    }

    QList<QAbstractSeries *> series = chart->series();
    for (int j=0; j>series.count(); j++)
    {
        chart->removeSeries(series[j]);
    }
}

void MainWindow::calculatePowerCon(QVector<CGraphData *> data)
{
    int ItemCount = data.count();

    double averagePower = 0;
    double usedPower = 0;
    int powercounts = 0;

    // time diff per line for consumption counting
    double diff = data[0]->getTime().secsTo(data[1]->getTime());

    // insert data to series
    for (int i = 0; i < ItemCount; i++)
    {
        if (data[i]->getElecConsump() > 0)
        {
            averagePower = averagePower + data[i]->getElecConsump();
            powercounts++;
        }
    }
    averagePower = averagePower/powercounts; // awerage power on logged cycles
    double hourDivider = 3600/diff; // ehat is the divider for hour based consumption
    usedPower = averagePower*(powercounts/hourDivider);
    QString powerStr = QString::number(usedPower);
    powerStr.append(" kWh");

    ui->PowerLabel->setText(powerStr);

    qDebug() << "MainWindow::calculatePowerCon - diff: " << diff;
    qDebug() << "MainWindow::calculatePowerCon - count: " << powercounts;
    qDebug() << "MainWindow::calculatePowerCon - aveage powwer, power kW/h:  , hour divider" << averagePower <<  usedPower << hourDivider;
}

void MainWindow::drawGraph()
{
    setupSeries(chart);

    setUpAxis(chart);

    QString title = "Data from date: ";
    title += ui->dateEdit->date().toString();
    chart->setTitle(title);

    QMargins marg = chart->margins();
    marg.setLeft(20);
    chart->setMargins(marg);

    ui->BaseView->setChart(chart);
    // ui->BaseView->setRenderHint(QPainter::Antialiasing);

    this->show();
    ui->SaveImageButton->setVisible(true);

    ui->BaseView->update();
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
    axisC->setLabelsPosition(QCategoryAxis::AxisLabelsPositionOnValue);
    axisC->setMin(0);
    axisC->setMax(60);
    axisC->setStartValue(0);
    axisC->append("Idle/thawing", 20);
    axisC->append("Water", 30);
    axisC->append("Heating", 50);
    axisC->append("Transfer", 60);
    chart->addAxis(axisC, Qt::AlignLeft);

    QValueAxis *axisY = new QValueAxis;
    axisY->setRange(-30, 65);
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
    // AlarmSeries->setPen(QPen(Qt::black, 3, Qt::DashDotLine, Qt::RoundCap, Qt::RoundJoin));
    // AlarmSeries->attachAxis(axisY);
}

void MainWindow::setupSeries(QChart *chart)
{
    qDebug() << "MainWindow::setupSeries ";
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
    // chart->addSeries(AlarmSeries);
}

void MainWindow::setSingleFileDataSet(QVector<CGraphData*> data)
{
    int ItemCount = data.count();

    ui->dateEdit->setDate(data[0]->getDate());

    // insert data to series
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
        // AlarmSeries->append(i, data[i]->getAlarmNro());
    }
}


void MainWindow::setDayOneButtons(bool value)
{
    ui->CircleWaterCheckBox->setEnabled(value);
    ui->UseWaterCheckBox->setEnabled(value);
    ui->ElecCheckBox->setEnabled(value);
    ui->IntakeTempCheckBox->setEnabled(value);
    ui->OutsideTempCheckBox->setEnabled(value);
    ui->PriorityCheckbox->setEnabled(value);
    ui->RoomTempCheckBox->setEnabled(value);
    ui->VaporTempCheckBox->setEnabled(value);
    ui->WasteTempCheckBox->setEnabled(value);
}

void MainWindow::SaveImage()
{
    qDebug() << "MainWindow::SaveImage" ;
    QPixmap p = ui->BaseView->grab();
    QOpenGLWidget *glWidget = ui->BaseView->findChild<QOpenGLWidget *>();
    if (glWidget) {
        QPainter painter(&p);
        QPoint d =
            glWidget->mapToGlobal(QPoint()) - ui->BaseView->mapToGlobal(QPoint());
        painter.setCompositionMode(QPainter::CompositionMode_SourceAtop);
        painter.drawImage(d, glWidget->grabFramebuffer());
        painter.end();
    }
    QString datestring = "/Users/mikasaha/Documents/Projects/Nibe/Logs/";
    datestring += ui->dateEdit->date().toString();
    datestring += ".png";
    if (p.save(datestring, "PNG"))
    {
        qDebug() << "Kuva tallennettu" ;
    }
    else
    {
        qDebug() << "Ei onnistunut" ;
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


void MainWindow::on_SaveImageButton_clicked()
{
    SaveImage();
}

