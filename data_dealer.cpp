#include "data_dealer.h"

DealerData::DealerData() :
    onCurrentWork(false),
    onNextWork(false),
    onNextNextWork(false),
    overallWorktime(0),
    continuousBreaktime(0)
{}


Dealer::Dealer(sys_var::working_time work_time, const QString& name, const dealer_grade grade) :
    QObject(nullptr), DEALER_WORKING_TIME(work_time), DEALER_NAME(name), DEALER_GRADE(grade)
{
    data = new DealerData();
}

bool Dealer::operator==(const Dealer &target)
{
    return DEALER_WORKING_TIME == target.DEALER_WORKING_TIME
            && DEALER_NAME == target.DEALER_NAME
            && DEALER_GRADE == target.DEALER_GRADE;
}

sys_var::working_time Dealer::getWorkingTime() const { return DEALER_WORKING_TIME; }

QString Dealer::getDealerName() const { return DEALER_NAME; }

dealer_grade Dealer::getDealerGrade() const { return DEALER_GRADE; }

bool Dealer::isOnCurrentWork() const { return data->onCurrentWork; }
void Dealer::setOnCurrentWork()
{
    data->onCurrentWork = true;
    resetContinuousBreaktime();
    emit currentWorkingStatusChanged();
}
void Dealer::setOffCurrentWork()
{
    data->onCurrentWork = false;
    emit currentWorkingStatusChanged();
}

bool Dealer::isOnNextWork() const { return data->onNextWork; }
void Dealer::setOnNextWork() { data->onNextWork = true; }
void Dealer::setOffNextWork() { data->onNextWork = false; }

bool Dealer::isOnNextNextWork() const { return data->onNextNextWork; }
void Dealer::setOnNextNextWork() { data->onNextNextWork = true; }
void Dealer::setOffNextNextWork() { data->onNextNextWork = false; }

int Dealer::getOverallWorktime() const { return data->overallWorktime; }
void Dealer::tickOverallWorktime()
{
    data->overallWorktime += TICK_INTERVAL;
    emit overallWorktimeChanged();
}

void Dealer::countContinuousBreaktime()
{
    data->continuousBreaktime++;
}
void Dealer::resetContinuousBreaktime()
{
    data->continuousBreaktime = 0;
}
int Dealer::getContinuousBreaktime() const { return data->continuousBreaktime; }
