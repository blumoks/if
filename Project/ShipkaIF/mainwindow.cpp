#include "mainwindow.h"
#include "ui_mainwindow.h"


DWORD WINAPI creatThread(LPVOID t);
initLogic* logic = new initLogic();

QComboBox* CombBox;
QStringList listOld;
QStringList listNew;
QString DeviceCurent = "";
QString DeviceOld = "";


int FlagPinBlock = 0;
QString StrPinInput = "";


HANDLE evThr = CreateEvent(NULL, TRUE, TRUE, NULL);
HANDLE evThrBasic = CreateEvent(NULL, TRUE, FALSE, NULL);
HANDLE evThrGrafRefresh = CreateEvent(NULL, FALSE, TRUE, NULL);


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent,Qt::FramelessWindowHint),
    ui(new Ui::MainWindow)
{
    qDebug() << "consrtuctor";

    ui->setupUi(this);
    ShipkaIniFile = new ShipkaLogFile();
    Thread();
    CombBox = new QComboBox;
    CombBox = ui->cmbBoxDevice;
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(timerForChangeInterfDevice()));
    //timer->start(1000);

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



    if(ShipkaIniFile->LangUtil == 1049)
    {
        translationRu();
        ShipkaIniFile->LangUtil = 1049;
    }
    else
    {
        translationEn();
        ShipkaIniFile->LangUtil = 516;
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

void MainWindow::closeEvent(QCloseEvent *event)
{
    qDebug() << "выход";
    BOOL WINAPI res = TerminateThread (hCreateTread,0);
    CloseHandle (hCreateTread);

    CloseHandle (evThr);
    CloseHandle (evThrBasic);
    CloseHandle (evThrGrafRefresh);

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
    ShipkaIniFile->ChangeLanguage("516");

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
    ShipkaIniFile->ChangeLanguage("1049");

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


    if(ui->cmbBoxDevice->currentText() == "")
    {
        errHadler2->ErrLongWindows(5);
        return ;
    }
    // проверяем флаг, что устройство инициализировано выводим ошибку, если нет

    if(((shipkaInf.flagDevice & DEVICE_NOT_INITIALIZED) ==  DEVICE_NOT_INITIALIZED) && FlagPinBlock == 0 && shipkaInf.typeDevice != "SHIPKA-lite")
    {

        errHadler2->MessWindows(6);
        return ;
    }
    WaitForSingleObject(evThr, INFINITE);
    ResetEvent(evThr);
    qDebug() << "Запрет на evThr";


    //change pin

    if (ui->tabWidget->currentIndex() == 0)
    {
        if((ui->editOldPin->text().size() == 0 && (shipkaInf.flagDevice & PIN_NOT_SETTED) != PIN_NOT_SETTED)  || ui->editPin1->text().size() == 0 || ui->editPin2->text().size() == 0)
        {
            errHadler2->ErrWindows(7);
            SetEvent(evThr);
            return;
        }

        QString str =  "ShInit.exe ChangePIN " + ui->cmbBoxDevice->currentText() + " " + ui->editOldPin->text() + " " + ui->editPin1->text() + " " + ui->editPin2->text();
        QString pStr = ParserStr(str);
        if(ShipkaIniFile->Log)
        {
            char strLog[255];
            sprintf (strLog, "\n%s\tDevice №: %s\tДействие: Смена Pin-кода\tРезультат: ", buffer,ui->cmbBoxDevice->currentText().toStdString().c_str());
            ShipkaIniFile->WriteToLog(strLog);

        }

        logic->ChangePIN(pStr);

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
                errHadler2->MessWindows(8);
                SetEvent(evThr);
                return ;
            }


            if((shipkaInf.flagDevice & DEVICE_NOT_FORMATED) == DEVICE_NOT_FORMATED)
            {
                errHadler2->MessWindows(8);
                {
                    SetEvent(evThr);
                    return;
                }
            }

            errHadler2->MessWindows(5);
            qDebug() << "typeDevice" + shipkaInf.typeDevice;
            if(shipkaInf.typeDevice == "SHIPKA-lite")
            {
                //перенести вмести со слотом
                dInputPin->exec();
                if(StrPinInput.length() == 0)
                {
                    SetEvent(evThr);
                    return;
                }
                QString str =  "ShInit.exe CheckPIN " + ui->cmbBoxDevice->currentText() + " " + StrPinInput + " " + StrPinInput + " " + StrPinInput;
                if(!logic->ChangePIN(str))
                {
                    SetEvent(evThr);
                    return;
                }
            }
            else
                StrPinInput = "NoPin";

            if(ShipkaIniFile->Log)
            {
                char strLog[255];
                sprintf (strLog, "\n%s\tDevice №: %s\tДействие: Форматирование без PUK-кода\tРезультат: ", buffer,ui->cmbBoxDevice->currentText().toStdString().c_str());
                ShipkaIniFile->WriteToLog(strLog);

            }

            QString  str =  "ShInit.exe Format " + ui->cmbBoxDevice->currentText() + " " + StrPinInput + " " + " WithoutPUK";
            logic->WithoutFormat(str);

        }

        if(ui->radioButton_2->isChecked() == true)
        {
            if(shipkaInf.typeDevice == "SHIPKA-lite")
            {
               dInputPin->exec();
               if(StrPinInput.length() == 0)
               {
                   SetEvent(evThr);
                   return;
               }
               QString str =  "ShInit.exe CheckPIN " + ui->cmbBoxDevice->currentText() + " " + StrPinInput + " " + StrPinInput + " " + StrPinInput;
               if(!logic->ChangePIN(str))
               {
                   SetEvent(evThr);
                   return;
               }
            }
            else
                StrPinInput = "NoPin";

            if(ShipkaIniFile->Log)
            {
                char strLog[255];
                sprintf (strLog, "\n%s\tDevice №: %s\tДействие: Форматирование с PUK-кодом\tРезультат: ", buffer,ui->cmbBoxDevice->currentText().toStdString().c_str());
                ShipkaIniFile->WriteToLog(strLog);

            }

            QString strPath = ShipkaIniFile->PathToFolderShipka + "/ShPUK.txt";
            QString fileName =  QFileDialog::getSaveFileName(this,QString::fromUtf8("Сохранить файл"),strPath,"*.txt",0, QFileDialog::DontConfirmOverwrite);
            if(fileName != "")
            {
                QString str =  "ShInit.exe Format " + ui->cmbBoxDevice->currentText() + " " + StrPinInput + " WithPUK SaveTo \"" + fileName + "\"";
                logic->WithFormat(str);
            }

        }
        StrPinInput = "";
     }


    //unblock device
    if (ui->tabWidget->currentIndex() == 2)
    {
        if(ShipkaIniFile->Log)
        {
            char strLog[255];
            sprintf (strLog, "\n%s\tDevice №: %s\tДействие: Разблокировка устройства\tРезультат: ", buffer,ui->cmbBoxDevice->currentText().toStdString().c_str());
            ShipkaIniFile->WriteToLog(strLog);

        }

        if(ui->editPuk->text().size() == 0 || ui->editPin1_2->text().size() == 0 || ui->editPin1_2->text().size() == 0)
        {
            errHadler2->ErrWindows(7);
            SetEvent(evThr);
            return;
        }
        QString str =  "ShInit.exe Unblock " + ui->cmbBoxDevice->currentText() + " " + ui->editPuk->text() + " " + ui->editPin1_2->text() + " " + ui->editPin2_2->text();
        QString pStr = ParserStr(str);

        if(logic->Unblock(pStr) == true )
        {
            FlagPinBlock = 0;
            ui->editPuk->setDisabled(true);
            ui->editPin1_2->setDisabled(true);
            ui->editPin2_2->setDisabled(true);
        }
        str =  "ShInit.exe CheckPIN " + ui->cmbBoxDevice->currentText() + " " + "OKBSAPR_" + " " + ui->editPin1_2->text() + " " + ui->editPin2_2->text();
        pStr = ParserStr(str);
        logic->ChangePIN(pStr);

        ui->editPuk->setText("");
        ui->editPin1_2->setText("");
        ui->editPin2_2->setText("");
    }

    if(FlagPinBlock == 1)
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
        QString str =  "ShInit.exe GetDeviceInfo " + CombBox->currentText();
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
            FlagPinBlock = 0;
            ui->editPuk->setDisabled(true);
            ui->editPin1_2->setDisabled(true);
            ui->editPin2_2->setDisabled(true);

        }
        if((shipkaInf.flagDevice & PIN_NOT_SETTED) ==  PIN_NOT_SETTED)
            ui->editOldPin->setEnabled(false);
        else
           ui->editOldPin->setEnabled(true);
    }
    SetEvent(evThr);

}

