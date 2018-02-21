#ifndef DLQ_INPUT_PIN_H
#define DLQ_INPUT_PIN_H

#include <QDialog>

namespace Ui {
class dlq_input_pin;
}

class dlq_input_pin : public QDialog
{
    Q_OBJECT

public:
    explicit dlq_input_pin(QWidget *parent = 0);
    ~dlq_input_pin();


private slots:
    void on_btnOk_clicked();
    void on_btnCancel_clicked();

private:
    Ui::dlq_input_pin *ui;
};

#endif // DLQ_INPUT_PIN_H
