#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTimer>

#include "ui_newdealerdialog.h"
#include "ui_newtabledialog.h"

#include "sys_var.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    // setup UI
    ui->setupUi(this);

    // maximize the window
    this->showMaximized();

    // register sys_var metatypes
    sys_var::registerMetaTypes();

    // initialize dealer containers
    dealerConts[sys_var::MORNING] = new DealerContainer(this, sys_var::MORNING);
    dealerConts[sys_var::DAY] = new DealerContainer(this, sys_var::DAY);
    dealerConts[sys_var::NIGHT] = new DealerContainer(this, sys_var::NIGHT);
    tableCont = new TableContainer(this);

    // current time display
    QTimer *secondTimer = new QTimer(this);
    connect(secondTimer, &QTimer::timeout, this, &MainWindow::showCurrentTime);
    secondTimer->start(1000); // 1 second
    showCurrentTime();

    // add dealer lists
    dealerLists[sys_var::MORNING] = new UIDealerList(this, dealerConts[sys_var::MORNING]);
    dealerLists[sys_var::DAY] = new UIDealerList(this, dealerConts[sys_var::DAY]);
    dealerLists[sys_var::NIGHT] = new UIDealerList(this, dealerConts[sys_var::NIGHT]);
    ui->morningTab->layout()->addWidget(dealerLists[sys_var::MORNING]);
    ui->dayTab->layout()->addWidget(dealerLists[sys_var::DAY]);
    ui->nightTab->layout()->addWidget(dealerLists[sys_var::NIGHT]);

    // add current dealers list
    currentDealerList = new UICurrentDealerList(
                this,
                dealerConts[sys_var::MORNING],
                dealerConts[sys_var::DAY],
                dealerConts[sys_var::NIGHT]
            );
    ui->currentDealerLayout->addWidget(currentDealerList);

    // add table list
    QVBoxLayout *tbl_vblayout = new QVBoxLayout(ui->tablesContent);
    ui->tablesContent->setLayout(tbl_vblayout);
    tableList = new UITableList(this, tableCont);
    tbl_vblayout->addWidget(tableList);

    // gui signal-slot connections
    // new dealer button clicked -> show new dealer dialog
    connect(ui->newDealerButton, &QPushButton::clicked, this, &MainWindow::showNewDealerDialog);
    // remove dealer button clicked -> delete selected dealer
    connect(ui->removeDealerButton, &QPushButton::clicked, this, &MainWindow::deleteSelectedDealer);
    // add table button clicked -> show new table dialog
    connect(ui->addTableButton, &QPushButton::clicked, this, &MainWindow::showNewTableDialog);

    // read dealers datafiles
    fileManager = new FileManager(this, dealerConts);
    fileManager->readMorningDealersDataFile();
    fileManager->readDayDealersDataFile();
    fileManager->readNightDealersDataFile();

    // dealer arrangement thread setting
    arrangementThread = new DealerArrangementThread(
                this,
                dealerConts[sys_var::MORNING],
                dealerConts[sys_var::DAY],
                dealerConts[sys_var::NIGHT],
                tableCont
            );
    // thread signal-slot connections
    connect(arrangementThread, &DealerArrangementThread::arrangementTimeSet,
            this, &MainWindow::displayArrangementTimes);
    connect(arrangementThread, &DealerArrangementThread::currentWorkingTimeChanged,
            this, &MainWindow::displayWorkingTime);
    connect(arrangementThread, &DealerArrangementThread::currentWorkingTimeChanged,
            currentDealerList, &UICurrentDealerList::switchWorkingTime);
    connect(tableCont, &TableContainer::tableAdded, arrangementThread,
            &DealerArrangementThread::arrangeNewTable);
    connect(tableCont, &TableContainer::tableRemoved, arrangementThread,
            &DealerArrangementThread::clearRemovedTable);
    connect(dealerConts[sys_var::MORNING], &DealerContainer::dealerRemoved,
            arrangementThread, &DealerArrangementThread::dealRemovedDealer);
    connect(dealerConts[sys_var::DAY], &DealerContainer::dealerRemoved,
            arrangementThread, &DealerArrangementThread::dealRemovedDealer);
    connect(dealerConts[sys_var::NIGHT], &DealerContainer::dealerRemoved,
            arrangementThread, &DealerArrangementThread::dealRemovedDealer);

    arrangementThread->start();
}

