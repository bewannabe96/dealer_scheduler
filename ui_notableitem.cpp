#include "ui_notableitem.h"
#include "ui_ui_notableitem.h"

UINoTableItem::UINoTableItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UINoTableItem)
{
    ui->setupUi(this);
}

UINoTableItem::~UINoTableItem()
{
    delete ui;
}
