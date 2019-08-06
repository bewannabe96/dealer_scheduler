#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QObject>

#include "sys_var.h"

#include "container_dealer.h"

#define BUF_SIZE 50

class FileManager : public QObject
{
    Q_OBJECT
public:
    explicit FileManager(QObject *parent, DealerContainer *dealer_containers[]);

private:
    DealerContainer **dealerConts;

    // Read Dealers Data File
    void readDealersDatafile(sys_var::working_time working_time);

    // Write Dealers Data File
    void writeDealersDatafile(sys_var::working_time working_time);

signals:

public slots:
    void readMorningDealersDataFile();
    void readDayDealersDataFile();
    void readNightDealersDataFile();

    void writeMorningDealersDataFile();
    void writeDayDealersDataFiel();
    void writeNightDealersDataFile();
};

#endif // FILEMANAGER_H
