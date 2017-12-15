#include "initlogic.h"
#include "mainwindow.h"

//DWORD WINAPI creatThread(LPVOID t);

cmd* cm;
DWORD WINAPI creatThread1(LPVOID t);


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
    qDebug() << str;
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

void initLogic :: ErrLongWindows(int err)
{
    dlg_LongErr = new dlgLongErr;
    dlg_LongErr->returnErr(err);
    dlg_LongErr->exec();
}

void initLogic :: ErrWindows(int err)
{
    dlgErrPin = new dlg_err_pin;
    dlgErrPin->returnErr(err);
    dlgErrPin->exec();
}

void initLogic :: MessWindows(QString PUK)
{
    qDebug() << "NO BLOCK";
    dlgMessPin = new dlg_mess_pin();
    dlgMessPin->returnMess(PUK);
    dlgMessPin->exec();
}

void initLogic :: MessWindows(int err)
{
    dlgMessPin = new dlg_mess_pin();
    dlgMessPin->returnMess(err);
    dlgMessPin->exec();
}

void  initLogic :: Wait(int data)
{
      DWORD dwID = 0;
      HANDLE hTread = CreateThread(NULL,0,creatThread1,0,0,&dwID);
        if(data == 0)
        {
              dlgWait = new dlg_wait(0,hTread);
              dlgWait->setAttribute( Qt::WA_DeleteOnClose, true );
              dlgWait->exec();
        }
        else
        {
            WaitForSingleObject(hTread,INFINITE);
        }

}

