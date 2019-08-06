#ifndef DEALER_H
#define DEALER_H

#include <QObject>
#include <QSharedData>

#include <QDateTime>

#include "sys_var.h"

// Dealer Grade
typedef int dealer_grade;

// Dealer Grade Range: 1~14
#define DEALER_GRADE_LOWER_LIMIT 1
#define DEALER_GRADE_UPPER_LIMIT 14

class DealerData : public QSharedData
{
public:
    DealerData();

    bool onCurrentWork;
    bool onNextWork;
    bool onNextNextWork;

    int overallWorktime; // in second

    int continuousBreaktime;
};

class Dealer : public QObject
{
    Q_OBJECT

public:
    // class constructor
    explicit Dealer(sys_var::working_time work_time, const QString& name, const dealer_grade grade);

    // tick interval
    static const int TICK_INTERVAL = 20; // 20sec

    // [==] operator overriding
    bool operator==(const Dealer &target);

    // get [DEALER_WORKING_TIME]
    sys_var::working_time getWorkingTime() const;
    // get [DEALER_NAME]
    QString getDealerName() const;
    // get [DEALER_GRADE]
    dealer_grade getDealerGrade() const;

    // get [DealerData::onCurrentWork]
    bool isOnCurrentWork() const;
    // set [DealerData::onCurrentWork]
    void setOnCurrentWork();
    void setOffCurrentWork();

    // get [DealerData::onNextWork]
    bool isOnNextWork() const;
    // set [DealerData::onNextWork]
    void setOnNextWork();
    void setOffNextWork();

    // get [DealerData::onNextNextWork]
    bool isOnNextNextWork() const;
    // set [DealerData::onNextNextWork]
    void setOnNextNextWork();
    void setOffNextNextWork();

    // get [DealerData::overallWorktime]
    int getOverallWorktime() const;
    // increase [DealerData::overallWorktime] by 1
    void tickOverallWorktime();

    // count [DealerData::continuousBreaktime]
    void countContinuousBreaktime();
    // reset [DealerData::continuousBreaktime] to 0
    void resetContinuousBreaktime();
    // get [DealerData::continuousBreaktime]
    int getContinuousBreaktime() const;

private:
    // dealer working time
    const sys_var::working_time DEALER_WORKING_TIME;
    // dealer name
    const QString DEALER_NAME;
    // dealer grade
    const dealer_grade DEALER_GRADE;

    // shared data
    QSharedDataPointer<DealerData> data;

signals:
    void currentWorkingStatusChanged();
    void overallWorktimeChanged();

public slots:
};

#define CURRENT_QUEUE_TIME  1
#define NEXT_QUEUE_TIME     2
#define NEXTNEXT_QUEUE_TIME 3

// Dealer Priority Functor
struct DealerPriority: public std::binary_function<Dealer*, Dealer*, bool>
{
private:
    const int EQUAL_LIMIT = 10 * 60; // 10 min
    int queueTime;
    int minuteLeftUntilNext;

public:
    DealerPriority() : queueTime(CURRENT_QUEUE_TIME) {}
    DealerPriority(int queue_time, QDateTime next_arrangement_time) :
        queueTime(queue_time)
    {
        minuteLeftUntilNext = QDateTime::currentDateTime().secsTo(next_arrangement_time);
    }

    bool operator()(const Dealer* left, const Dealer* right) const
    {
        int left_cont_breaktime = left->getContinuousBreaktime();
        int right_cont_breaktime = right->getContinuousBreaktime();

        switch(queueTime)
        {
        case NEXTNEXT_QUEUE_TIME:
            if(left->isOnNextWork())
                left_cont_breaktime = 0;
            else if(left->isOnCurrentWork())
                left_cont_breaktime = 1;
            else
                left_cont_breaktime += 2;

            if(right->isOnNextWork())
                right_cont_breaktime = 0;
            else if(right->isOnCurrentWork())
                right_cont_breaktime = 1;
            else
                right_cont_breaktime += 2;
            break;

        case NEXT_QUEUE_TIME:;
            if(left->isOnCurrentWork())
                left_cont_breaktime = 0;
            else
                left_cont_breaktime++;

            if(right->isOnCurrentWork())
                right_cont_breaktime = 0;
            else
                right_cont_breaktime++;
        }

        if(left_cont_breaktime == right_cont_breaktime)
        {
            int left_overall_worktime = left->getOverallWorktime();
            int right_overall_worktime = right->getOverallWorktime();

            switch(queueTime)
            {
            case NEXTNEXT_QUEUE_TIME:
                if(left->isOnNextWork())
                    left_overall_worktime += 20 * 60; // +20min
                if(right->isOnNextWork())
                    right_overall_worktime += 20 * 60; // +20min
            case NEXT_QUEUE_TIME:
                if(left->isOnCurrentWork())
                    left_overall_worktime += minuteLeftUntilNext;
                if(right->isOnCurrentWork())
                    right_overall_worktime += minuteLeftUntilNext;
            }

            int diff = left_overall_worktime - right_overall_worktime;

            if(diff > -EQUAL_LIMIT && diff < EQUAL_LIMIT)
            {
                return left->getDealerGrade() > right->getDealerGrade();
            }
            return left_overall_worktime < right_overall_worktime;
        }
        return left_cont_breaktime > right_cont_breaktime;
    }
};

#endif // DEALER_H
