#include "ui_dealeritem.h"

UIDealerItem::UIDealerItem(QTreeWidget *view, Dealer *dlr_ptr) :
    QTreeWidgetItem(view), DEALER_PTR(dlr_ptr)
{
    setText(0, DEALER_PTR->getDealerName());
    setText(1, "G-"+QString::number(DEALER_PTR->getDealerGrade()));

    // data signal-slot connections
    connect(DEALER_PTR, &Dealer::destroyed, this, &UIDealerItem::deleteLater);
}

Dealer* UIDealerItem::getDealer() const { return DEALER_PTR; }
