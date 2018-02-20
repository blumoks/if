#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <string>
#include <tchar.h>
#include <ctime>
#include <stdio.h>
#include <QDir>
#include<QTimer>

#define MAX_SIZE 255
void valueChanged(int newValue);

DWORD WINAPI creatThread(LPVOID t);
QComboBox* combBox;
HANDLE evThrInterf;
QStringList list_;
initLogic* logic = new initLogic();
ShipkaInfo shipkaInf;
int flagPinBlock = 0;
QString strPinInput = "";

QAction *actionQuitter;
QAction *actionQuitterRu;
QAction *actionQuitterEn;
QAction *actionQuitterHelp;
QAction *actionQuitterAbout;

HANDLE evThr = CreateEvent(NULL, TRUE, TRUE, NULL);
HANDLE evThrBasic = CreateEvent(NULL, TRUE, FALSE, NULL);
HANDLE evThrGrafRefresh = CreateEvent(NULL, TRUE, TRUE, NULL);

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent,Qt::FramelessWindowHint),
    ui(new Ui::MainWindow)
{
    qDebug() << "consrtuctor";
    ui->setupUi(this);
    evThrInterf = CreateEvent(NULL, TRUE, TRUE, NULL);
    Thread();
    combBox = new QComboBox;
    combBox = ui->cmbBoxDevice;

// дорисовываем интерфейс
//  создание menuBar
    QMenu *menuFi = menuBar()->addMenu("");

// создаем кнопку Файл
    f_button = new QPushButton("Файл", this);

// устанавливаем размер и положение кнопки
    f_button->setGeometry(QRect(QPoint(10, 35), QSize(50, 20)));
    f_button->setMenu(menuFi);
    f_button->setStyleSheet("QPushButton {\n        border: 1px solid rgb(232, 232, 231);\n }\n\n QPushButton:hover {\nbackground-color: rgb(248, 238, 0);\n  border: 2px  solid rgb(205, 205, 203);\n }\n\n QPushButton::menu-indicator\n{\nimage:none\n}");
    actionQuitter = menuFi->addAction("Выход", this, SLOT(close()));
    menuFi->setStyleSheet("QMenu { \n border-image: url(\":/images/menuBar.png\") }");

    QMenu *menuLe = menuBar()->addMenu("");

// создаем кнопку Язык
    l_button = new QPushButton("Язык", this);

// устанавливаем размер и положение кнопки
    l_button->setGeometry(QRect(QPoint(60, 35), QSize(50, 20)));
    l_button->setMenu(menuLe);
    l_button->setStyleSheet("QPushButton {\n        border: 1px solid rgb(232, 232, 231);\n }\n\n QPushButton:hover {\nbackground-color: rgb(248, 238, 0);\n  border: 2px  solid rgb(205, 205, 203);\n }\n\n QPushButton::menu-indicator\n{\nimage:none\n}");
    actionQuitterRu = menuLe->addAction("Русский",this,SLOT(translationRu()));
    actionQuitterEn = menuLe->addAction("Английский",this,SLOT(translationEn()));
    menuLe->setStyleSheet("QMenu { \n border-image: url(\":/images/menuBar.png\") }");

    QMenu *menuSos = menuBar()->addMenu("");

    s_button = new QPushButton("Помощь", this);
// устанавливаем размер и положение кнопки
    s_button->setGeometry(QRect(QPoint(110, 35), QSize(70, 20)));
    s_button->setMenu(menuSos);
    s_button->setStyleSheet("QPushButton {\n        border: 1px solid rgb(232, 232, 231);\n }\n\n QPushButton:hover {\nbackground-color: rgb(248, 238, 0);\n  border: 2px  solid rgb(205, 205, 203);\n }\n\n QPushButton::menu-indicator\n{\nimage:none\n}");
    actionQuitterHelp = menuSos->addAction("Справка",this,SLOT(help()));
    menuSos->setStyleSheet("QMenu { \n border-image: url(\":/images/menuBar.png\") }");
    actionQuitterAbout = menuSos->addAction("О программе...", this, SLOT(aboutProgramm()));

// определяем язык программы, проссматривая  ShInit.ini
    CHAR langId[MAX_SIZE];
    QString strPath = funPath() + "/ShInit.ini";
    qDebug() << strPath;
    QByteArray ba = strPath.toLocal8Bit();
    char *str = ba.data();

    GetPrivateProfileStringA(("LANGUAGE"), ("LangId"), ("Default"), langId, MAX_SIZE, str);
    if(GetLastError() == 2)
    {
        qDebug() << "getlasterr = 2";
 //значение языка системы
        int ret = GetSystemDefaultLangID();
        if (ret == 1049)
            translationRu();
         else
            translationEn();
    }
    else
    {
        if(GetLastError() == 0)
        {
            QString string(langId);
            qDebug() << string;
            if(string == "516")
            {
                 translationEn();
            }
            if(string == "1049")
            {
                 translationRu();
            }
        }
    }


    QObject::connect(ui->btnClose, SIGNAL(clicked()), this, SLOT(close()));
    QObject::connect(ui->btnCancel, SIGNAL(clicked()), this, SLOT(close()));
    QObject::connect(ui->btnMinim, SIGNAL(clicked()), this, SLOT(showMinimized()));

    ui->editPuk->setDisabled(true);
    ui->editPin1_2->setDisabled(true);
    ui->editPin2_2->setDisabled(true);
 }



