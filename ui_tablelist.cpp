#include "ui_tablelist.h"
#include "ui_ui_tablelist.h"

#include "ui_notableitem.h"

UITableList::UITableList(QWidget *parent, TableContainer *tbl_cont_ptr) :
    QWidget(parent),
    ui(new Ui::UITableList),
    TABLE_CONT_PTR(tbl_cont_ptr)
{
    ui->setupUi(this);

    // data signal-slot connections
    connect(TABLE_CONT_PTR, &TableContainer::tableAdded, this, &UITableList::addTableItem);
    connect(TABLE_CONT_PTR, &TableContainer::tableRemoved, this, &UITableList::removeTableItem);
}

UITableList::~UITableList()
{
    delete ui;
}

void UITableList::addTableItem(Table *tbl_ptr)
{
    QVBoxLayout *vblayout;
    switch(tbl_ptr->getGameType())
    {
    case ROULETTE:
        vblayout = ui->rouletteLayout;
        break;
    case BLACKJACK:
        vblayout = ui->blackjackLayout;
        break;
    case BACCARAT:
        vblayout = ui->baccaratLayout;
        break;
    }

    UITableItem *tbl_itm = new UITableItem(this, tbl_ptr);
    connect(tbl_itm, &UITableItem::removeButtonClicked, TABLE_CONT_PTR, &TableContainer::removeTable);
    vblayout->addWidget(tbl_itm);
    items[tbl_ptr] = tbl_itm;
}

void UITableList::removeTableItem(Table *tbl_ptr)
{
    QVBoxLayout *vblayout;
    switch(tbl_ptr->getGameType())
    {
    case ROULETTE:
        vblayout = ui->rouletteLayout;
        break;
    case BLACKJACK:
        vblayout = ui->blackjackLayout;
        break;
    case BACCARAT:
        vblayout = ui->baccaratLayout;
        break;
    }

    table_items_container::iterator search = items.find(tbl_ptr);
    if(search != items.end())
    {
        vblayout->removeWidget(search->second);
        items.erase(search);
    }
}
