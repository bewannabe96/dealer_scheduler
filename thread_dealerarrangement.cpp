#include "thread_dealerarrangement.h"

#include "systemstatus.h"

#include "data_dealer.h"

#include <QTimer>

DealerArrangementThread::DealerArrangementThread(
        QObject *parent,
        DealerContainer *morning_dealers,
        DealerContainer *day_dealers,
        DealerContainer *night_dealers,
        TableContainer *table_container) :
    QThread(parent), tableCont(table_container)
{
    breaktimeQueue = new BreaktimeQueue(
                this,
                morning_dealers,
                day_dealers,
                night_dealers
            );

    // breaktime queue signal-slot connections
    connect(this, &DealerArrangementThread::currentWorkingTimeChanged,
            breaktimeQueue, &BreaktimeQueue::switchCurrentWorkingTime);
    connect(this, &DealerArrangementThread::nextWorkingTimeChanged,
            breaktimeQueue, &BreaktimeQueue::switchNextWorkingTime);
    connect(this, &DealerArrangementThread::nextnextWorkingTimeChanged,
            breaktimeQueue, &BreaktimeQueue::switchNextNextWorkingTime);

    // worktime time display
    QTimer *minuteTimer = new QTimer(this);
    connect(minuteTimer, &QTimer::timeout,
            breaktimeQueue, &BreaktimeQueue::tickOverallWorktimeForWorkingDealers);
    minuteTimer->start(Dealer::TICK_INTERVAL * 1000); // 20 second
}

void DealerArrangementThread::run()
{
    stopCondVarMutex.lock();
    initializeArrangementTimes();
    while(!stopCondVar.wait(
              &stopCondVarMutex,
              QDateTime::currentDateTime().msecsTo(nextArrangementTime)
              ))
    {
        setArrangementTimes();
        breaktimeQueue->countDealersContinuousBreaktime();

        tableCont->pushArrangedDealers();
        arrangeAllNextNextDealers();
    }
    stopCondVarMutex.unlock();
}

sys_var::working_time DealerArrangementThread::convertQDateTimeToWorkingTime(
        const QDateTime &datetime)
{
    QTime time = datetime.time();
    if(time >= DATHREAD_TIME_CONST::morningTimeStart &&
            time < DATHREAD_TIME_CONST::morningTimeEnd)
        return sys_var::MORNING;
    else if(time >= DATHREAD_TIME_CONST::dayTimeStart &&
            time < DATHREAD_TIME_CONST::dayTimeEnd)
        return sys_var::DAY;
    else // time >= DATHREAD_TIME_CONST::nightTimeStart ||
        // time < DATHREAD_TIME_CONST::nightTimeEnd
        return sys_var::NIGHT;
}

void DealerArrangementThread::initializeArrangementTimes()
{
    nextArrangementTime = QDateTime::currentDateTime();

    int minute = nextArrangementTime.time().minute();
    if(minute < MIN_TEN)
    {
        nextArrangementTime.setTime(
                    QTime(nextArrangementTime.time().hour(), MIN_TEN)
                    );
    }
    else if(minute >= MIN_TEN && minute < MIN_THIRTY)
    {
        nextArrangementTime.setTime(
                    QTime(nextArrangementTime.time().hour(), MIN_THIRTY)
                    );
    }
    else if(minute >= MIN_THIRTY && minute < MIN_FIFTY)
    {
        nextArrangementTime.setTime(
                    QTime(nextArrangementTime.time().hour(), MIN_FIFTY)
                    );
    }
    else // minute >= MIN_FIFTY
    {
        nextArrangementTime.setTime(
                    QTime(nextArrangementTime.time().hour(), MIN_FIFTY)
                    );
        nextArrangementTime = nextArrangementTime.addSecs(20 * 60); // +20min
    }

    currentArrangementTime = nextArrangementTime.addSecs(-20 * 60); // -20min
    nextnextArrangementTime = nextArrangementTime.addSecs(20 * 60); // +20min
    emit arrangementTimeSet(currentArrangementTime, nextArrangementTime, nextnextArrangementTime);

    // set working-times and signal them
    currentWorkingTime = convertQDateTimeToWorkingTime(currentArrangementTime);
    emit currentWorkingTimeChanged(currentWorkingTime);
    nextWorkingTime = convertQDateTimeToWorkingTime(nextArrangementTime);
    emit nextWorkingTimeChanged(nextWorkingTime);
    nextnextWorkingTime = convertQDateTimeToWorkingTime(nextnextArrangementTime);
    emit nextnextWorkingTimeChanged(nextnextWorkingTime);
}