void MainWindow::help()
{
    ShellExecuteA(0,"open",  "InitHelp.chm", 0, 0, SW_SHOWDEFAULT );
}



void MainWindow::mousePressEvent(QMouseEvent *event)
{
    // Запоминаем позицию при нажатии кнопки мыши
    mpos = event->pos();
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (mpos.x() >= 0 && event->buttons() && Qt::LeftButton)
    {
        QPoint diff = event->pos() - mpos;
        QPoint newpos = this->pos() + diff;

        this->move(newpos);
     }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *)
{
     // Очищаем старое значение позиции нажатия мыши
     mpos = QPoint(-1, -1);
}

void MainWindow::translationEn()
{
    QString strPath = funPath() + "/ShInit.ini";
    QByteArray ba = strPath.toLocal8Bit();
    char *str = ba.data();
    WritePrivateProfileStringA(("LANGUAGE"),("LangId"), ("516"),(str));

    qtLanguageTranslator.load("QtLanguage_en_US", ".");   // Загружаем перевод
    qApp->installTranslator(&qtLanguageTranslator);
    f_button->setText("File");
    f_button->setGeometry(QRect(QPoint(15, 35), QSize(38, 20)));
    l_button->setText("Language");
    l_button->setGeometry(QRect(QPoint(50, 35), QSize(74, 20)));
    s_button->setText("Help");

    actionQuitter->setText("Exit");
    actionQuitterRu->setText("Russian");
    actionQuitterEn->setText("English");
    actionQuitterHelp->setText("Help");
    actionQuitterAbout->setText("About the program...");
 }

void MainWindow::translationRu()
{
    QString strPath = funPath() + "/ShInit.ini";
    qDebug() << strPath;
    QByteArray ba = strPath.toLocal8Bit();
    char *str = ba.data();
    WritePrivateProfileStringA(("LANGUAGE"), ("LangId"), ("1049"), (str));

    qtLanguageTranslator.load("QtLanguage_ru_Ru", ".");   // Загружаем перевод
    qApp->installTranslator(&qtLanguageTranslator);
    f_button->setText("Файл");
    f_button->setGeometry(QRect(QPoint(10, 35), QSize(50, 20)));
    l_button->setText("Язык");
    l_button->setGeometry(QRect(QPoint(60, 35), QSize(50, 20)));
    s_button->setText("Помощь");

    actionQuitter->setText("Выход");
    actionQuitterRu->setText("Русский");
    actionQuitterEn->setText("Английский");
    actionQuitterHelp->setText("Справка");
    actionQuitterAbout->setText("О программе...");
}
    
