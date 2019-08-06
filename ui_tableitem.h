#ifndef UITABLEITEM_H
#define UITABLEITEM_H

#include <QWidget>

#include "data_table.h"
#include "data_dealer.h"

namespace Ui {
class UITableItem;
}

class UITableItem : public QWidget
{
    Q_OBJECT

public:
    explicit UITableItem(QWidget *parent, Table *tbl_ptr);

    Table* getTable() const;

private:
    Ui::UITableItem *ui;

    // data
    Table *TABLE_PTR;

signals:
    void removeButtonClicked(Table *tbl_ptr);

public slots:
    void requestTableRemove();

    void setCurrentDealer(Dealer *dlr_ptr);
    void setNextDealer(Dealer *dlr_ptr);
    void setNextNextDealer(Dealer *dlr_ptr);
};

#endif // UITABLEITEM_H
