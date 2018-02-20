#include "dlglongerr.h"


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

    ShipkaLogFile* ShipkaIniFile2 = new ShipkaLogFile();
    QPoint pos = this->mapToGlobal(QPoint(0,0));


    if (codeErr == 1)
    {
        if(ShipkaIniFile2->Log)
        {
            ShipkaIniFile2->WriteToLog("Смена PIN-кода завершена с ошибкой. Неизвестная ошибка.");
        }

        if(ShipkaIniFile2->LangUtil == 1049)
            ui->lblErrMsg->setText("Смена PIN-кода завершена с ошибкой. Неизвестная ошибка.");
        else
            ui->lblErrMsg->setText("Change of PIN is completed with an error. Unknown error.");
    }
    if (codeErr == 2)
    {
        if(ShipkaIniFile2->Log)
        {
            ShipkaIniFile2->WriteToLog("Pin-код не содержит символов из всех необходимых алфовитов");
        }
        if(ShipkaIniFile2->LangUtil == 1049)
            ui->lblErrMsg->setText("Pin-код не содержит символов из всех необходимых алфовитов");
        else
            ui->lblErrMsg->setText("PIN doesn't contain symbols from all alfabets needed");
    }
    if (codeErr == 3)
    {
        if(ShipkaIniFile2->Log)
        {
            ShipkaIniFile2->WriteToLog("Форматирование завершено с ошибкой.Форматирование устройства запрещено Администратором");
        }
        if(ShipkaIniFile2->LangUtil == 1049)
            ui->lblErrMsg->setText("\tФорматирование завершено с ошибкой.\nФорматирование устройства запрещено Администратором");
        else
            ui->lblErrMsg->setText("Formatted with error. Format device disable by the Administrator");
    }
    if (codeErr == 4)
    {
        if(ShipkaIniFile2->Log)
        {
            ShipkaIniFile2->WriteToLog("Длина введенного PIN-кода не удовлетворяет установленной политике");
        }
        if(ShipkaIniFile2->LangUtil == 1049)
            ui->lblErrMsg->setText("\t        Длина введенного PIN-кода\n\tне удовлетворяет установленной политике");
        else
            ui->lblErrMsg->setText("The length of the entered PIN-code is not inferior to the old policy");
    }

    if (codeErr == 5)
    {
        if(ShipkaIniFile2->Log)
        {
            ShipkaIniFile2->WriteToLog("Ни одного криптографического устройства не обнаружено");
        }
        if(ShipkaIniFile2->LangUtil == 1049)
            ui->lblErrMsg->setText("  Ни одного криптографического устройства не обнаружено");
        else
            ui->lblErrMsg->setText("\t  No cryptographic device found");
    }
}


dlgLongErr::~dlgLongErr()
{
    delete ui;
}
