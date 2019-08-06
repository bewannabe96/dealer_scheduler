#include "ui_newdealerdialog.h"
#include "ui_ui_newdealerdialog.h"

#include "QMessageBox"

UINewDealerDialog::UINewDealerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UINewDealerDialog)
{
    ui->setupUi(this);

    // signal-slot connections
    // button box accepted -> set new dealer info
    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &UINewDealerDialog::setDealerInfo);
    // button box rejected -> reject
    connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &UINewDealerDialog::reject);
}

UINewDealerDialog::~UINewDealerDialog()
{
    delete ui;
}

sys_var::working_time UINewDealerDialog::getWorkingTime() const { return workingTime; }

QString UINewDealerDialog::getDealerName() const { return dealerName; }

dealer_grade UINewDealerDialog::getDealerGrade() const { return dealerGrade; }

void UINewDealerDialog::setDealerInfo()
{
    workingTime = ui->worktimeComboBox->currentIndex();
    dealerName = ui->nameLineEdit->text();
    dealerGrade= ui->gradeComboBox->currentIndex() + 1;
    if(dealerName == "")
    {
        QMessageBox msg_box(this);
        msg_box.setIcon(QMessageBox::Warning);
        msg_box.setText("이름이 입력되지 않았습니다.");
        msg_box.setInformativeText("다시 한번 확인하십시오.");
        msg_box.setStandardButtons(QMessageBox::Ok);
        msg_box.exec();
        return;
    }
    accept();
}

