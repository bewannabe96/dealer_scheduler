#ifndef UICURRENTDEALERITEM_H
#define UICURRENTDEALERITEM_H

#include <QObject>
#include <QTreeWidgetItem>

#include "data_dealer.h"

class UICurrentDealerItem : public QObject, public QTreeWidgetItem
{
    Q_OBJECT

public:
    explicit UICurrentDealerItem(QTreeWidget *view, Dealer *dlr_ptr);

private:
    const QIcon DEALER_WORK_ICON;
    const QIcon DEALER_WAIT_ICON;

    // data
    Dealer *DEALER_PTR;

signals:

public slots:
    void updateCurrentWorkingStatus();
    void updateWorkingTime();
};

#endif // UICURRENTDEALERITEM_H