QString MainWindow::funPath()
{
    QSettings cfg(QSettings::IniFormat, QSettings::UserScope, "application");
    QString config_dir = (QFileInfo(cfg.fileName()).absolutePath());
    config_dir = config_dir + "/OKB SAPR JSC";
    if(!QDir().exists(config_dir))
        QDir().mkdir(config_dir);
    config_dir = config_dir + "/ACShipka";
    if(!QDir().exists(config_dir))
        QDir().mkdir(config_dir);
    //config_dir = config_dir + "/ShPUK.txt";
    return config_dir;
}

void MainWindow::changeEvent(QEvent *event)
{
    // В случае получения события изменения языка приложения
    if (event->type() == QEvent::LanguageChange) {
        ui->retranslateUi(this);    // переведём окно заново
    }
}


void MainWindow::on_btnOk_clicked()
{
    //текущее время
    char buffer[80];
    time_t seconds = time(NULL);
    tm* timeinfo = localtime(&seconds);
    char* format = (char*)"%d.%m.%Y %H:%M:%S";
    strftime(buffer, 80, format, timeinfo);

    dInputPin = new dlq_input_pin;
    // смотрим будем ли вести лог файл
    CHAR langId[MAX_SIZE];
    FILE* ptrFile;
    bool logYes;
    QString strPath = funPath() + "/AcshParams.ini";
    QByteArray ba = strPath.toLocal8Bit();
    char* strCh = ba.data();
    GetPrivateProfileStringA(("LogFile"), ("FileName"), ("Default"), langId, MAX_SIZE, strCh);

    if(GetLastError() == 0)
        logYes = true;
    else
        false;

    if(ui->cmbBoxDevice->currentText() == "")
    {
        logic->ErrLongWindows(5);
        return ;
    }
    // проверяем флаг, что устройство инициализировано выводим ошибку, если нет

    if(((shipkaInf.flagDevice & DEVICE_NOT_INITIALIZED) ==  DEVICE_NOT_INITIALIZED) && flagPinBlock == 0 && shipkaInf.typeDevice != "SHIPKA-lite")
    {

        logic->MessWindows(6);
        return ;
    }
    ResetEvent(evThr);
    WaitForSingleObject(evThrBasic, INFINITE);
    //change pin


    if (ui->tabWidget->currentIndex() == 0)
    {
        if((ui->editOldPin->text().size() == 0 && (shipkaInf.flagDevice & PIN_NOT_SETTED) != PIN_NOT_SETTED)  || ui->editPin1->text().size() == 0 || ui->editPin2->text().size() == 0)
        {
            logic->ErrWindows(7);
            SetEvent(evThr);
            return;
        }
        QString str =  "ShInit.exe ChangePIN " + ui->cmbBoxDevice->currentText() + " " + ui->editOldPin->text() + " " + ui->editPin1->text() + " " + ui->editPin2->text();

        if(logYes)
        {
            ptrFile = fopen(langId, "a+");
            fprintf(ptrFile,"\n%s\tDevice №: %s\tДействие: Смена Pin-кода\tРезультат: ",buffer,ui->cmbBoxDevice->currentText().toStdString().c_str());
            fclose (ptrFile);
        }
       if(logic->ChangePIN(str))
        {
            ui->editOldPin->setEnabled(true);
        }

        ui->editOldPin->setText("");
        ui->editPin1->setText("");
        ui->editPin2->setText("");
    }

    //format PUK

    if (ui->tabWidget->currentIndex() == 1)
    {
        if(ui->radioButton->isChecked() == true)
        {

            if((shipkaInf.typeDevice == "SHIPKA-lite") && ((shipkaInf.flagDevice & DEVICE_NOT_INITIALIZED) ==  DEVICE_NOT_INITIALIZED))
            {
                logic->MessWindows(8);
                return ;
            }


            if((shipkaInf.flagDevice & DEVICE_NOT_FORMATED) == DEVICE_NOT_FORMATED)
            {
                logic->MessWindows(8);
                {
                    SetEvent(evThr);
                    return;
                }
            }

            logic->MessWindows(5);
            qDebug() << "typeDevice" + shipkaInf.typeDevice;
            if(shipkaInf.typeDevice == "SHIPKA-lite")
            {
                //перенести вмести со слотом
                dInputPin->exec();
                if(strPinInput.length() == 0)
                {
                    SetEvent(evThr);
                    return;
                }
            }
            else
                strPinInput = "NoPin";

            if(logYes)
            {
                ptrFile = fopen(langId, "a+");
                fprintf(ptrFile,"\n%s\tDevice №: %s\tДействие: Форматирование без PUK-кода\tРезультат: ",buffer,ui->cmbBoxDevice->currentText().toStdString().c_str());
                fclose (ptrFile);
            }

            QString  str =  "ShInit.exe Format " + ui->cmbBoxDevice->currentText() + " " + strPinInput + " " + " WithoutPUK";
            logic->WithoutFormat(str);

        }

        if(ui->radioButton_2->isChecked() == true)
        {
            if(shipkaInf.typeDevice == "SHIPKA-lite")
            {
               dInputPin->exec();
               if(strPinInput.length() == 0)
               {
                   SetEvent(evThr);
                   return;
               }
            }
            else
                strPinInput = "NoPin";

            if(logYes)
            {
                ptrFile = fopen(langId, "a+");
                fprintf(ptrFile,"\n%s\tDevice №: %s\tДействие: Форматирование с PUK-кодом\tРезультат: ",buffer,ui->cmbBoxDevice->currentText().toStdString().c_str());
                fclose (ptrFile);
            }

            QString strPath = funPath() + "/ShPUK.txt";
            QString fileName =  QFileDialog::getSaveFileName(this,QString::fromUtf8("Сохранить файл"),strPath,"*.txt",0, QFileDialog::DontConfirmOverwrite);
            if(fileName != "")
            {
                QString str =  "ShInit.exe Format " + ui->cmbBoxDevice->currentText() + " " + strPinInput + " WithPUK SaveTo \"" + fileName + "\"";

                logic->WithFormat(str);

            }

        }
        strPinInput = "";
     }


    //unblock device
    if (ui->tabWidget->currentIndex() == 2)
    {
        if(logYes)
        {
            ptrFile = fopen(langId, "a+");
            fprintf(ptrFile,"\n%s\tDevice №: %s\tДействие: Разблокировка устройства\tРезультат: ",buffer,ui->cmbBoxDevice->currentText().toStdString().c_str());
            fclose (ptrFile);
        }

        if(ui->editPuk->text().size() == 0 || ui->editPin1_2->text().size() == 0 || ui->editPin1_2->text().size() == 0)
        {
            logic->ErrWindows(7);
            SetEvent(evThr);
            return;
        }
        QString str =  "ShInit.exe Unblock " + ui->cmbBoxDevice->currentText() + " " + ui->editPuk->text() + " " + ui->editPin1_2->text() + " " + ui->editPin2_2->text();
        if(logic->Unblock(str) == true )
        {
            flagPinBlock = 0;
            ui->editPuk->setDisabled(true);
            ui->editPin1_2->setDisabled(true);
            ui->editPin2_2->setDisabled(true);
        }
        ui->editPuk->setText("");
        ui->editPin1_2->setText("");
        ui->editPin2_2->setText("");
    }

    if(flagPinBlock == 1)
    {
        ui->editPin1_2->setEnabled(true);
        ui->editPin2_2->setEnabled(true);
        ui->editPuk->setEnabled(true);
        ui->editOldPin->setText("");
        ui->editPin1->setText("");
        ui->editPin2->setText("");
    }
    if(shipkaInf.typeDevice != "SHIPKA-lite")
    {
        QString str =  "ShInit.exe GetDeviceInfo " + combBox->currentText();
        qDebug() << str;
        shipkaInf = logic->GetDeviceInfo(str);
        if((shipkaInf.flagDevice & PIN_BLOCKED) == PIN_BLOCKED)
        {
           qDebug() << "PIN_BLOCKED";
           ui->editPin1_2->setEnabled(true);
           ui->editPin2_2->setEnabled(true);
           ui->editPuk->setEnabled(true);
        }
        else
        {
            flagPinBlock = 0;
            ui->editPuk->setDisabled(true);
            ui->editPin1_2->setDisabled(true);
            ui->editPin2_2->setDisabled(true);

        }
    }
    SetEvent(evThr);

}

