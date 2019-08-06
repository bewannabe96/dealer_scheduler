#ifndef UINEWDEALERDIALOG_H
#define UINEWDEALERDIALOG_H

#include <QDialog>

#include "sys_var.h"

#include "data_dealer.h"

namespace Ui {
class UINewDealerDialog;
}

class UINewDealerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit UINewDealerDialog(QWidget *parent = 0);
    ~UINewDealerDialog();

    // getters for data
    sys_var::working_time getWorkingTime() const;
    QString getDealerName() const;
    dealer_grade getDealerGrade() const;

private:
    Ui::UINewDealerDialog *ui;

    // data
    sys_var::working_time workingTime;
    QString dealerName;
    dealer_grade dealerGrade;

public slots:
    void setDealerInfo();
};

#endif // UINEWDEALERDIALOG_H
