#include "mainwindow.h"
#include <QApplication>
#include <QMessageBox>
#include <QTextCodec>

QString FlagLeng;
int main(int argc, char *argv[])
{


    QApplication a(argc, argv);
    MainWindow w;
    FlagLeng = "ru";
    HANDLE ghMutex = CreateMutex( NULL, FALSE, L"Shipka");
    DWORD result;
    result = WaitForSingleObject(ghMutex,0);

    if (result != WAIT_OBJECT_0)
    {
        w.showMaximized();
        return 0;
    }

    a.setStyleSheet("\nQMainWindow{\n    border-image: url(\":/images/window.png\") 0 0 0 0;\n	}\n\n");
    w.show();

    return a.exec();
}
