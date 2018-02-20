#include "dlglongerr.h"
#include "ui_dlglongerr.h"
#include <windows.h>
#include <QDir>
#include <QString>
#include <QSettings>
#include <QDebug>
#include <QDesktopWidget>
#define MAX_SIZE 255

dlgLongErr::dlgLongErr(QWidget *parent) :
    QDialog(parent, Qt::Window | Qt::FramelessWindowHint),
    ui(new Ui::dlgLongErr)
{
    ui->setupUi(this);
    QObject::connect(ui->btnClose, SIGNAL(clicked()), this, SLOT(close()));
    QObject::connect(ui->btnOk, SIGNAL(clicked()), this, SLOT(close()));

    QRect r = QApplication::desktop()->screenGeometry();
    move(r.width()/2 - this->width()/2,r.height()/2 - this->height()/2);
}

void dlgLongErr :: returnErr(int codeErr)
{

    QPoint pos = this->mapToGlobal(QPoint(0,0));

    qDebug() << pos.x();


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

if (codeErr == 1)
{
    if(logYes)
    {
        ptrFile = fopen(langId, "a+");
        fprintf(ptrFile,"Смена PIN-кода завершена с ошибкой. Неизвестная ошибка.");
        fclose (ptrFile);
    }

    if(string == "1049")
       ui->lblErrMsg->setText("Смена PIN-кода завершена с ошибкой. Неизвестная ошибка.");
    else
        ui->lblErrMsg->setText("Change of PIN is completed with an error. Unknown error.");
}
if (codeErr == 2)
{
    if(logYes)
    {
        ptrFile = fopen(langId, "a+");
        fprintf(ptrFile,"Pin-код не содержит символов из всех необходимых алфовитов");
        fclose (ptrFile);
    }
    if(string == "1049")
        ui->lblErrMsg->setText("Pin-код не содержит символов из всех необходимых алфовитов");
    else
        ui->lblErrMsg->setText("PIN doesn't contain symbols from all alfabets needed");
}
if (codeErr == 3)
{
    if(logYes)
    {
        ptrFile = fopen(langId, "a+");
        fprintf(ptrFile,"Форматирование завершено с ошибкой.Форматирование устройства запрещено Администратором");
        fclose (ptrFile);
    }
    if(string == "1049")
        ui->lblErrMsg->setText("\tФорматирование завершено с ошибкой.\nФорматирование устройства запрещено Администратором");
    else
        ui->lblErrMsg->setText("Formatted with error. Format device disable by the Administrator");
}
if (codeErr == 4)
{
    if(logYes)
    {
        ptrFile = fopen(langId, "a+");
        fprintf(ptrFile,"Длина введенного PIN-кода не удовлетворяет установленной политике");
        fclose (ptrFile);
    }
    if(string == "1049")
        ui->lblErrMsg->setText("\t        Длина введенного PIN-кода\n\tне удовлетворяет установленной политике");
    else
        ui->lblErrMsg->setText("The length of the entered PIN-code is not inferior to the old policy");
}

if (codeErr == 5)
{
    if(logYes)
    {
        ptrFile = fopen(langId, "a+");
        fprintf(ptrFile,"Ни одного криптографического устройства не обнаружено");
        fclose (ptrFile);
    }
    if(string == "1049")
        ui->lblErrMsg->setText("  Ни одного криптографического устройства не обнаружено");
    else
        ui->lblErrMsg->setText("\t  No cryptographic device found");
}

}


dlgLongErr::~dlgLongErr()
{
    delete ui;
}
