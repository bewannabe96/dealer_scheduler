#ifndef SYSTEMSTATUS_H
#define SYSTEMSTATUS_H

#include <QObject>

#include <QString>

class SystemStatus
{
public:
    static void informDealerCreated(const QString &dlr_name);
    static void informDealerExist(const QString &dlr_name);
    static void informDealerRemoved(const QString &dlr_name);
    static bool confirmDealerDeletion(const QString &dlr_name);

    static void informTableCreated(const QString &tbl_name);
    static void informTableExist(const QString &tbl_name);
    static void informTableRemoved(const QString &tbl_name);

    static void informFileNotOpened(const QString &file_name);

    static void informNotEnoughDealer();
};

#endif // SYSTEMSTATUS_H
