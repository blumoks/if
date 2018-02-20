#include "dlg_wait.h"
#include "ui_dlg_wait.h"
#include <QTimer>

HANDLE h;

dlg_wait::dlg_wait(QWidget *parent,HANDLE hT) :
    QDialog(parent, Qt::FramelessWindowHint),
    ui(new Ui::dlg_wait)
{
    ui->setupUi(this);
    h = hT;
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(funTimer()));
    timer->start(100);
}

dlg_wait::~dlg_wait()
{
    delete ui;
}


void dlg_wait::funTimer()
{
    if(WaitForSingleObject(h,INFINITE) == NULL)
        close();
}
