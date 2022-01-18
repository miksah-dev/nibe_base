#ifndef COMPAREDIALOG_H
#define COMPAREDIALOG_H

#include <QDialog>

namespace Ui {
class compareDialog;
}

class compareDialog : public QDialog
{
    Q_OBJECT

public:
    explicit compareDialog(QWidget *parent = nullptr);
    ~compareDialog();

private slots:
    void on_compareButtonBox_accepted();

    void on_compareButtonBox_rejected();

    void on_calendarWidget_activated(const QDate &date);

private:
    Ui::compareDialog *dialogUi;
};

#endif // COMPAREDIALOG_H