void MainWindow::aboutProgramm()
{
   dlgAbout = new dlg_aboutProg;
   dlgAbout->show();
}



void MainWindow::Thread()
{
    qDebug() << "in Thread";
    DWORD dwID = 0;



    hCreateTread = CreateThread(NULL,0,creatThread,0,0,&dwID);	// создаем поток для бесконечного цикла
    DWORD MyExitCode = 0;

    if(!(GetExitCodeThread (hCreateTread, &MyExitCode))){
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

        while (true)
        {

            WaitForSingleObject(evThr, INFINITE);
            ResetEvent(evThr);
            qDebug() << "in logic->ComandList";

            ResetEvent(evThrGrafRefresh);
            listNew = logic->ComandList();


            if (listOld != listNew)
            {
                qDebug() << "List != List";

                listOld = listNew;
                CombBox->clear();
                if(listOld.size() == 0)
                    CombBox->addItems(QStringList() << "");
                else
                {
                    CombBox->addItems(listOld);
                }


            }
            SetEvent(evThrGrafRefresh);
            //SetEvent(evThrBasic);
            SetEvent(evThr);
            qDebug() << "out logic->ComandList";
            qDebug() << "ЗРазрешение на Basic";
            Sleep(2000);


            WaitForSingleObject(evThrGrafRefresh, INFINITE);


        }
        return 0;
}


void MainWindow::on_cmbBoxDevice_currentIndexChanged(const QString &arg1)
{

    WaitForSingleObject(evThrGrafRefresh, INFINITE);
    ResetEvent(evThrGrafRefresh);


    if(listOld.size() == 0)
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

        QString str =  "ShInit.exe GetDeviceInfo " + CombBox->currentText();
        shipkaInf = logic->GetDeviceInfo(str);

        if((shipkaInf.flagDevice & PUK_NOT_REQUIRED) == PUK_NOT_REQUIRED)
        {
            ui->radioButton_2->setDisabled(true);
            ui->radioButton_2->setDisabled(false);
        }
        if((shipkaInf.flagDevice & PIN_BLOCKED) == PIN_BLOCKED && shipkaInf.typeDevice != "SHIPKA-lite")
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

        if((shipkaInf.flagDevice & PIN_NOT_SETTED) ==  PIN_NOT_SETTED && shipkaInf.typeDevice != "SHIPKA-lite")
            ui->editOldPin->setEnabled(false);
        else
            ui->editOldPin->setEnabled(true);
        }
        DeviceOld = DeviceCurent;

    SetEvent(evThrGrafRefresh);
}


QString MainWindow::ParserStr(QString strComand)
{
    QString parseStrComand;
    int nQoute= 0;
    for(int i = 0; i < strComand.length(); i++)
    {
        if(strComand[i] == '\"')
        {

                    parseStrComand += "\"\\\"\"";
                    nQoute= 1- nQoute;
                    continue;
        }
        if(strComand[i] == '\\')
        {
                    parseStrComand += "\"\\\\\"";
                    continue;
        }
        /*case '&':
                case '<':
                case '>':
                case '|':
                case '^':
                    if(nQoute)
                    {
                        parseStrComand += "\"";
                        parseStrComand += strComand[i];
                        parseStrComand += "\"";
                        break;
                    }
                default:*/
        parseStrComand += strComand[i];


    }
    return parseStrComand;
}
