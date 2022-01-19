#include "comparedialog.h"
#include "ui_comparedialog.h"

#include <QFileDialog>

compareDialog::compareDialog(QWidget *parent) :
    QDialog(parent),
    dialogUi(new Ui::compareDialog)
{
    dialogUi->setupUi(this);
}

compareDialog::~compareDialog()
{
    delete dialogUi;
}

QString compareDialog::SelectFile()
{
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::AnyFile);
    dialog.setNameFilter("All LOG files (*.LOG *.log)");
    dialog.setViewMode(QFileDialog::Detail);
    QStringList fileNames;

    if (dialog.exec())
    {
        fileNames = dialog.selectedFiles();
        return fileNames[0];
    }
    else
    {
        return "default";
    }
}


QStringList compareDialog::GetFilenames()
{
    return filenames;
}

void compareDialog::on_compareButtonBox_accepted()
{

}


void compareDialog::on_compareButtonBox_rejected()
{

}


void compareDialog::on_calendarWidget_activated(const QDate &date)
{

}

void compareDialog::on_OpenFile1_clicked()
{
    QString file = SelectFile();
    dialogUi->lineEdit->setText(file);
    if (file != "default")
        filenames[0] = file;
}


void compareDialog::on_OpenFile2_clicked()
{
    QString file = SelectFile();
    dialogUi->lineEdit_2->setText(file);
    if (file != "default")
        filenames[1] = file;
}


