#include "ui_currentdealeritem.h"

UICurrentDealerItem::UICurrentDealerItem(QTreeWidget *view, Dealer *dlr_ptr) :
    QTreeWidgetItem(view),
    DEALER_WORK_ICON(":/status/src/dealer_work"),
    DEALER_WAIT_ICON(":/status/src/dealer_wait"),
    DEALER_PTR(dlr_ptr)
{
    setText(1, DEALER_PTR->getDealerName());
    setText(2, "G-"+QString::number(DEALER_PTR->getDealerGrade()));
    updateCurrentWorkingStatus();
    updateWorkingTime();

    // data signal-slot connections
    connect(DEALER_PTR, &Dealer::currentWorkingStatusChanged,
            this, &UICurrentDealerItem::updateCurrentWorkingStatus);
    connect(DEALER_PTR, &Dealer::overallWorktimeChanged,
            this, &UICurrentDealerItem::updateWorkingTime);
}

void UICurrentDealerItem::updateCurrentWorkingStatus()
{
    if(DEALER_PTR->isOnCurrentWork())
        setIcon(0, DEALER_WORK_ICON);
    else
        setIcon(0, DEALER_WAIT_ICON);
}

void UICurrentDealerItem::updateWorkingTime()
{
    int secs = DEALER_PTR->getOverallWorktime();
    setText(3, QString::number(secs/60) + "분");
}
