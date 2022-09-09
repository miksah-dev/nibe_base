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

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->dateEdit->setDate(QDate::currentDate());

    chart = new QChart();

    compareFiles = false;
    ui->CompareDayOneCheckBox->setVisible(false);
    ui->CompareDayTwoCheckBox->setVisible(false);
    ui->SaveImageButton->setVisible(false);

    setCompareButtonsVisibility(false);

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

    CircleWaterInSeries2->setUseOpenGL(true);
    CircleWaterOutSeries2->setUseOpenGL(true);
    TempRoomSeries2->setUseOpenGL(true);
    UseWaterUpSeries2->setUseOpenGL(true);
    UseWaterDownSeries2->setUseOpenGL(true);
    OutsideTempSeries2->setUseOpenGL(true);
    WasteTempSeries2->setUseOpenGL(true);
    IntakeTempSeries2->setUseOpenGL(true);
    VaporTempSeries2->setUseOpenGL(true);
    TotElecSeries2->setUseOpenGL(true);
    PrioritySeries2->setUseOpenGL(true);
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

    QList<QAbstractAxis *> axis = chart->axes();
    for (int i=0; i<axis.count(); i++)
    {
        chart->removeAxis(axis[i]);
    }

    chart->removeAllSeries();
}

void MainWindow::drawGraph()
{
    // chart->hide();


    setupSeries(chart);

    setUpAxis(chart);

    QString title = "Data from date: ";
    title += ui->dateEdit->date().toString();
    chart->setTitle(title);

    QMargins marg = chart->margins();
    marg.setLeft(40);
    chart->setMargins(marg);

    ui->BaseView->setChart(chart);
    // ui->BaseView->setRenderHint(QPainter::Antialiasing);

    this->show();
    ui->SaveImageButton->setVisible(true);
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
    if (compareFiles)
    {
        CircleWaterInSeries2->attachAxis(axisY);
        CircleWaterOutSeries2->attachAxis(axisY);
        TempRoomSeries2->attachAxis(axisY);
        OutsideTempSeries2->attachAxis(axisY);
        WasteTempSeries2->attachAxis(axisY);
        UseWaterDownSeries2->attachAxis(axisY);
        UseWaterUpSeries2->attachAxis(axisY);
        IntakeTempSeries2->attachAxis(axisY);
        VaporTempSeries2->attachAxis(axisY);
        TotElecSeries2->attachAxis(axisY);
        PrioritySeries2->setPen(QPen(Qt::black, 2, Qt::DashDotLine, Qt::RoundCap, Qt::RoundJoin));
        PrioritySeries2->attachAxis(axisY);

        CircleWaterInSeries2->setPen(CircleWaterInSeries->pen());
        CircleWaterOutSeries2->setPen(CircleWaterOutSeries->pen());
        TempRoomSeries2->setPen(TempRoomSeries->pen());
        OutsideTempSeries2->setPen(OutsideTempSeries->pen());
        WasteTempSeries2->setPen(WasteTempSeries->pen());
        UseWaterDownSeries2->setPen(UseWaterDownSeries->pen());
        UseWaterUpSeries2->setPen(UseWaterUpSeries->pen());
        IntakeTempSeries2->setPen(IntakeTempSeries->pen());
        VaporTempSeries2->setPen(VaporTempSeries->pen());
        TotElecSeries2->setPen(TotElecSeries->pen());
        PrioritySeries2->setPen(QPen(Qt::black, 1, Qt::DashDotLine, Qt::RoundCap, Qt::RoundJoin));

        hideComparelegends(chart);

    }
}

void MainWindow::hideComparelegends(QChart *chart)
{
    auto markersList = chart->legend()->markers();
    int i = markersList.count();
    for (int j = 12; j<i ; j++)
    {
        markersList[j]->setVisible(false);
    }
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
    if (compareFiles)
    {
        qDebug() << "MainWindow::setupSeries - compare";
        chart->addSeries(CircleWaterInSeries2);
        chart->addSeries(CircleWaterOutSeries2);
        chart->addSeries(TempRoomSeries2);
        chart->addSeries(UseWaterDownSeries2);
        chart->addSeries(UseWaterUpSeries2);
        chart->addSeries(OutsideTempSeries2);
        chart->addSeries(WasteTempSeries2);
        chart->addSeries(IntakeTempSeries2);
        chart->addSeries(VaporTempSeries2);
        chart->addSeries(TotElecSeries2);
        chart->addSeries(PrioritySeries2);
    }
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
    }
}

void MainWindow::setFirstCompareSet(QVector<CGraphData*> data)
{
    qDebug() << "MainWindow::setFirstCompareSet ";
    int ItemCount = data.count();
    qDebug() << "MainWindow::setFirstCompareSet - data count " << ItemCount;
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
    }
}

