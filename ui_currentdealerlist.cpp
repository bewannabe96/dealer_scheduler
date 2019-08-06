#include "ui_currentdealerlist.h"
#include "ui_ui_currentdealerlist.h"

#include "ui_currentdealeritem.h"

UICurrentDealerList::UICurrentDealerList(
        QWidget *parent,
        DealerContainer *morning_dealers,
        DealerContainer *day_dealers,
        DealerContainer *night_dealers) :
    QWidget(parent),
    ui(new Ui::UICurrentDealerList), morningDealers(morning_dealers),
    dayDealers(day_dealers), nightDealers(night_dealers)
{
    ui->setupUi(this);

    // adjust column width
    for(int col=0; col<ui->treeWidget->columnCount(); col++)
        ui->treeWidget->resizeColumnToContents(col);

    // data signal-slot connections
    connect(morningDealers, &DealerContainer::dealerAdded, this, &UICurrentDealerList::addNewDealer);
    connect(dayDealers, &DealerContainer::dealerAdded, this, &UICurrentDealerList::addNewDealer);
    connect(nightDealers, &DealerContainer::dealerAdded, this, &UICurrentDealerList::addNewDealer);

    connect(morningDealers, &DealerContainer::dealerRemoved, this, &UICurrentDealerList::removeDealer);
    connect(dayDealers, &DealerContainer::dealerRemoved, this, &UICurrentDealerList::removeDealer);
    connect(nightDealers, &DealerContainer::dealerRemoved, this, &UICurrentDealerList::removeDealer);
}

UICurrentDealerList::~UICurrentDealerList()
{
    delete ui;
}

void UICurrentDealerList::switchWorkingTime(sys_var::working_time work_time)
{
    currentWorkingTime = work_time;

    DealerContainer *dealers;
    if(currentWorkingTime == sys_var::MORNING)
        dealers = morningDealers;
    else if(currentWorkingTime == sys_var::DAY)
        dealers = dayDealers;
    else // currentWorkingTime == sys_var::NIGHT
        dealers = nightDealers;

    ui->treeWidget->clear();
    const dealer_raw_container &raw_dealers = dealers->getRawContainer();
    for(dealer_raw_container::const_iterator iter=raw_dealers.begin();
        iter!=raw_dealers.end(); iter++)
        addDealer(*iter);
}

void UICurrentDealerList::addDealer(Dealer *dlr_ptr)
{
    // new current dealer item
    new UICurrentDealerItem(ui->treeWidget, dlr_ptr);
    // adjust column width
    for(int col=0; col<ui->treeWidget->columnCount(); col++)
        ui->treeWidget->resizeColumnToContents(col);
}

void UICurrentDealerList::addNewDealer(Dealer *dlr_ptr)
{
    if(dlr_ptr->getWorkingTime() == currentWorkingTime)
        addDealer(dlr_ptr);
}

void UICurrentDealerList::removeDealer(Dealer *dlr_ptr)
{
    if(dlr_ptr->getWorkingTime() == currentWorkingTime)
        switchWorkingTime(currentWorkingTime);
}
