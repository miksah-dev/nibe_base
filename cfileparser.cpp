#include "cfileparser.h"

#include <qdebug.h>
#include <QString>
#include <QStringList>
#include <QFileDialog>
#include <QFile>
#include <QRegularExpression>

CFileParser::CFileParser(QWidget *parent)
    : QWidget{parent}
{

}

void CFileParser::clear()
{
    FileDataVector.clear();
}

QVector<CGraphData*> CFileParser::ParseFile(QString fileName)
{

    QFile inputFile(fileName);
    if (inputFile.open(QIODevice::ReadOnly))
    {
       QTextStream in(&inputFile);
       // read two first lines away
       in.readLine();
       in.readLine();
       while (!in.atEnd())
       {
          QString line = in.readLine();
          ParseLine(line);

       }
       inputFile.close();
       return FileDataVector;
    }
    return FileDataVector;
}

void CFileParser::ParseLine(QString line)
{
    QStringList list;
    list = line.split(QRegularExpression("\\s+"));
    if (list.size() < 22)
    {
        printf("list size: %lli, returning", list.size());
        return;
    }
    CGraphData *dataItem = new(CGraphData);
    // Date
    QDate date = QDate::fromString(list[0],"yyyy-MM-dd");
    dataItem->setDate(date);
    // Time
    QTime time = QTime::fromString(list[1], "hh:mm:ss");
    dataItem->setTime(time);

    dataItem->setVersion(list[2].toInt());
    dataItem->setRversion(list[3].toInt());
    dataItem->setTempOut(list[4].toInt());
    dataItem->setCircleWaterIn(list[5].toInt());
    dataItem->setCircleWaterOut(list[6].toInt());
    dataItem->setUseWaterDown(list[7].toInt());
    dataItem->setUseWaterUp(list[8].toInt());
    dataItem->setTempVapor(list[9].toInt());
    dataItem->setbt18(list[10].toInt());
    dataItem->setbt19(list[11].toInt());
    dataItem->setbt20(list[12].toInt());
    dataItem->setTempWaste(list[13].toInt());
    dataItem->setTempIntake(list[14].toInt());
    dataItem->setTempRoom(list[15].toInt());
    dataItem->setElecConsump(list[16].toInt());
    dataItem->setAlarmNro(list[17].toInt());
    dataItem->setCalc_Supply(list[18].toInt());
    dataItem->setBt1Average(list[19].toInt());
    dataItem->setRelayBase(list[20].toInt());
    dataItem->setPriority(list[21].toInt());

    FileDataVector.append(dataItem);
}


QStringList CFileParser::SelectFile()
{
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::AnyFile);
    dialog.setNameFilter("All LOG files (*.LOG *.log)");
    dialog.setViewMode(QFileDialog::Detail);
    QStringList fileNames;
    if (dialog.exec())
    {
        fileNames = dialog.selectedFiles();
        return fileNames;
        }
    else
    {
        fileNames.append(("default"));
        return fileNames;
    }
}

CFileParser::~CFileParser()
{
    FileDataVector.clear();
}
