#include "errorhandler.h"
#include <QProcess>

DWORD WINAPI creatThread1(LPVOID t);
DWORD WINAPI creatThreadDell(LPVOID t);

HANDLE GetProcessHandle(const wchar_t* szExeName);
void KillProcess();

void ErrorHandler :: ErrLongWindows(int err)
{
    dlg_LongErr = new dlgLongErr;
    dlg_LongErr->returnErr(err);
    dlg_LongErr->exec();
}

void ErrorHandler :: ErrWindows(int err)
{
    dlgErrPin = new dlg_err_pin;
    dlgErrPin->returnErr(err);
    dlgErrPin->exec();
}

void ErrorHandler :: MessWindows(QString PUK)
{
    qDebug() << "NO BLOCK";
    dlgMessPin = new dlg_mess_pin();
    dlgMessPin->returnMess(PUK);
    dlgMessPin->exec();
}

void ErrorHandler :: MessWindows(int err)
{
    dlgMessPin = new dlg_mess_pin();
    dlgMessPin->returnMess(err);
    dlgMessPin->exec();
}

void  ErrorHandler :: Wait(int data)
{

    DWORD dwID = 0;

    hTread = CreateThread(NULL,0,creatThread1,0,0,&dwID);
    if(data == 0)
    {
        dlgWait = new dlg_wait(0,hTread);
        dlgWait->setAttribute( Qt::WA_DeleteOnClose, true );
        dlgWait->exec();
    }
    else
    {
        HANDLE hTread2 = CreateThread(NULL,0,creatThreadDell,(LPVOID)data,0,&dwID);
        WaitForSingleObject(hTread,INFINITE);
        BOOL WINAPI res = TerminateThread (hTread2,0);
        CloseHandle (hTread2);

    }

        BOOL WINAPI res = TerminateThread (hTread,0);
        KillProcess();
        CloseHandle (hTread);

}

DWORD WINAPI creatThreadDell(LPVOID t)
{
    int timeLife = (int)t;
    Sleep(timeLife);
    qDebug() << "Dell process";

    KillProcess();
}

void  KillProcess()
{
    HANDLE kill = GetProcessHandle(L"ShInit.exe");
    qDebug() << kill;
    DWORD fdwExit = 0;
    GetExitCodeProcess(kill, &fdwExit);
    TerminateProcess(kill, fdwExit);
    int x = CloseHandle(kill);
    qDebug() << x;
    WaitForSingleObject(kill,INFINITE);
}

HANDLE GetProcessHandle(const wchar_t* szExeName)
{
    PROCESSENTRY32 Pc = { sizeof(PROCESSENTRY32) };
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPALL, 0);
    if (Process32First(hSnapshot, &Pc)) {
        do {
            if (!wcscmp(Pc.szExeFile, szExeName)) {
                return OpenProcess(PROCESS_ALL_ACCESS, TRUE, Pc.th32ProcessID);
            }
        } while (Process32Next(hSnapshot, &Pc));
    }
    return NULL;
}
