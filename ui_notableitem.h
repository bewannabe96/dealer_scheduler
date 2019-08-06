#ifndef UI_NOTABLEITEM_H
#define UI_NOTABLEITEM_H

#include <QWidget>

namespace Ui {
class UINoTableItem;
}

class UINoTableItem : public QWidget
{
    Q_OBJECT

public:
    explicit UINoTableItem(QWidget *parent = 0);
    ~UINoTableItem();

private:
    Ui::UINoTableItem *ui;
};

#endif // UI_NOTABLEITEM_H
