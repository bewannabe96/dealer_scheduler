#ifndef TABLE_CONTAINER_H
#define TABLE_CONTAINER_H

#include <QObject>
#include <QSharedData>

#include <set>

#include "data_table.h"

// Raw Container Type
typedef std::set<Table*, TablePriority> table_raw_container;

class TableContainerData : public QSharedData
{
public:
    // tables raw container
    table_raw_container tables;
};

class TableContainer : public QObject
{
    Q_OBJECT

public:
    explicit TableContainer(QObject *parent);

    const table_raw_container& getRawContainer() const;

    // search table
    // return [nullptr] if not founded
    Table* searchTable(const Table& compare);

    // add table
    void addTable(const game_type game_type, const int table_no);

    void removeAllNextDealers();
    void removeAllNextNextDealers();
    void pushArrangedDealers();

private:
    // shared data
    QSharedDataPointer<TableContainerData> data;

signals:
    void tableAdded(Table *tbl_ptr);
    void tableRemoved(Table *tbl_ptr);

public slots:
    // remove table
    void removeTable(const Table *tbl_ptr);
};

#endif // TABLE_CONTAINER_H
