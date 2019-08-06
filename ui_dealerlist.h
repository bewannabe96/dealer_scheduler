#ifndef UIDEALERLIST_H
#define UIDEALERLIST_H

#include <QWidget>

#include <map>

#include "ui_dealeritem.h"

#include "container_dealer.h"

typedef std::map<Dealer*, UIDealerItem*> dealer_items_container;

namespace Ui {
class UIDealerList;
}

class UIDealerList : public QWidget
{
    Q_OBJECT

public:
    explicit UIDealerList(QWidget *parent, DealerContainer *dlr_cont_ptr);
    ~UIDealerList();

    Dealer* getSelectedDealer() const;

private:
    Ui::UIDealerList *ui;

    DealerContainer *DEALER_CONT_PTR;

    dealer_items_container items;

public slots:
    void addDelaerItem(Dealer *dlr_ptr);
    void removeDealerItem(Dealer *dlr_ptr);
};

#endif // UIDEALERLIST_H
