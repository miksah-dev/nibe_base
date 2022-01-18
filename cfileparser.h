#ifndef CFILEPARSER_H
#define CFILEPARSER_H
#include "cgraphdata.h"

#include <QWidget>
#include <QVector>
#include <QString>

class CFileParser : public QWidget
{
    Q_OBJECT
public:
    explicit CFileParser(QWidget *parent = nullptr);

public:
    ~CFileParser();

    QVector<CGraphData*> ParseFile(QString fileName);
    QStringList SelectFile();



signals:


private:

    void ParseLine(QString line);

    QVector <CGraphData*> FileDataVector;
};

#endif // CFILEPARSER_H
