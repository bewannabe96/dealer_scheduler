#ifndef THREAD_DEALERARRANGEMENT_H
#define THREAD_DEALERARRANGEMENT_H

#include <QThread>

#include <QMutex>
#include <QWaitCondition>

#include <QDateTime>

#include "sys_var.h"

#include "data_table.h"

#include "container_dealer.h"
#include "container_breaktimequeue.h"

#include "container_table.h"

#define HOUR_SIX 6
#define HOUR_FOURTEEN 14
#define HOUR_TWENTYTWO 22

#define MIN_TEN 10
#define MIN_THIRTY 30
#define MIN_FIFTY 50

namespace DATHREAD_TIME_CONST
{

// Morning Time: 	0650-1450
const QTime morningTimeStart = QTime(HOUR_SIX, MIN_FIFTY);
const QTime morningTimeEnd = QTime(HOUR_FOURTEEN, MIN_FIFTY);
// Day Time:		1450-2250
const QTime dayTimeStart = QTime(HOUR_FOURTEEN, MIN_FIFTY);
const QTime dayTimeEnd = QTime(HOUR_TWENTYTWO, MIN_FIFTY);
// Night Time:		2250-0650
const QTime nightTimeStart = QTime(HOUR_TWENTYTWO, MIN_FIFTY);
const QTime nightTimeEnd = QTime(HOUR_SIX, MIN_FIFTY);

}

class DealerArrangementThread : public QThread
{
    Q_OBJECT

public:
    DealerArrangementThread(
            QObject *parent,
            DealerContainer *morning_dealers,
            DealerContainer *day_dealers,
            DealerContainer *night_dealers,
            TableContainer *table_container
            );

    void run() override;

private:
    // core thread stop condition variable
    QWaitCondition stopCondVar;
    // core thread stop condition variable mutex
    QMutex stopCondVarMutex;

    // current working-time
    sys_var::working_time currentWorkingTime;
    // next working-time
    sys_var::working_time nextWorkingTime;
    // next-next working-time
    sys_var::working_time nextnextWorkingTime;

    // current arrangement time
    QDateTime currentArrangementTime;
    // next arrangement time
    QDateTime nextArrangementTime;
    // next next arrangement time
    QDateTime nextnextArrangementTime;

    sys_var::working_time convertQDateTimeToWorkingTime(const QDateTime &datetime);

    // breaktime queue (dealers container adapter)
    BreaktimeQueue *breaktimeQueue;

    // table container
    TableContainer *tableCont;

    void initializeArrangementTimes();
    void setArrangementTimes();

    void arrangeAllNextDealers();
    void arrangeAllNextNextDealers();
    void rearrangeAllDealers();

signals:
    void arrangementTimeSet(
            const QDateTime &current, const QDateTime &next, const QDateTime &nextnext);
    void currentWorkingTimeChanged(sys_var::working_time work_time);
    void nextWorkingTimeChanged(sys_var::working_time work_time);
    void nextnextWorkingTimeChanged(sys_var::working_time work_time);

public slots:
    void stop();

    void arrangeNewTable(Table *tbl_ptr);
    void clearRemovedTable(Table *tbl_ptr);
    void dealRemovedDealer(Dealer *dlr_ptr);
};

#endif // THREAD_DEALERARRANGEMENT_H
