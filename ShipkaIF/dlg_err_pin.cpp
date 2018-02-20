#include "dlg_err_pin.h"
#include "ui_dlg_err_pin.h"
#include <windows.h>
#include <QDebug>
#include <QDir>
#include <QSettings>
#define MAX_SIZE 255

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

    CHAR langId[MAX_SIZE];
    QSettings cfg(QSettings::IniFormat, QSettings::UserScope, "application");
    QString config_dir = (QFileInfo(cfg.fileName()).absolutePath());
    config_dir = config_dir + "/OKB SAPR JSC";
    if(!QDir().exists(config_dir))
        QDir().mkdir(config_dir);
    config_dir = config_dir + "/ACShipka";
    if(!QDir().exists(config_dir))
        QDir().mkdir(config_dir);
    QString strLang = config_dir + "/ShInit.ini";
    QByteArray ba = strLang.toLocal8Bit();
    char *str = ba.data();

    GetPrivateProfileStringA(("LANGUAGE"), ("LangId"), ("Default"), langId, MAX_SIZE, (str));

    QString string(langId);
    FILE* ptrFile;
    bool logYes;
   // memset(langId,0,MAX_SIZE);
     config_dir = config_dir + "/AcshParams.ini";
     ba = config_dir.toLocal8Bit();
     str = ba.data();
    GetPrivateProfileStringA(("LogFile"), ("FileName"), ("Default"), langId, MAX_SIZE, str);

    if(GetLastError() == 0)
      logYes = true;
    else
        false;

    if (codeErr == 0)
    {
        if(logYes)
        {
            ptrFile = fopen(langId, "a+");
            fprintf(ptrFile,"Неверный Pin-код");
            fclose (ptrFile);
        }
        if(string == "1049")
            ui->lblErrMsg->setText("        Неверный Pin-код");
        else
            ui->lblErrMsg->setText("        Incorrect PIN");
    }
    if ( codeErr == 1)
    {
        if(logYes)
        {
            ptrFile = fopen(langId, "a+");
            fprintf(ptrFile,"Ошибка при вводе нового Pin-кода");
            fclose (ptrFile);
        }
        if(string == "1049")
            ui->lblErrMsg->setText("Ошибка при вводе нового Pin-кода");
        else
            ui->lblErrMsg->setText("     Error entering new PIN");
    }

    if ( codeErr == 2)
    {
        if(logYes)
        {
            ptrFile = fopen(langId, "a+");
            fprintf(ptrFile,"Устройство неотформатировано");
            fclose (ptrFile);
        }

        if(string == "1049")
            ui->lblErrMsg->setText("Устройство неотформатировано");
        else
            ui->lblErrMsg->setText("Device is unformatted");
    }


    if (codeErr == 3)
    {
        if(logYes)
        {
            ptrFile = fopen(langId, "a+");
            fprintf(ptrFile,"Неверный Puk-код");
            fclose (ptrFile);
        }

        if(string == "1049")
            ui->lblErrMsg->setText("       Неверный Puk-код");
        else
            ui->lblErrMsg->setText("        Incorrect PUK");
    }
    if (codeErr == 4)
    {
        if(logYes)
        {
            ptrFile = fopen(langId, "a+");
            fprintf(ptrFile,"Неверная длина Puk-кода\n");
            fclose (ptrFile);
        }
        if(string == "1049")
            ui->lblErrMsg->setText("    Неверная длина Puk-кода");
        else
            ui->lblErrMsg->setText("      Invalid PUK length");
    }

    if (codeErr == 5)
    {
        if(logYes)
        {
            ptrFile = fopen(langId, "a+");
            fprintf(ptrFile,"Pin-код был изменен");
            fclose (ptrFile);
        }
        if(string == "1049")
            ui->lblErrMsg->setText("      Pin-код был изменен");
        else
            ui->lblErrMsg->setText("     Enter old PIN to be changed");
    }

    if (codeErr == 6)
    {
        if(logYes)
        {
            ptrFile = fopen(langId, "a+");
            fprintf(ptrFile,"Введенные PIN-коды не совпадают");
            fclose (ptrFile);
        }
        if(string == "1049")
            ui->lblErrMsg->setText("Введенные PIN-коды не совпадают");
        else
            ui->lblErrMsg->setText("   Entered new PINs are not equal");
    }

    if (codeErr == 7)
    {
        if(logYes)
        {
            ptrFile = fopen(langId, "a+");
            fprintf(ptrFile,"Заполните недостоющие поля");
            fclose (ptrFile);
        }
        if(string == "1049")
            ui->lblErrMsg->setText("    Заполните недостоющие поля");
        else
            ui->lblErrMsg->setText("    Fill in the missing fields");
    }
}
dlg_err_pin::~dlg_err_pin()
{
    delete ui;
}
