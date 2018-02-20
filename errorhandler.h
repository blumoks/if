#ifndef ERRORHANDLER_H
#define ERRORHANDLER_H

#include "dlg_err_pin.h"
#include "dlglongerr.h"
#include "dlg_wait.h"
#include "dlg_mess_pin.h"
#include <QDebug>
#include <TlHelp32.h>

class ErrorHandler
{
public:
    void ErrWindows(int err);
    void ErrLongWindows(int err);
    void MessWindows(int err);
    void MessWindows(QString PUK);
    dlgLongErr* dlg_LongErr;
    dlg_err_pin* dlgErrPin;
    dlg_mess_pin* dlgMessPin;
    dlg_wait* dlgWait;
    void Wait(int data);
    HANDLE hTread;

};

#endif // ERRORHANDLER_H
