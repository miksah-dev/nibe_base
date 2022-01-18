#ifndef COMPAREDIALOG_H
#define COMPAREDIALOG_H

#include <QDialog>
#include <QDate>

namespace Ui {
class compareDialog;
}

class compareDialog : public QDialog
{
    Q_OBJECT

public:
    explicit compareDialog(QWidget *parent = nullptr);
    ~compareDialog();

    QStringList GetFilenames();

private slots:
    void on_compareButtonBox_accepted();
    void on_compareButtonBox_rejected();
    void on_calendarWidget_activated(const QDate &date);
    void on_OpenFile1_clicked();
    void on_OpenFile2_clicked();

    QString SelectFile();



private:
    Ui::compareDialog *dialogUi;

    QString file1;
    QString file2;
};

#endif // COMPAREDIALOG_H
