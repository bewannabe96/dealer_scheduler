#ifndef UIDEALERITEM_H
#define UIDEALERITEM_H

#include <QObject>
#include <QTreeWidgetItem>

#include "data_dealer.h"

class UIDealerItem : public QObject, public QTreeWidgetItem
{
    Q_OBJECT

public:
    explicit UIDealerItem(QTreeWidget *view, Dealer *dlr_ptr);

    Dealer* getDealer() const;

private:
    // data
    Dealer *DEALER_PTR;
};

#endif // UIDEALERITEM_H