void MainWindow::aboutProgramm()
{
   dlgAbout = new dlg_aboutProg;
   dlgAbout->show();
}


void MainWindow::on_tabWidget_currentChanged(int index)
{
     if(index == 0)
     {
         if((shipkaInf.flagDevice & PIN_NOT_SETTED) ==  PIN_NOT_SETTED)
             ui->editOldPin->setEnabled(false);
         else
            ui->editOldPin->setEnabled(true);

     }

}



void MainWindow::Thread()
{
    qDebug() << "Thread";
    DWORD dwID = 0;
    HANDLE hTread = CreateThread(NULL,0,creatThread,0,0,&dwID);	// создаем поток для бесконечного цикла
    DWORD MyExitCode = 0;

    if(!(GetExitCodeThread (hTread, &MyExitCode))){
        qDebug() << MyExitCode;
         return;
    }


    if (MyExitCode == 1){
        qDebug() << MyExitCode;
         return;
    }
}


MainWindow::~MainWindow()
{
    delete ui;
}

DWORD WINAPI creatThread(LPVOID t)
{
    int i = 0;
    while (true)
    {
        WaitForSingleObject(evThr, INFINITE);
        qDebug() << "in logic->ComandList";
        QStringList list;
        list = logic->ComandList();


        if (list_ != list)
        {
            qDebug() << "List != List";
            ResetEvent(evThrGrafRefresh);
            list_ = list;
            combBox->clear();
            if(list_.size() == 0)
                combBox->addItems(QStringList() << "");
            else
            {
                Sleep(1000);
                combBox->addItems(list_);
            }

            SetEvent(evThrGrafRefresh);
        }
        Sleep(2000);
        qDebug() << "out logic->ComandList";

        WaitForSingleObject(evThrGrafRefresh, INFINITE);
        SetEvent(evThrBasic);
    }

    return 0;
}