void DealerArrangementThread::setArrangementTimes()
{
    currentArrangementTime = nextArrangementTime;
    nextArrangementTime = currentArrangementTime.addSecs(20 * 60); // +20min
    nextnextArrangementTime = currentArrangementTime.addSecs(40 * 60); // +40min
    emit arrangementTimeSet(currentArrangementTime, nextArrangementTime, nextnextArrangementTime);

    // check working-time changed
    sys_var::working_time working_time
            = convertQDateTimeToWorkingTime(nextnextArrangementTime);
    if(nextnextWorkingTime != working_time)
    {
        nextnextWorkingTime = working_time;
        emit nextnextWorkingTimeChanged(nextnextWorkingTime);
        return;
    }
    working_time = convertQDateTimeToWorkingTime(nextArrangementTime);
    if(nextWorkingTime != working_time)
    {
        nextWorkingTime = working_time;
        emit nextWorkingTimeChanged(nextWorkingTime);
        return;
    }
    working_time = convertQDateTimeToWorkingTime(currentArrangementTime);
    if(currentWorkingTime != working_time)
    {
        currentWorkingTime = working_time;
        emit currentWorkingTimeChanged(currentWorkingTime);
    }
}

void DealerArrangementThread::arrangeAllNextDealers()
{
    Dealer *dlr_ptr;
    const table_raw_container &raw_tables = tableCont->getRawContainer();
    for(table_raw_container::const_iterator iter=raw_tables.begin();
        iter!=raw_tables.end(); iter++)
    {
        dlr_ptr = breaktimeQueue->popDealerFromNextBreaktimeQueue(
                    nextArrangementTime,
                    (*iter)->getCurrentDealer()
                    );
        (*iter)->setNextDealer(dlr_ptr);
    }

}

void DealerArrangementThread::arrangeAllNextNextDealers()
{
    Dealer *dlr_ptr;
    const table_raw_container &raw_tables = tableCont->getRawContainer();
    for(table_raw_container::const_iterator iter=raw_tables.begin();
        iter!=raw_tables.end(); iter++)
    {
        dlr_ptr = breaktimeQueue->popDealerFromNextNextBreaktimeQueue(
                    nextArrangementTime,
                    (*iter)->getNextDealer()
                    );
        (*iter)->setNextNextDealer(dlr_ptr);
    }
}

void DealerArrangementThread::rearrangeAllDealers()
{
    tableCont->removeAllNextDealers();
    arrangeAllNextDealers();

    tableCont->removeAllNextNextDealers();
    arrangeAllNextNextDealers();
}

void DealerArrangementThread::stop()
{
    stopCondVarMutex.lock();
    stopCondVar.wakeAll();
    stopCondVarMutex.unlock();
}

void DealerArrangementThread::arrangeNewTable(Table *tbl_ptr)
{
    Dealer *popped_dealer = breaktimeQueue->popDealerFromCurrentBreaktimeQueue();
    if(popped_dealer == nullptr)
        SystemStatus::informNotEnoughDealer();
    tbl_ptr->setCurrentDealer(popped_dealer);

    rearrangeAllDealers();
}

void DealerArrangementThread::clearRemovedTable(Table *tbl_ptr)
{
    tbl_ptr->removeCurrentDealer();
    tbl_ptr->removeNextDealer();
    tbl_ptr->removeNextNextDealer();

    rearrangeAllDealers();
}

void DealerArrangementThread::dealRemovedDealer(Dealer *dlr_ptr)
{
    if(dlr_ptr->isOnCurrentWork()
            || dlr_ptr->isOnNextWork()
            || dlr_ptr->isOnNextNextWork())
        rearrangeAllDealers();
}
