#include "dlg_aboutprog.h"
#include "ui_dlg_aboutprog.h"

dlg_aboutProg::dlg_aboutProg(QWidget *parent) :
    QDialog(parent, Qt::FramelessWindowHint),
    ui(new Ui::dlg_aboutProg)
{
    ui->setupUi(this);
    QObject::connect(ui->btnClose, SIGNAL(clicked()), this, SLOT(close()));
    QObject::connect(ui->btnOk, SIGNAL(clicked()), this, SLOT(close()));
}

dlg_aboutProg::~dlg_aboutProg()
{
    delete ui;
}