void MainWindow::setSecondCompareSet(QVector<CGraphData*> data)
{
    qDebug() << "MainWindow::setSecondCompareSet ";
    int ItemCount = data.count();
    qDebug() << "MainWindow::setSecondCompareSet - data count " << ItemCount;
    // insert data to series
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


void MainWindow::onCompareDialogAccepted()
{
    qDebug() << "MainWindow::onCompareDialogAccepted ";
    QStringList fileList = cmpDialog->getFilenames();
    delete cmpDialog;
    qDebug() << "MainWindow::onCompareDialogAccepted - filelist:" << fileList;
    compareFiles = true;
    setCompareButtonsVisibility(true);

    ui->CompareDayOneCheckBox->setVisible(true);
    ui->CompareDayTwoCheckBox->setVisible(true);

    handleCompare(fileList);

}

void MainWindow::onCompareDialogRejected()
{
     qDebug() << "MainWindow::onCompareDialogRejected";
}

void MainWindow::on_compareButton_clicked()
{
    qDebug() << "MainWindow::on_compareButton_clicked ";
    cmpDialog = new compareDialog(this);
    connect(cmpDialog, &compareDialog::compareDialogAccepted, this, &MainWindow::onCompareDialogAccepted);
    cmpDialog->show();
}

void MainWindow::handleCompare(QStringList files)
{
    qDebug() << "MainWindow::handleCompare " ;

    clearDataSets();

    QVector<CGraphData*> data = parser.ParseFile(files[0]);
    qDebug() << "MainWindow::handleCompare - first file parsed ";
    setFirstCompareSet(data);
    ui->CompareDayOneCheckBox->setText(data[0]->getDate().toString());
    data.clear();
    data = parser.ParseFile(files[1]);
    qDebug() << "MainWindow::handleCompare - second file parsed ";
    setSecondCompareSet(data);
    ui->CompareDayTwoCheckBox->setText(data[0]->getDate().toString());
    drawGraph();
}

void MainWindow::setCompareButtonsVisibility(bool value)
{
    ui->CircleWaterCheckBox_2->setVisible(value);
    ui->ElecCheckBox_2->setVisible(value);
    ui->IntakeTempCheckBox_2->setVisible(value);
    ui->OutsideTempCheckBox_2->setVisible(value);
    ui->PriorityCheckbox_2->setVisible(value);
    ui->RoomTempCheckBox_2->setVisible(value);
    ui->UseWaterCheckBox_2->setVisible(value);
    ui->VaporTempCheckBox_2->setVisible(value);
    ui->WasteTempCheckBox_2->setVisible(value);
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

void MainWindow::on_CompareDayOneCheckBox_stateChanged()
{

    setDayOneButtons(ui->CompareDayOneCheckBox->isChecked());
    UseWaterUpSeries->setVisible(ui->CompareDayOneCheckBox->isChecked());
    UseWaterDownSeries->setVisible(ui->CompareDayOneCheckBox->isChecked());
    CircleWaterInSeries->setVisible(ui->CompareDayOneCheckBox->isChecked());
    CircleWaterOutSeries->setVisible(ui->CompareDayOneCheckBox->isChecked());
    TempRoomSeries->setVisible(ui->CompareDayOneCheckBox->isChecked());
    WasteTempSeries->setVisible(ui->CompareDayOneCheckBox->isChecked());
    OutsideTempSeries->setVisible(ui->CompareDayOneCheckBox->isChecked());
    IntakeTempSeries->setVisible(ui->CompareDayOneCheckBox->isChecked());
    VaporTempSeries->setVisible(ui->CompareDayOneCheckBox->isChecked());
    TotElecSeries->setVisible(ui->CompareDayOneCheckBox->isChecked());
    PrioritySeries->setVisible(ui->CompareDayOneCheckBox->isChecked());
}


void MainWindow::on_CompareDayTwoCheckBox_stateChanged()
{
    UseWaterUpSeries2->setVisible(ui->CompareDayTwoCheckBox->isChecked());
    UseWaterDownSeries2->setVisible(ui->CompareDayTwoCheckBox->isChecked());
    CircleWaterInSeries2->setVisible(ui->CompareDayTwoCheckBox->isChecked());
    CircleWaterOutSeries2->setVisible(ui->CompareDayTwoCheckBox->isChecked());
    TempRoomSeries2->setVisible(ui->CompareDayTwoCheckBox->isChecked());
    WasteTempSeries2->setVisible(ui->CompareDayTwoCheckBox->isChecked());
    OutsideTempSeries2->setVisible(ui->CompareDayTwoCheckBox->isChecked());
    IntakeTempSeries2->setVisible(ui->CompareDayTwoCheckBox->isChecked());
    VaporTempSeries2->setVisible(ui->CompareDayTwoCheckBox->isChecked());
    TotElecSeries2->setVisible(ui->CompareDayTwoCheckBox->isChecked());
    PrioritySeries2->setVisible(ui->CompareDayTwoCheckBox->isChecked());

    setCompareButtonsVisibility(ui->CompareDayTwoCheckBox->isChecked());

    // if (!ui->CompareDayTwoCheckBox->isChecked())
        // hideComparelegends();

}


void MainWindow::on_UseWaterCheckBox_2_stateChanged()
{
    UseWaterUpSeries2->setVisible(ui->UseWaterCheckBox_2->isChecked());
    UseWaterDownSeries2->setVisible(ui->UseWaterCheckBox_2->isChecked());
}


void MainWindow::on_CircleWaterCheckBox_2_stateChanged()
{
    CircleWaterInSeries2->setVisible(ui->CircleWaterCheckBox_2->isChecked());
    CircleWaterOutSeries2->setVisible(ui->CircleWaterCheckBox_2->isChecked());
}


void MainWindow::on_RoomTempCheckBox_2_stateChanged()
{
    TempRoomSeries2->setVisible(ui->RoomTempCheckBox_2->isChecked());
}


void MainWindow::on_WasteTempCheckBox_2_stateChanged()
{
    WasteTempSeries2->setVisible(ui->WasteTempCheckBox_2->isChecked());
}


void MainWindow::on_OutsideTempCheckBox_2_stateChanged()
{
    OutsideTempSeries2->setVisible(ui->OutsideTempCheckBox_2->isChecked());
}


void MainWindow::on_SaveImageButton_clicked()
{
    SaveImage();
}

