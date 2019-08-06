#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    // QApplication
    QApplication app(argc, argv);

    // UIMainWindow
    MainWindow main_window;

    // show UIMainWindow
    main_window.show();

    // execute QApplication
    return app.exec();
}
