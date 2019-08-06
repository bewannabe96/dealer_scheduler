#include "container_dealer.h"

#include "systemstatus.h"

DealerContainer::DealerContainer(QObject *parent, sys_var::working_time work_time) :
    QObject(parent), WORKING_TIME(work_time)
{
    data = new DealerContainerData();
}

const dealer_raw_container& DealerContainer::getRawContainer() const { return data->dealers; }

int DealerContainer::getSize() const
{
    return data->dealers.size();
}

Dealer* DealerContainer::searchDealer(const Dealer &compare)
{
    for(dealer_raw_container::iterator iter=data->dealers.begin();
        iter!=data->dealers.end(); iter++)
        if(**iter == compare)
            return *iter;
    return nullptr;
}

void DealerContainer::addDealer(sys_var::working_time work_time, const QString& name,
                                const dealer_grade grade, bool ignore_result)
{
    Dealer *new_dlr_ptr = new Dealer(work_time, name, grade);
    if(searchDealer(*new_dlr_ptr) != nullptr)
    {
        if(!ignore_result)
            SystemStatus::informDealerCreated(name);
        delete new_dlr_ptr;
        return;
    }
    new_dlr_ptr->setParent(this);
    data->dealers.push_back(new_dlr_ptr);
    emit dealerAdded(new_dlr_ptr);
    if(!ignore_result)
        SystemStatus::informDealerCreated(name);
}

void DealerContainer::removeDealer(const Dealer *dlr_ptr)
{
    if(!SystemStatus::confirmDealerDeletion(dlr_ptr->getDealerName()))
        return;
    for(dealer_raw_container::iterator iter=data->dealers.begin();
        iter!=data->dealers.end(); iter++)
        if((**iter) == *dlr_ptr)
        {
            data->dealers.erase(iter);
            emit dealerRemoved(*iter);
            return;
        }
    // dealer not found
}
