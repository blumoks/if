#ifndef DLG_ABOUTPROG_H
#define DLG_ABOUTPROG_H

#include <QDialog>

namespace Ui {
class dlg_aboutProg;
}

class dlg_aboutProg : public QDialog
{
    Q_OBJECT

public:
    explicit dlg_aboutProg(QWidget *parent = 0);
    ~dlg_aboutProg();

private:
    Ui::dlg_aboutProg *ui;


};

#endif // DLG_ABOUTPROG_H
