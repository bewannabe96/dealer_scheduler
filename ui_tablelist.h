#ifndef UITABLELIST_H
#define UITABLELIST_H

#include <QWidget>

#include <map>

#include "ui_tableitem.h"
#include "ui_notableitem.h"

#include "container_table.h"

typedef std::map<Table*, UITableItem*> table_items_container;

namespace Ui {
class UITableList;
}

class UITableList : public QWidget
{
    Q_OBJECT

public:
    explicit UITableList(QWidget *parent, TableContainer *tbl_cont_ptr);
    ~UITableList();

private:
    Ui::UITableList *ui;

    TableContainer *TABLE_CONT_PTR;

    table_items_container items;

signals:

public slots:
    void addTableItem(Table *tbl_ptr);
    void removeTableItem(Table *tbl_ptr);
};

#endif // UITABLELIST_H
