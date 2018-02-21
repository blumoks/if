
#include <string.h>
#include <QDebug>
#include <iostream>
#include <sstream>
#include <fstream>
#include <bitset>
#include "cmd.h"

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
};
#endif // INITLOGIC_H
