#include "ui_dealerlist.h"
#include "ui_ui_dealerlist.h"

UIDealerList::UIDealerList(QWidget *parent, DealerContainer *dlr_cont_ptr) :
    QWidget(parent),
    ui(new Ui::UIDealerList),
    DEALER_CONT_PTR(dlr_cont_ptr)
{
    ui->setupUi(this);

    // data signal-slot connections
    connect(DEALER_CONT_PTR, &DealerContainer::dealerAdded, this, &UIDealerList::addDelaerItem);
    connect(DEALER_CONT_PTR, &DealerContainer::dealerRemoved, this, &UIDealerList::removeDealerItem);
}

UIDealerList::~UIDealerList()
{
    delete ui;
}

Dealer* UIDealerList::getSelectedDealer() const
{
    UIDealerItem *current_item = dynamic_cast<UIDealerItem*>(ui->treeWidget->currentItem());
    return current_item->getDealer();
}

void UIDealerList::addDelaerItem(Dealer *dlr_ptr)
{
    // new dealer item
    items[dlr_ptr] = new UIDealerItem(ui->treeWidget, dlr_ptr);
    // adjust column width
    for(int col=0; col<ui->treeWidget->columnCount(); col++)
        ui->treeWidget->resizeColumnToContents(col);
}

void UIDealerList::removeDealerItem(Dealer *dlr_ptr)
{
    dealer_items_container::iterator search = items.find(dlr_ptr);
    if(search != items.end())
    {
        delete search->second;
        items.erase(search);
    }
}
