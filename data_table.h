#ifndef TABLE_H
#define TABLE_H

#include <QObject>
#include <QSharedData>

#include "data_dealer.h"

// Game Type
typedef int game_type;

enum {ROULETTE=1, BLACKJACK, BACCARAT};

class TableData : public QSharedData
{
public:
    TableData();

    Dealer *currentDealer;
    Dealer *nextDealer;
    Dealer *nextnextDealer;
};

class Table : public QObject
{
    Q_OBJECT

public:
    // class constructor
    explicit Table(const game_type game_type, const int table_no);

    // [==] operator overriding
    bool operator==(const Table &target);

    // get [GAME_TYPE]
    game_type getGameType() const;
    // get [TABLE_NO]
    int getTableNo() const;
    // get [TABLE_NAME]
    QString getTableName() const;

    // get [TableData::currentDealer]
    Dealer* getCurrentDealer() const;
    // set [TableData::currentDealer]
    void setCurrentDealer(Dealer* dlr_ptr);
    // remove [TableData::currentDealer]
    void removeCurrentDealer();

    // get [TableData::nextDealer]
    Dealer* getNextDealer() const;
    // set [TableData::nextDealer]
    void setNextDealer(Dealer* dlr_ptr);
    // remove [TableData::nextDealer]
    void removeNextDealer();

    // get [TableData::nextnextDealer]
    Dealer* getNextNextDealer() const;
    // set [TableData::nextnextDealer]
    void setNextNextDealer(Dealer* dlr_ptr);
    // remove [TableData::nextnextDealer]
    void removeNextNextDealer();

    void pushArrangedDealers();

private:
    // game type
    const game_type GAME_TYPE;
    // table number
    const int TABLE_NO;
    // table name (= game type + table number)
    QString TABLE_NAME;

    // shared data
    QSharedDataPointer<TableData> data;

signals:
    void currentDealerArranged(Dealer *dlr_ptr);
    void nextDealerArranged(Dealer *dlr_ptr);
    void nextnextDealerArranged(Dealer *dlr_ptr);

public slots:
};

// Table Priority Functor
struct TablePriority: public std::binary_function<Table*, Table*, bool>
{
    bool operator()(const Table* left, const Table* right) const
    {
        return left->getGameType() < right->getGameType()
            || (left->getGameType() == right->getGameType()
            && left->getTableNo() < right->getTableNo());
    }
};

#endif // TABLE_H
