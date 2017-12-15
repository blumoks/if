#ifndef DLG_WAIT_H
#define DLG_WAIT_H

#include <QDialog>
#include <windows.h>

namespace Ui {
class dlg_wait;
}

class dlg_wait : public QDialog
{
    Q_OBJECT

public:
    explicit dlg_wait(QWidget *parent = 0,HANDLE hT = NULL);
    ~dlg_wait();
private slots:
    void funTimer();
private:
    Ui::dlg_wait *ui;
};

#endif // DLG_WAIT_H
