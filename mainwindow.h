#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QDateTime>

#include "filemanager.h"

#include "ui_dealerlist.h"
#include "ui_currentdealerlist.h"
#include "ui_tablelist.h"

#include "container_dealer.h"
#include "container_table.h"

#include "thread_dealerarrangement.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    // File Manager
    FileManager *fileManager;

    // Containers
    DealerContainer *dealerConts[3];
    TableContainer *tableCont;

    // Dealer Lists
    // -dealerLists[sys_var::MORNING]: morning-time dealers
    // -dealerLists[sys_var::DAY]: day-time dealers
    // -dealerLists[sys_var::NIGHT]: night-time dealers
    UIDealerList *dealerLists[3];

    // Current Dealers List
    UICurrentDealerList *currentDealerList;

    // Table Lists
    UITableList *tableList;

    // Dealer Arrangement Thread
    DealerArrangementThread *arrangementThread;

signals:

public slots:
    // show current time
    void showCurrentTime();

    // display working-time
    void displayWorkingTime(sys_var::working_time work_time);

    // display arrangement times
    void displayArrangementTimes(
            const QDateTime &current, const QDateTime &next, const QDateTime &nextnext);

    // show add dealer dialog
    void showNewDealerDialog();
    // delete selected dealer
    void deleteSelectedDealer();

    // show add table dialog
    void showNewTableDialog();
};

#endif // MAINWINDOW_H
