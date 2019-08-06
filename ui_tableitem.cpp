#include "ui_tableitem.h"
#include "ui_ui_tableitem.h"

#include <QMessageBox>

UITableItem::UITableItem(QWidget *parent, Table *tbl_ptr) :
    QWidget(parent), ui(new Ui::UITableItem), TABLE_PTR(tbl_ptr)
{
    ui->setupUi(this);

    ui->nameLabel->setText(TABLE_PTR->getTableName());

    // data signal-slot connections
    connect(tbl_ptr, &Table::currentDealerArranged, this, &UITableItem::setCurrentDealer);
    connect(tbl_ptr, &Table::nextDealerArranged, this, &UITableItem::setNextDealer);
    connect(tbl_ptr, &Table::nextnextDealerArranged, this, &UITableItem::setNextNextDealer);

    // gui signal_slot connections
    connect(ui->removeButton, &QPushButton::clicked, this, &UITableItem::requestTableRemove);
}

Table* UITableItem::getTable() const { return TABLE_PTR; }

void UITableItem::requestTableRemove()
{
    QMessageBox msg_box(this);
    msg_box.setIcon(QMessageBox::Warning);
    msg_box.setText("\'" + TABLE_PTR->getTableName() + "\'"
                   + " 테이블을 제거하시겠습니까?");
    msg_box.setStandardButtons(QMessageBox::Ok|QMessageBox::Cancel);
    if(msg_box.exec() == QMessageBox::Ok)
        emit removeButtonClicked(TABLE_PTR);
}

void UITableItem::setCurrentDealer(Dealer *dlr_ptr)
{
    if(dlr_ptr == nullptr)
        ui->currentLabel->setText("배정된 딜러 없음");
    else
        ui->currentLabel->setText(dlr_ptr->getDealerName());
}

void UITableItem::setNextDealer(Dealer *dlr_ptr)
{
    if(dlr_ptr == nullptr)
        ui->nextLabel->setText("배정된 딜러 없음");
    else
        ui->nextLabel->setText(dlr_ptr->getDealerName());
}

void UITableItem::setNextNextDealer(Dealer *dlr_ptr)
{
    if(dlr_ptr == nullptr)
        ui->nextnextLabel->setText("배정된 딜러 없음");
    else
        ui->nextnextLabel->setText(dlr_ptr->getDealerName());
}
