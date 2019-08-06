#include "ui_newtabledialog.h"
#include "ui_ui_newtabledialog.h"

UINewTableDialog::UINewTableDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UINewTableDialog)
{
    ui->setupUi(this);

    // signal-slot connections
    // button box accepted -> set new table info
    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &UINewTableDialog::setTableInfo);
    // button box accepted -> accept
    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &UINewTableDialog::accept);
    // button box rejected -> reject
    connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &UINewTableDialog::reject);
}

UINewTableDialog::~UINewTableDialog()
{
    delete ui;
}

int UINewTableDialog::getGameType() const { return gameType; }

int UINewTableDialog::getTableNo() const { return tableNo; }

void UINewTableDialog::setTableInfo()
{
    gameType = ui->gametypeComboBox->currentIndex() + 1;
    tableNo = ui->tablenoSpinBox->value();
}
