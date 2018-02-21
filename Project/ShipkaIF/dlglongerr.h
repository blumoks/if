#ifndef DLGLONGERR_H
#define DLGLONGERR_H
#include "shipkalogfile.h"
#include <QDialog>
#include "ui_dlglongerr.h"
#include <windows.h>
#include <QDir>
#include <QString>
#include <QSettings>
#include <QDebug>
#include <QDesktopWidget>
#include "shipkalogfile.h"

#define MAX_SIZE 255

namespace Ui {
class dlgLongErr;
}

class dlgLongErr : public QDialog
{
    Q_OBJECT

public:
    explicit dlgLongErr(QWidget *parent = 0);
    ~dlgLongErr();
    void returnErr(int codeErr);
private:
    Ui::dlgLongErr *ui;
};

#endif // DLGLONGERR_H
