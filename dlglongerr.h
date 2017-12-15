#ifndef DLGLONGERR_H
#define DLGLONGERR_H

#include <QDialog>

namespace Ui {
class dlgLongErr;
}

class dlgLongErr : public QDialog
{
    Q_OBJECT

public:
    explicit dlgLongErr(QWidget *parent = 0);
    ~dlgLongErr();
    void returnErr(int codeErr);
private:
    Ui::dlgLongErr *ui;
};

#endif // DLGLONGERR_H
