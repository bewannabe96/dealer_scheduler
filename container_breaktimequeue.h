#ifndef CONTAINER_BREAKTIMEQUEUE_H
#define CONTAINER_BREAKTIMEQUEUE_H

#include <QObject>
#include <QSharedData>
#include <QMutex>

#include "data_dealer.h"
#include "container_dealer.h"

class BreaktimeQueueData : public QSharedData
{
public:
    explicit BreaktimeQueueData();
    DealerContainer *currentWorkingDealers;
    DealerContainer *nextWorkingDealers;
    DealerContainer *nextnextWorkingDealers;
};


class BreaktimeQueue : public QObject
{
    Q_OBJECT
public:
    explicit BreaktimeQueue(
            QObject *parent,
            DealerContainer *morning_dealers,
            DealerContainer *day_dealers,
            DealerContainer *night_dealers
            );

    Dealer* popDealerFromCurrentBreaktimeQueue();
    Dealer* popDealerFromNextBreaktimeQueue(QDateTime next_arrangement_time, Dealer *exclude_dealer = nullptr);
    Dealer* popDealerFromNextNextBreaktimeQueue(QDateTime next_arrangement_time, Dealer *exclude_dealer = nullptr);

    void countDealersContinuousBreaktime();

private:
    // shared data
    QSharedDataPointer<BreaktimeQueueData> data;

    DealerContainer *morningDealers;
    DealerContainer *dayDealers;
    DealerContainer *nightDealers;

signals:

public slots:
    void switchCurrentWorkingTime(sys_var::working_time work_time);
    void switchNextWorkingTime(sys_var::working_time work_time);
    void switchNextNextWorkingTime(sys_var::working_time work_time);
    void tickOverallWorktimeForWorkingDealers();
};

#endif // CONTAINER_BREAKTIMEQUEUE_H
