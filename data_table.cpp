#include "data_table.h"

TableData::TableData()
{}

Table::Table(const game_type game_type, const int table_no) :
    QObject(nullptr), GAME_TYPE(game_type), TABLE_NO(table_no)
{
    data = new TableData();
    data->currentDealer = nullptr;
    data->nextDealer = nullptr;
    data->nextnextDealer = nullptr;

    switch(game_type)
    {
    case ROULETTE:
        TABLE_NAME = "Roulette " + QString::number(table_no);
        break;

    case BLACKJACK:
        TABLE_NAME = "Blackjack " + QString::number(table_no);
        break;

    case BACCARAT:
        TABLE_NAME = "Baccarat " + QString::number(table_no);
        break;
    }
}

bool Table::operator==(const Table &target)
{
    return TABLE_NAME == target.TABLE_NAME;
}

game_type Table::getGameType() const { return GAME_TYPE; }

int Table::getTableNo() const { return TABLE_NO; }

QString Table::getTableName() const { return TABLE_NAME; }

Dealer* Table::getCurrentDealer() const { return data->currentDealer; }
void Table::setCurrentDealer(Dealer* dlr_ptr)
{
    data->currentDealer = dlr_ptr;
    if(data->currentDealer != nullptr)
        data->currentDealer->setOnCurrentWork();
    emit currentDealerArranged(dlr_ptr);
}
void Table::removeCurrentDealer()
{
    if(data->currentDealer == nullptr)
        return;
    data->currentDealer->setOffCurrentWork();
    data->currentDealer = nullptr;
    emit currentDealerArranged(data->currentDealer);
}

Dealer* Table::getNextDealer() const { return data->nextDealer; }
void Table::setNextDealer(Dealer* dlr_ptr)
{
    data->nextDealer = dlr_ptr;
    if(data->nextDealer != nullptr)
        data->nextDealer->setOnNextWork();
    emit nextDealerArranged(data->nextDealer);
}
void Table::removeNextDealer()
{
    if(data->nextDealer == nullptr)
        return;
    data->nextDealer->setOffNextWork();
    data->nextDealer = nullptr;
    emit nextDealerArranged(data->nextDealer);
}

Dealer* Table::getNextNextDealer() const { return data->nextnextDealer; }
void Table::setNextNextDealer(Dealer* dlr_ptr)
{
    data->nextnextDealer = dlr_ptr;
    if(data->nextnextDealer != nullptr)
        data->nextnextDealer->setOnNextNextWork();
    emit nextnextDealerArranged(dlr_ptr);
}
void Table::removeNextNextDealer()
{
    if(data->nextnextDealer == nullptr)
        return;
    data->nextnextDealer->setOffNextNextWork();
    data->nextnextDealer = nullptr;
    emit nextnextDealerArranged(data->nextnextDealer);
}

void Table::pushArrangedDealers()
{
    removeCurrentDealer();
    setCurrentDealer(data->nextDealer);

    removeNextDealer();
    setNextDealer(data->nextnextDealer);

    removeNextNextDealer();
}
