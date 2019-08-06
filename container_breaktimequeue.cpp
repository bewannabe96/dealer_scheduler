#include "container_breaktimequeue.h"

#include <QDateTime>

#include <algorithm>

BreaktimeQueueData::BreaktimeQueueData() :
    currentWorkingDealers(nullptr)
{}

BreaktimeQueue::BreaktimeQueue(
        QObject *parent,
        DealerContainer *morning_dealers,
        DealerContainer *day_dealers,
        DealerContainer *night_dealers) :
    QObject(parent), morningDealers(morning_dealers),
    dayDealers(day_dealers), nightDealers(night_dealers)
{
    data = new BreaktimeQueueData();
}

Dealer* BreaktimeQueue::popDealerFromCurrentBreaktimeQueue()
{
    const dealer_raw_container &raw_dealers = data->currentWorkingDealers->getRawContainer();
    dealer_raw_container copied_dealers;
    std::copy_if(raw_dealers.begin(), raw_dealers.end(),
                 std::back_inserter(copied_dealers),
                 std::not1(std::mem_fun(&Dealer::isOnCurrentWork)));
    if(copied_dealers.size() == 0)
        return nullptr;
    dealer_raw_container::iterator rtn_iter
            = std::min_element(copied_dealers.begin(), copied_dealers.end(), DealerPriority());
    return *rtn_iter;
}

Dealer* BreaktimeQueue::popDealerFromNextBreaktimeQueue(
        QDateTime next_arrangement_time, Dealer *exclude_dealer)
{
    Dealer *rtn_dlr = nullptr;
    const dealer_raw_container &raw_dealers = data->nextWorkingDealers->getRawContainer();
    dealer_raw_container copied_dealers;
    std::copy_if(raw_dealers.begin(), raw_dealers.end(),
                 std::back_inserter(copied_dealers),
                 std::not1(std::mem_fun(&Dealer::isOnNextWork)));
    do
    {
        if(copied_dealers.size() == 0)
            return nullptr;
        dealer_raw_container::iterator rtn_iter
                = std::min_element(copied_dealers.begin(), copied_dealers.end(),
                                   DealerPriority(NEXT_QUEUE_TIME, next_arrangement_time));
        rtn_dlr = *rtn_iter;
        copied_dealers.erase(rtn_iter);
    } while(*rtn_dlr == *exclude_dealer);
    return rtn_dlr;
}

Dealer* BreaktimeQueue::popDealerFromNextNextBreaktimeQueue(
        QDateTime next_arrangement_time, Dealer *exclude_dealer)
{
    Dealer *rtn_dlr = nullptr;
    const dealer_raw_container &raw_dealers = data->nextnextWorkingDealers->getRawContainer();
    dealer_raw_container copied_dealers;
    std::copy_if(raw_dealers.begin(), raw_dealers.end(),
                 std::back_inserter(copied_dealers),
                 std::not1(std::mem_fun(&Dealer::isOnNextNextWork)));
    do
    {
        if(copied_dealers.size() == 0)
            return nullptr;
        dealer_raw_container::iterator rtn_iter
                = std::min_element(copied_dealers.begin(), copied_dealers.end(),
                                   DealerPriority(NEXTNEXT_QUEUE_TIME, next_arrangement_time));
        rtn_dlr = *rtn_iter;
        copied_dealers.erase(rtn_iter);
    } while(exclude_dealer != nullptr && *rtn_dlr == *exclude_dealer);
    return rtn_dlr;
}

void BreaktimeQueue::countDealersContinuousBreaktime()
{
    const dealer_raw_container &raw_dealers = data->currentWorkingDealers->getRawContainer();
    for(dealer_raw_container::const_iterator iter = raw_dealers.begin();
        iter!=raw_dealers.end(); iter++)
    {
        if((*iter)->isOnCurrentWork())
            (*iter)->resetContinuousBreaktime();
        else
            (*iter)->countContinuousBreaktime();
    }
}

void BreaktimeQueue::switchCurrentWorkingTime(sys_var::working_time work_time)
{
    if(work_time == sys_var::MORNING)
        data->currentWorkingDealers = morningDealers;
    else if(work_time == sys_var::DAY)
        data->currentWorkingDealers = dayDealers;
    else // work_time == sys_var::NIGHT
        data->currentWorkingDealers = nightDealers;
}

void BreaktimeQueue::switchNextWorkingTime(sys_var::working_time work_time)
{
    if(work_time == sys_var::MORNING)
        data->nextWorkingDealers = morningDealers;
    else if(work_time == sys_var::DAY)
        data->nextWorkingDealers = dayDealers;
    else // work_time == sys_var::NIGHT
        data->nextWorkingDealers = nightDealers;
}

void BreaktimeQueue::switchNextNextWorkingTime(sys_var::working_time work_time)
{
    if(work_time == sys_var::MORNING)
        data->nextnextWorkingDealers = morningDealers;
    else if(work_time == sys_var::DAY)
        data->nextnextWorkingDealers = dayDealers;
    else // work_time == sys_var::NIGHT
        data->nextnextWorkingDealers = nightDealers;
}

void BreaktimeQueue::tickOverallWorktimeForWorkingDealers()
{
    const dealer_raw_container &raw_dealers = data->currentWorkingDealers->getRawContainer();
    for(dealer_raw_container::const_iterator iter = raw_dealers.begin();
        iter!=raw_dealers.end(); iter++)
        if((*iter)->isOnCurrentWork())
            (*iter)->tickOverallWorktime();
}
