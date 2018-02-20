#include "dlg_err_pin.h"

dlg_err_pin::dlg_err_pin(QWidget *parent) :
    QDialog(parent, Qt::FramelessWindowHint),
    ui(new Ui::dlg_err_pin)
{
    ui->setupUi(this);

QObject::connect(ui->btnClose, SIGNAL(clicked()), this, SLOT(close()));
QObject::connect(ui->btnOk, SIGNAL(clicked()), this, SLOT(close()));
}


void dlg_err_pin :: returnErr(int codeErr)
{
    ShipkaLogFile* ShipkaIniFile2 = new ShipkaLogFile();
    if (codeErr == 0)
    {
        if(ShipkaIniFile2->Log)
        {
            ShipkaIniFile2->WriteToLog("Неверный Pin-код");
        }
        if(ShipkaIniFile2->LangUtil == 1049)
            ui->lblErrMsg->setText("        Неверный Pin-код");
        else
            ui->lblErrMsg->setText("        Incorrect PIN");
    }
    if ( codeErr == 1)
    {
        if(ShipkaIniFile2->Log)
        {
            ShipkaIniFile2->WriteToLog("Ошибка при вводе нового Pin-кода");
        }
        if(ShipkaIniFile2->LangUtil == 1049)
            ui->lblErrMsg->setText("Ошибка при вводе нового Pin-кода");
        else
            ui->lblErrMsg->setText("     Error entering new PIN");
    }

    if ( codeErr == 2)
    {
        if(ShipkaIniFile2->Log)
        {
            ShipkaIniFile2->WriteToLog("Устройство неотформатировано");
        }

        if(ShipkaIniFile2->LangUtil == 1049)
            ui->lblErrMsg->setText("Устройство неотформатировано");
        else
            ui->lblErrMsg->setText("Device is unformatted");
    }


    if (codeErr == 3)
    {
        if(ShipkaIniFile2->Log)
        {
            ShipkaIniFile2->WriteToLog("Неверный Puk-код");
        }

        if(ShipkaIniFile2->LangUtil == 1049)
            ui->lblErrMsg->setText("       Неверный Puk-код");
        else
            ui->lblErrMsg->setText("        Incorrect PUK");
    }
    if (codeErr == 4)
    {
        if(ShipkaIniFile2->Log)
        {
            ShipkaIniFile2->WriteToLog("Неверная длина Puk-кода");
        }
        if(ShipkaIniFile2->LangUtil == 1049)
            ui->lblErrMsg->setText("    Неверная длина Puk-кода");
        else
            ui->lblErrMsg->setText("      Invalid PUK length");
    }

    if (codeErr == 5)
    {
        if(ShipkaIniFile2->Log)
        {
            ShipkaIniFile2->WriteToLog("Pin-код был изменен");
        }
        if(ShipkaIniFile2->LangUtil == 1049)
            ui->lblErrMsg->setText("      Pin-код был изменен");
        else
            ui->lblErrMsg->setText("     Enter old PIN to be changed");
    }

    if (codeErr == 6)
    {
        if(ShipkaIniFile2->Log)
        {
            ShipkaIniFile2->WriteToLog("Введенные PIN-коды не совпадают");
        }
        if(ShipkaIniFile2->LangUtil == 1049)
            ui->lblErrMsg->setText("Введенные PIN-коды не совпадают");
        else
            ui->lblErrMsg->setText("   Entered new PINs are not equal");
    }

    if (codeErr == 7)
    {
        if(ShipkaIniFile2->Log)
        {
            ShipkaIniFile2->WriteToLog("Заполните недостоющие поля");
        }
        if(ShipkaIniFile2->LangUtil == 1049)
            ui->lblErrMsg->setText("    Заполните недостоющие поля");
        else
            ui->lblErrMsg->setText("    Fill in the missing fields");
    }
}
dlg_err_pin::~dlg_err_pin()
{
    delete ui;
}
