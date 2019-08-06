#-------------------------------------------------
#
# Project created by QtCreator 2018-08-20T21:23:22
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DealerSchedulerRedesign
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
    ui_currentdealeritem.cpp \
    ui_currentdealerlist.cpp \
    ui_dealeritem.cpp \
    ui_dealerlist.cpp \
    ui_newdealerdialog.cpp \
    ui_newtabledialog.cpp \
    ui_tableitem.cpp \
    ui_tablelist.cpp \
    data_table.cpp \
    data_dealer.cpp \
    container_dealer.cpp \
    container_table.cpp \
    mainwindow.cpp \
    thread_dealerarrangement.cpp \
    sys_var.cpp \
    container_breaktimequeue.cpp \
    systemstatus.cpp \
    filemanager.cpp \
    ui_notableitem.cpp

HEADERS += \
    sys_var.h \
    ui_currentdealeritem.h \
    ui_currentdealerlist.h \
    ui_dealeritem.h \
    ui_dealerlist.h \
    ui_newdealerdialog.h \
    ui_newtabledialog.h \
    ui_tableitem.h \
    ui_tablelist.h \
    data_dealer.h \
    data_table.h \
    container_dealer.h \
    container_table.h \
    mainwindow.h \
    thread_dealerarrangement.h \
    container_breaktimequeue.h \
    systemstatus.h \
    filemanager.h \
    ui_notableitem.h

FORMS += \
    mainwindow.ui \
    ui_newdealerdialog.ui \
    ui_currentdealerlist.ui \
    ui_dealerlist.ui \
    ui_tablelist.ui \
    ui_tableitem.ui \
    ui_newtabledialog.ui \
    ui_notableitem.ui

RESOURCES += \
    icons.qrc
