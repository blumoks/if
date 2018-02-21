#include "dlg_errpin.h"
#include "ui_dlgerrpin.h"
#include "mainwindow.h"

int FLAG_Tab;

Dlg_Err_Pin::Dlg_Err_Pin(QWidget *parent) :
    QDialog(parent,Qt::FramelessWindowHint),
    ui(new Ui::Dlg_Err_Pin)
{
    ui->setupUi(this);


