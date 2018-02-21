#ifndef DLG_ERR_PIN_H
#define DLG_ERR_PIN_H
#include "ui_dlg_err_pin.h"
#include <windows.h>
#include <QDebug>
#include <QDir>
#include <QSettings>
#include "shipkalogfile.h"
#include <QDialog>

#define MAX_SIZE 255

namespace Ui {
class dlg_err_pin;
}

class dlg_err_pin : public QDialog
{
    Q_OBJECT

public:
    explicit dlg_err_pin(QWidget *parent = 0);
    ~dlg_err_pin();

    void returnErr(int codeErr);

private:
    Ui::dlg_err_pin *ui;
};

#endif // DLG_ERR_PIN_H
