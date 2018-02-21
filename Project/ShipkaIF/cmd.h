#ifndef CMD_H
#define CMD_H
#include <QString>
#include <QDebug>
#include <QStringList>
#include <Windows.h>
#include "errorhandler.h"
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

struct ShipkaInfo
{
    int flagDevice;
    QString typeDevice;
};


class cmd
{
public:
   QStringList FoundComandList();
   bool Comand(QString str_);
   ShipkaInfo GetInfo(QString str_);
 };
#endif // CMD_H
