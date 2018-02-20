#include "dlg_mess_pin.h"
#include "ui_dlg_mess_pin.h"
#include <QDebug>
#include <QString>
#include <windows.h>
#include <QDir>
#include <QSettings>
#include <QtGui>
#include <QDebug>
#include <QtWidgets>
#include <QDesktopWidget>
#define MAX_SIZE 255


QVBoxLayout* layoutLab;
QLabel* label;
int code = 0;

dlg_mess_pin::dlg_mess_pin(QWidget *parent) :
    QDialog(parent, Qt::FramelessWindowHint),
    ui(new Ui::dlg_mess_pin)
{
    ui->setupUi(this);
    QObject::connect(ui->btnClose, SIGNAL(clicked()), this, SLOT(close()));
    QObject::connect(ui->btnOk, SIGNAL(clicked()), this, SLOT(close()));
    label = new QLabel();

    layoutLab = new QVBoxLayout;
    layoutLab->setContentsMargins(0,3,10,10);
    this->setLayout(layoutLab);

    label->setContentsMargins(65,5,30,0);
    layoutLab->addWidget(ui->btnClose);
    layoutLab->setAlignment(ui->btnClose,Qt::AlignTop | Qt::AlignRight);
    layoutLab->addWidget(label);

    ui->btnOk->setFixedSize(QSize(100, 30));
    ui->btnClose->setFixedSize(QSize(21, 20));

    layoutLab->addWidget(ui->btnOk);
    layoutLab->setAlignment(ui->btnOk,Qt::AlignCenter);

}

void dlg_mess_pin :: returnMess(int codeMess)
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
    config_dir = config_dir + "/AcshParams.ini";
    ba = config_dir.toLocal8Bit();
    str = ba.data();
    GetPrivateProfileStringA(("LogFile"), ("FileName"), ("Default"), langId, MAX_SIZE, str);

    if(GetLastError() == 0)
      logYes = true;
    else
        false;

    if (codeMess == 0)
    {
        if(logYes)
        {
            ptrFile = fopen(langId, "a+");
            fprintf(ptrFile,"Смена Pin-кода прошла успешно");
            fclose (ptrFile);
        }
        if(string == "1049")
            label->setText("Смена Pin-кода прошла успешно!");
        else
            label->setText("Pin changed!");
    }
    if (codeMess == 1)
    {
        if(logYes)
        {
            ptrFile = fopen(langId, "a+");
            fprintf(ptrFile, "Устройство заблокировано");
            fclose (ptrFile);
        }
        if(string == "1049")
            label->setText("Устройство заблокировано");
        else
            label->setText("Device locked");
    }
    if (codeMess == 2)
    {
        if(logYes)
        {
            ptrFile = fopen(langId, "a+");
            fprintf(ptrFile, "Устройство разблокировано");
            fclose (ptrFile);
        }
        if(string == "1049")
            label->setText("Устройство разблокировано");
        else
            label->setText("Device unlocked");
    }

    if (codeMess == 3)
    {
        if(logYes)
        {
            ptrFile = fopen(langId, "a+");
            fprintf(ptrFile, "PIN-код не был задан");
            fclose (ptrFile);
        }
        if(string == "1049")
            label->setText("PIN-код не был задан! Не забудьте задать новый PIN-код!");
        else
            label->setText("PIN was not set! Do not forget to set a new PIN!");
    }

    if (codeMess == 4)
    {
        if(logYes)
        {
            ptrFile = fopen(langId, "a+");
            fprintf(ptrFile, "Форматирование успешно завершено");
            fclose (ptrFile);
        }
        if(string == "1049")
            label->setText("Форматирование успешно завершено");
        else
            label->setText("Format completed successfully");
    }
    if (codeMess == 5)
    {
        if(string == "1049")
            label->setText("Остается действительным PUK, выработанный ранее");
        else
            label->setText("The early developed PUK is remain valid");

      code = 5;
    }
    if (codeMess == 6)
    {
        if(logYes)
        {
            ptrFile = fopen(langId, "a+");
            fprintf(ptrFile, "Устройство не неинициализировано");
            fclose (ptrFile);
        }
        if(string == "1049")
            label->setText("Устройство не неинициализировано");
        else
            label->setText("No Device startup done");
    }
    if (codeMess == 7)
    {
        if(logYes)
        {
            ptrFile = fopen(langId, "a+");
            fprintf(ptrFile, "PUK не сохранен в файл");
            fclose (ptrFile);
        }
        if(string == "1049")
            label->setText("PUK не сохранен в файл");
        else
            label->setText("Cannot save PUK to file");
    }
    if (codeMess == 8)
    {
        if(string == "1049")
            label->setText("Повторите после форматирования с Puk-кодом");
        else
            label->setText("PUK wasn't generated. Try again after formating with PUK");
    }
    label->adjustSize();

    QRect r = QApplication::desktop()->screenGeometry();
    move(r.width()/2 - (label->width()+10)/2,r.height()/2 - (this->height()+15)/2);

}

void dlg_mess_pin :: returnMess(QString PUK)
{

    label->setText("PUK: " + PUK);
    label->adjustSize();
}

dlg_mess_pin::~dlg_mess_pin()
{
    delete ui;
}

