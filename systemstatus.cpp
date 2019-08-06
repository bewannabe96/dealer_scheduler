#include "systemstatus.h"

#include <QMessageBox>

void SystemStatus::informDealerCreated(const QString &dlr_name)
{
    QMessageBox msg_box;
    msg_box.setText("\'" + dlr_name + "\'" + " 딜러가 성공적으로 생성되었습니다.");
    msg_box.setStandardButtons(QMessageBox::Ok);
    msg_box.exec();
}

void SystemStatus::informDealerExist(const QString &dlr_name)
{
    QMessageBox msg_box;
    msg_box.setIcon(QMessageBox::Warning);
    msg_box.setText("\'" + dlr_name + "\'" + " 딜러가 이미 존재합니다.");
    msg_box.setInformativeText("다시 한번 확인하십시오.");
    msg_box.setStandardButtons(QMessageBox::Ok);
    msg_box.exec();
}

void SystemStatus::informDealerRemoved(const QString &dlr_name)
{
    QMessageBox msg_box;
    msg_box.setText("\'" + dlr_name + "\'" + " 딜러가 삭제되었습니다.");
    msg_box.setStandardButtons(QMessageBox::Ok);
    msg_box.exec();
}

bool SystemStatus::confirmDealerDeletion(const QString &dlr_name)
{
    QMessageBox msg_box;
    msg_box.setIcon(QMessageBox::Warning);
    msg_box.setText("\'" + dlr_name + "\'" + " 딜러를 영구적으로 삭제하시겠습니까?");
    msg_box.setInformativeText("삭제된 딜러는 복구할 수 없습니다.");
    msg_box.setStandardButtons(QMessageBox::Ok|QMessageBox::Cancel);
    return msg_box.exec() == QMessageBox::Ok;
}




void SystemStatus::informTableCreated(const QString &tbl_name)
{
    QMessageBox msg_box;
    msg_box.setText("\'" + tbl_name + "\'" + " 테이블이 성공적으로 생성되었습니다.");
    msg_box.setStandardButtons(QMessageBox::Ok);
    msg_box.exec();
}

void SystemStatus::informTableExist(const QString &tbl_name)
{
    QMessageBox msg_box;
    msg_box.setIcon(QMessageBox::Warning);
    msg_box.setText("\'" + tbl_name + "\'" + " 테이블이 이미 존재합니다.");
    msg_box.setInformativeText("다시 한번 확인하십시오.");
    msg_box.setStandardButtons(QMessageBox::Ok);
    msg_box.exec();
}

void SystemStatus::informTableRemoved(const QString &tbl_name)
{
    QMessageBox msg_box;
    msg_box.setText("\'" + tbl_name + "\'" + " 테이블이 제거되었습니다.");
    msg_box.setStandardButtons(QMessageBox::Ok);
    msg_box.exec();
}

void SystemStatus::informFileNotOpened(const QString &file_name)
{
    QMessageBox msg_box;
    msg_box.setIcon(QMessageBox::Warning);
    msg_box.setText("\'" + file_name + "\'" + " 파일을 불러올 수 없습니다.");
    msg_box.setStandardButtons(QMessageBox::Ok);
    msg_box.exec();
}

void SystemStatus::informNotEnoughDealer()
{
    QMessageBox msg_box;
    msg_box.setIcon(QMessageBox::Warning);
    msg_box.setText("딜러가 부족합니다.");
    msg_box.setInformativeText(
                "현재 휴식중인 딜러가 없습니다. 딜러를 배치하지 않고 테이블을 생성합니다.");
    msg_box.setStandardButtons(QMessageBox::Ok);
    msg_box.exec();
}
