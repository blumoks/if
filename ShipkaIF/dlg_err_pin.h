#ifndef DLG_ERR_PIN_H
#define DLG_ERR_PIN_H

#include <QDialog>

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
