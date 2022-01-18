#include "comparedialog.h"
#include "ui_comparedialog.h"

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

void compareDialog::on_compareButtonBox_accepted()
{

}


void compareDialog::on_compareButtonBox_rejected()
{

}


void compareDialog::on_calendarWidget_activated(const QDate &date)
{

}

