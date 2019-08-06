#ifndef UICURRENTDEALERLIST_H
#define UICURRENTDEALERLIST_H

#include <QWidget>

#include "sys_var.h"

#include "container_dealer.h"

namespace Ui {
class UICurrentDealerList;
}

class UICurrentDealerList : public QWidget
{
    Q_OBJECT

public:
    explicit UICurrentDealerList(
            QWidget *parent,
            DealerContainer *morning_dealers,
            DealerContainer *day_dealers,
            DealerContainer *night_dealers
            );
    ~UICurrentDealerList();

private:
    Ui::UICurrentDealerList *ui;

    sys_var::working_time currentWorkingTime;

    DealerContainer *morningDealers;
    DealerContainer *dayDealers;
    DealerContainer *nightDealers;

public slots:
    void switchWorkingTime(sys_var::working_time work_time);

    void addDealer(Dealer *dlr_ptr);
    void addNewDealer(Dealer *dlr_ptr);
    void removeDealer(Dealer *dlr_ptr);
};

#endif // UICURRENTDEALERLIST_H
