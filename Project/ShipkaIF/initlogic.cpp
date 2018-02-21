#include "initlogic.h"
#include "mainwindow.h"
#include<QTimer>

cmd* cm;

initLogic :: initLogic()
{
    cm = new cmd();
}

ShipkaInfo initLogic :: GetDeviceInfo(QString str)
{
    return cm->GetInfo(str);
}

bool initLogic :: ChangePIN(QString str)
{
    if( cm->Comand(str) == true)
    {
         qDebug() << "Пароль изменен";
         return true;
    }
    else
    {
         qDebug() << "Пароль не изменен";
         return false;
    }
}

bool initLogic :: WithoutFormat(QString str)
{
    if( cm->Comand(str) == true)
    {
        qDebug() << "отформатировано без пина";
        return true;
    }
    else
    {
        qDebug() << "ошибка в форматирование без пина";
        return false;
    }
}

bool initLogic :: WithFormat(QString str)
{
    if( cm->Comand(str) == true)
    {
        qDebug() << "отформатировано с пином";
        return true;
    }
    else
    {
        qDebug() << "ошибка в форматирование без пина";
        return false;
    }
}
bool initLogic :: Unblock(QString str)
{
    if( cm->Comand(str) == true)
    {
        qDebug() << "устройство разблокировано";
        return true;
    }
    else
    {
        qDebug() << "не разблокировано";
        return false;
    }
}

QStringList initLogic :: ComandList()
{
    QStringList list;
    list = cm->FoundComandList();
    return list;
}


