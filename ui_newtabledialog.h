#ifndef UINEWTABLEDIALOG_H
#define UINEWTABLEDIALOG_H

#include <QDialog>

#include "data_table.h"

namespace Ui {
class UINewTableDialog;
}

class UINewTableDialog : public QDialog
{
    Q_OBJECT

public:
    explicit UINewTableDialog(QWidget *parent = 0);
    ~UINewTableDialog();

    // getters for data
    game_type getGameType() const;
    int getTableNo() const;

private:
    Ui::UINewTableDialog *ui;

    // data
    game_type gameType;
    int tableNo;

public slots:
    void setTableInfo();
};

#endif // UINEWTABLEDIALOG_H
