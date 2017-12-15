
#include <string.h>
#include <QDebug>
#include <iostream>
#include <sstream>
#include <fstream>
#include <bitset>
#include "cmd.h"
#include "dlg_err_pin.h"
#include "dlglongerr.h"
#include "dlg_wait.h"
#ifndef INITLOGIC_H
#define INITLOGIC_H


using namespace std;

class initLogic
{
public:
  initLogic();
  ShipkaInfo  GetDeviceInfo(QString str);
  bool ChangePIN(QString str);
  bool WithoutFormat(QString str);
  bool WithFormat(QString str);
  bool Unblock(QString str);
  QStringList ComandList();
  void ErrWindows(int err);
  void ErrLongWindows(int err);
  void MessWindows(int err);
  void MessWindows(QString PUK);
  dlgLongErr* dlg_LongErr;
  dlg_err_pin* dlgErrPin;
  dlg_mess_pin* dlgMessPin;
  dlg_wait* dlgWait;
  void Wait(int data);
signals:
    void f();
};
#endif // INITLOGIC_H