MainWindow::~MainWindow()
{
    arrangementThread->stop();
    delete ui;
}

void MainWindow::showCurrentTime()
{
    ui->currentTimeLabel->setText(QTime::currentTime().toString("AP hh:mm:ss"));
    ui->currentDateLabel->setText(QDate::currentDate().toString("yyyy/MM/dd (dddd)"));
}

void MainWindow::displayWorkingTime(sys_var::working_time work_time)
{
    switch(work_time)
    {
    case sys_var::MORNING:
        ui->currentWorktimeLabel->setText("Morning Time");
        ui->currentWorktimePeriodLabel->setText(
                    DATHREAD_TIME_CONST::morningTimeStart.toString("AP hh:mm:ss") + " ~ "
                    + DATHREAD_TIME_CONST::morningTimeEnd.toString("AP hh:mm:ss")
                    );
        break;
    case sys_var::DAY:
        ui->currentWorktimeLabel->setText("Day Time");
        ui->currentWorktimePeriodLabel->setText(
                    DATHREAD_TIME_CONST::dayTimeStart.toString("AP hh:mm:ss") + " ~ "
                    + DATHREAD_TIME_CONST::dayTimeEnd.toString("AP hh:mm:ss")
                    );
        break;
    case sys_var::NIGHT:
        ui->currentWorktimeLabel->setText("Night Time");
        ui->currentWorktimePeriodLabel->setText(
                    DATHREAD_TIME_CONST::nightTimeStart.toString("AP hh:mm:ss") + " ~ "
                    + DATHREAD_TIME_CONST::nightTimeEnd.toString("AP hh:mm:ss")
                    );
        break;
    }
}

void MainWindow::displayArrangementTimes(
        const QDateTime &current, const QDateTime &next, const QDateTime &nextnext)
{
    QDateTime nextnext_end_time = nextnext.addSecs(20 * 60); // +20min
    ui->currentArngeTimeLabel->setText(
                current.toString("yyyy/MM/dd AP hh:mm")
                + " ~ " + next.toString("yyyy/MM/dd AP hh:mm")
                );
    ui->nextArngeTimeLabel->setText(
                next.toString("yyyy/MM/dd AP hh:mm")
                + " ~ " + nextnext.toString("yyyy/MM/dd AP hh:mm")
                );
    ui->nextnextArngeTimeLabel->setText(
                nextnext.toString("yyyy/MM/dd AP hh:mm")
                + " ~ " + nextnext_end_time.toString("yyyy/MM/dd AP hh:mm")
                );
}

void MainWindow::showNewDealerDialog()
{
    UINewDealerDialog *newDealerDialog = new UINewDealerDialog(this);
    newDealerDialog->setModal(true);
    if(newDealerDialog->exec() == QDialog::Accepted)
    {
        dealerConts[newDealerDialog->getWorkingTime()]->addDealer(
                    newDealerDialog->getWorkingTime(),
                    newDealerDialog->getDealerName(),
                    newDealerDialog->getDealerGrade());
    }
    newDealerDialog->deleteLater();
}

void MainWindow::deleteSelectedDealer()
{
    sys_var::working_time work_time = ui->worktimeTab->currentIndex();
    if(work_time == -1)
        return;
    Dealer *selected = dealerLists[work_time]->getSelectedDealer();
    dealerConts[work_time]->removeDealer(selected);
}

void MainWindow::showNewTableDialog()
{
    UINewTableDialog *newTableDialog = new UINewTableDialog(this);
    newTableDialog->setModal(true);
    if(newTableDialog->exec() == QDialog::Accepted)
        tableCont->addTable(
                    newTableDialog->getGameType(),
                    newTableDialog->getTableNo());
    newTableDialog->deleteLater();
}
