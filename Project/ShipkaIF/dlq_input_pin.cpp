#include "dlq_input_pin.h"
#include "ui_dlq_input_pin.h"
#include "QDebug"

extern QString StrPinInput;

dlq_input_pin::dlq_input_pin(QWidget *parent) :
    QDialog(parent, Qt::FramelessWindowHint),
    ui(new Ui::dlq_input_pin)
{
    ui->setupUi(this);
    QObject::connect(ui->btnClose, SIGNAL(clicked()), this, SLOT(close()));
    QObject::connect(ui->btnCancel, SIGNAL(clicked()), this, SLOT(close()));
}

dlq_input_pin::~dlq_input_pin()
{
    delete ui;
}

void dlq_input_pin::on_btnOk_clicked()
{
    qDebug() << ui->editPin->text();
    StrPinInput = ui->editPin->text();
    //emit sendPin(ui->editPin->text());
    ui->editPin->setText("");
    this->accept();
}

void dlq_input_pin::on_btnCancel_clicked()
{
    close();
}