void MainWindow::on_cmbBoxDevice_currentIndexChanged(const QString &arg1)
{
    WaitForSingleObject(evThrGrafRefresh, INFINITE);
    qDebug() << "обновились";
    if(list_.size() == 0)
        {
            ui->radioButton->setAutoExclusive(false);
            ui->radioButton_2->setAutoExclusive(false);
            ui->radioButton->setChecked(false);
            ui->radioButton_2->setChecked(false);
            ui->radioButton->setAutoExclusive(true);
            ui->radioButton_2->setAutoExclusive(true);
            ui->editOldPin->setEnabled(true);
       }
    else
    {
        QString str =  "ShInit.exe GetDeviceInfo " + combBox->currentText();
        shipkaInf = logic->GetDeviceInfo(str);
       // QString strDebug = shipkaInf.flagDevice;
        qDebug() << shipkaInf.flagDevice;
        if((shipkaInf.flagDevice & PUK_NOT_REQUIRED) == PUK_NOT_REQUIRED)
        {
            ui->radioButton_2->setDisabled(true);
            ui->radioButton_2->setDisabled(false);
        }
        if((shipkaInf.flagDevice & PIN_BLOCKED) == PIN_BLOCKED)
        {
           qDebug() << "PIN_BLOCKED";
           ui->editPin1_2->setEnabled(true);
           ui->editPin2_2->setEnabled(true);
           ui->editPuk->setEnabled(true);
        }

        if((shipkaInf.flagDevice & DEVICE_NOT_FORMATED) ==  DEVICE_NOT_FORMATED)
          ui->radioButton_2->setChecked(true);
        else
           ui->radioButton->setChecked(true);
    }
    SetEvent(evThrGrafRefresh);
}
