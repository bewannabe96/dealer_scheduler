#ifndef DEALER_CONTAINER_H
#define DEALER_CONTAINER_H

#include <QObject>
#include <QSharedData>

#include <list>
#include <algorithm>

#include "sys_var.h"

#include "data_dealer.h"

// Raw Container Type
typedef std::list<Dealer*> dealer_raw_container;

class DealerContainerData : public QSharedData
{
public:
    // dealers raw container
    dealer_raw_container dealers;
};

class DealerContainer : public QObject
{
    Q_OBJECT

public:
    // class constructor
    explicit DealerContainer(QObject *parent, sys_var::working_time work_time);

    const dealer_raw_container& getRawContainer() const;

    int getSize() const;

    // search dealer
    // return [nullptr] if not founded
    Dealer* searchDealer(const Dealer& compare);

    // add dealer
    void addDealer(sys_var::working_time work_time, const QString& name,
                   const dealer_grade grade, bool ignore_result = false);

    // remove dealer
    void removeDealer(const Dealer *dlr_ptr);

private:
    // working-time
    const sys_var::working_time WORKING_TIME;

    // shared data
    QSharedDataPointer<DealerContainerData> data;

signals:
    void dealerAdded(Dealer *dlr_ptr);
    void dealerRemoved(Dealer *dlr_ptr);
};

#endif // DEALER_CONTAINER_H
