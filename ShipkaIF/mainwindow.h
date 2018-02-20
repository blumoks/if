#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QMouseEvent>
#include <QPoint>
#include "QDebug"
#include <QtGui>
#include <QMenuBar>
#include <QTabWidget>
#include <QLineEdit>
#include <QMessageBox>
#include <QFileDialog>
#include <QSettings>
#include "dlg_aboutprog.h"
#include "initlogic.h"
#include "cmd.h"
#include "dlq_input_pin.h"
#include "dlg_mess_pin.h"
#include <QTranslator>
#include <QLibraryInfo>
#include <windows.h>
#define DEVICE_NOT_INITIALIZED	(0x00000001)
#define DEVICE_NOT_FORMATED		(0x00000002)
#define PIN_NOT_SETTED			(0x00000004)
#define PUK_NOT_SETTED			(0x00000008)
#define PUK_NOT_REQUIRED		(0x00000010)
#define PIN_BLOCKED				(0x00000020)
#define PUK_BLOCKED				(0x00000040)

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public slots:
    void translationRu();
    void translationEn();
    void help();
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void CreateWind();
    void changeEvent(QEvent * event) override;
    CHAR fileLog();
    QString funPath();
    void IntetfChange();
private:
    Ui::MainWindow *ui;
    QPushButton *l_button;
    QPushButton *f_button;
    QPushButton *s_button;
    dlq_input_pin* dInputPin;
    QTranslator qtLanguageTranslator;

protected:
     void mousePressEvent(QMouseEvent *event);
     void mouseReleaseEvent(QMouseEvent *event);
     void mouseMoveEvent(QMouseEvent *event);
     dlg_aboutProg* dlgAbout;
     void Thread();


 QPoint mpos;

private slots:
 void on_btnOk_clicked();
void aboutProgramm();

void on_tabWidget_currentChanged(int index);
void on_cmbBoxDevice_currentIndexChanged(const QString &arg1);
};

#endif // MAINWINDOW_H
