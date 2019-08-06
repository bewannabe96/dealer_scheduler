#include "container_table.h"

#include "systemstatus.h"

TableContainer::TableContainer(QObject *parent) :
    QObject(parent)
{
    data = new TableContainerData();
}

const table_raw_container& TableContainer::getRawContainer() const { return data->tables; }

Table* TableContainer::searchTable(const Table &compare)
{
    for(table_raw_container::iterator iter=data->tables.begin();
        iter!=data->tables.end(); iter++)
        if(**iter == compare)
            return *iter;
    return nullptr;
}

void TableContainer::addTable(const game_type game_type, const int table_no)
{
    Table *new_tbl_ptr = new Table(game_type, table_no);
    if(searchTable(*new_tbl_ptr) != nullptr)
    {
        SystemStatus::informTableExist(new_tbl_ptr->getTableName());
        delete new_tbl_ptr;
        return;
    }
    new_tbl_ptr->setParent(this);
    data->tables.insert(new_tbl_ptr);
    emit tableAdded(new_tbl_ptr);
    SystemStatus::informTableCreated(new_tbl_ptr->getTableName());
}

void TableContainer::removeAllNextDealers()
{
    for(table_raw_container::const_iterator iter=data->tables.begin();
        iter!=data->tables.end(); iter++)
        (*iter)->removeNextDealer();
}

void TableContainer::removeAllNextNextDealers()
{
    for(table_raw_container::const_iterator iter=data->tables.begin();
        iter!=data->tables.end(); iter++)
        (*iter)->removeNextNextDealer();
}

void TableContainer::pushArrangedDealers()
{
    for(table_raw_container::iterator iter=data->tables.begin();
        iter!=data->tables.end(); iter++)
        (*iter)->pushArrangedDealers();
}

void TableContainer::removeTable(const Table *tbl_ptr)
{
    for(table_raw_container::iterator iter=data->tables.begin();
        iter!=data->tables.end(); iter++)
        if(**iter == *tbl_ptr)
        {
            data->tables.erase(iter);
            emit tableRemoved(*iter);
            SystemStatus::informTableRemoved((*iter)->getTableName());
            break;
        }
}
