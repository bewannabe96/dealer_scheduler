#include "filemanager.h"

#include <QFile>
#include <QDataStream>

#include "systemstatus.h"

#include "data_dealer.h"

FileManager::FileManager(QObject *parent, DealerContainer *dealer_containers[]) :
    QObject(parent), dealerConts(dealer_containers)
{
    // file manager signal-slot connections
    connect(dealerConts[sys_var::MORNING], &DealerContainer::dealerAdded,
            this, &FileManager::writeMorningDealersDataFile);
    connect(dealerConts[sys_var::MORNING], &DealerContainer::dealerRemoved,
            this, &FileManager::writeMorningDealersDataFile);

    connect(dealerConts[sys_var::DAY], &DealerContainer::dealerAdded,
            this, &FileManager::writeDayDealersDataFiel);
    connect(dealerConts[sys_var::DAY], &DealerContainer::dealerRemoved,
            this, &FileManager::writeDayDealersDataFiel);

    connect(dealerConts[sys_var::NIGHT], &DealerContainer::dealerAdded,
            this, &FileManager::writeNightDealersDataFile);
    connect(dealerConts[sys_var::NIGHT], &DealerContainer::dealerRemoved,
            this, &FileManager::writeNightDealersDataFile);
}

void FileManager::readDealersDatafile(sys_var::working_time working_time)
{
    // open file
    QFile file(sys_var::DEALERS_DATAFILE[working_time]);
    if(!file.open(QIODevice::ReadOnly))
    {
        SystemStatus::informFileNotOpened(QString(sys_var::DEALERS_DATAFILE[working_time]));
        return;
    }
    QDataStream in(&file);
    in.setByteOrder(QDataStream::LittleEndian);

    // read container size
    int container_size;
    in >> container_size;

    // read container data
    int name_size, read_size;
    char * str_buffer = new char[BUF_SIZE];
    QString name;
    int grade;
    for(int i=0; i<container_size; i++)
    {
        in >> name_size;
        while(name_size > 0)
        {
            read_size = in.readRawData(str_buffer, name_size);
            name_size -= read_size;
        }
        name = QString(str_buffer);

        in >> grade;

        dealerConts[working_time]->addDealer(working_time, name, grade, true);
    }

    delete[] str_buffer;
}

void FileManager::writeDealersDatafile(sys_var::working_time working_time)
{
    // open file
    QFile file(sys_var::DEALERS_DATAFILE[working_time]);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        SystemStatus::informFileNotOpened(QString(sys_var::DEALERS_DATAFILE[working_time]));
        return;
    }
    QDataStream out(&file);
    out.setByteOrder(QDataStream::LittleEndian);

    // write container size
    int container_size = dealerConts[working_time]->getSize();
    out << container_size;

    // write container data
    const dealer_raw_container &raw_dealers = dealerConts[working_time]->getRawContainer();
    const char *raw_name;
    int name_size;
    for(dealer_raw_container::const_iterator iter=raw_dealers.begin();
        iter!=raw_dealers.end(); iter++)
    {
        raw_name = ((*iter)->getDealerName().toStdString().c_str());
        name_size = strlen(raw_name) + 1;
        out << name_size;
        out.writeRawData(raw_name, name_size);
        out << (*iter)->getDealerGrade();
    }
}

void FileManager::readMorningDealersDataFile() { readDealersDatafile(sys_var::MORNING); }
void FileManager::readDayDealersDataFile() { readDealersDatafile(sys_var::DAY); }
void FileManager::readNightDealersDataFile() { readDealersDatafile(sys_var::NIGHT); }

void FileManager::writeMorningDealersDataFile() { writeDealersDatafile(sys_var::MORNING); }
void FileManager::writeDayDealersDataFiel() { writeDealersDatafile(sys_var::DAY); }
void FileManager::writeNightDealersDataFile() { writeDealersDatafile(sys_var::NIGHT); }
