#ifndef DLG_MESS_PIN_H
#define DLG_MESS_PIN_H

#include <QDialog>

namespace Ui {
class dlg_mess_pin;
}

class dlg_mess_pin : public QDialog
{
    Q_OBJECT

public:
    explicit dlg_mess_pin(QWidget *parent = 0);
    ~dlg_mess_pin();
    void returnMess(int codeMess);
    void returnMess(QString PUK);

private:
    Ui::dlg_mess_pin *ui;

};

#endif // DLG_MESS_PIN_H
