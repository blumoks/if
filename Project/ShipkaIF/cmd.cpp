#include "cmd.h"



ErrorHandler* errHadler = new ErrorHandler();
int FLAG_BLOC = 0;
extern int FlagPinBlock;
DWORD WINAPI creatThread1(LPVOID t);
string strResult;
QString strComand;
void KillProcess();


 QStringList cmd :: FoundComandList()
 {
    QStringList list;
    int numbDev = 0;
    strResult= "";
    strComand = "ShInit.exe GetDeviceList";

    errHadler->Wait(10000);


    stringstream data;
    data << strResult;
    string strPart;
    while (getline(data, strPart, '\n'))
    {
        stringstream ss;
        ss << strPart;
        int s = 0;
        int flag = 0;
        string arg;
        while (getline(ss, arg, ' '))
        {
           if (s == 1 && flag == 1)
           {
               QString str_ = QString::fromStdString(arg);
               qDebug() << str_;
               list << str_;
           }
           if (s == 0 && arg == "DeviceID:")
           {
               flag = 1;
               numbDev++;
           }
           s++;
        }
    }
    return list;
 }

bool cmd ::Comand(QString str_)
{
    bool FLAGmess = true;
    strResult= "";

    if(str_.indexOf("CheckPIN") != -1)
    {
        FLAGmess = false;
    }

    strComand = str_;

    qDebug() << strComand;



    if(str_.indexOf("Format",0) != -1)
    {
        errHadler->Wait(0);
    }
    else
        errHadler->Wait(40000);


// разбор ошибок

    if(FLAGmess == true)
    {
        if (strResult.find("Function ChangePIN succeeded!") != std::string::npos)
        {
            errHadler->MessWindows(0);
            return true;
        }

        if (strResult.find("Function UnblockDevice failed!\r\nError: invalid PUK format.\r\nPUK can contain only symbols from 0 to 9 and from A to F") != std::string::npos)
        {
            errHadler->ErrWindows(3);
            return false;
        }

        if (strResult.find("Function UnblockDevice failed!\r\nError: incorrect old PIN") != std::string::npos)
        {
            errHadler->ErrWindows(3);
            return false;
        }
        if (strResult.find("Function UnblockDevice succeeded") != std::string::npos)
        {
            errHadler->MessWindows(2);
            return true;
        }

        if (strResult.find("Error: invalid PUK length") != std::string::npos)
        {
            errHadler->ErrWindows(4);
            return false;
        }

        if (strResult.find("Error: PUK wasn't generated. Try again after formating with PUK") != std::string::npos)
        {
            errHadler->MessWindows(8);
            return true;
        }
    }




    if (strResult.find("Error: incorrect old PIN") != std::string::npos)
    {
        errHadler->ErrWindows(0);
        return false;
    }

    if (strResult.find("Error: entered new PINs are not equal") != std::string::npos)
    {
        errHadler->ErrWindows(1);
        return false;
    }



    if (strResult.find("Error: enter old PIN to be changed") != std::string::npos)
    {
        errHadler->ErrWindows(5);
        return false;
    }

    if (strResult.find("Error: PIN doesn't contain symbols from all alfabets needed") != std::string::npos)
    {
        if(FLAG_BLOC == 0)
        {
            FLAG_BLOC = 1;
            strResult = "";
            Comand(str_);
            return false;
        }
        else
        {
            errHadler->ErrLongWindows(2);
            return false;
        }
    }

    if (strResult.find("Error: entered new PINs are not equal") != std::string::npos)
    {
        errHadler->ErrWindows(6);
        return false;
    }

    if (strResult.find("Error: device is blocked (PIN)") != std::string::npos)
    {
        errHadler->MessWindows(1);
        FlagPinBlock = 1;
        return false;
    }


    if (strResult.find("Error: Device is blocked (PUK)") != std::string::npos)
    {
        errHadler->ErrLongWindows(3);
        return false;
    }

    if (strResult.find("Error: Wrong length of PIN") != std::string::npos)
    {
        errHadler->ErrLongWindows(4);
        return false;
    }

    if (strResult.find("Function FormatDevice failed!") != std::string::npos)
    {
        errHadler->ErrWindows(2);
        return false;
    }

    if (strResult.find("Wrong input data!") != std::string::npos)
    {
        return false;
    }

    if (strResult.find("Cannot save PUK to file") != std::string::npos)
    {
        errHadler->MessWindows(7);
        int num = strResult.find("PUK:");//strResult.indexOf("PUK:",0);

        if(num != -1)
        {
            QString PUK = "";
            num = num+4;
            while(strResult[++num] != '\r')
                  PUK = PUK + strResult[num];
            errHadler->MessWindows(PUK);
         }
         return true;
    }

    if (strResult.find("Function FormatDevice succeeded!") != std::string::npos)
    {
        errHadler->MessWindows(4);
        if(str_.indexOf("WithPUK SaveTo",0) != -1)
        {
            QString pathToFile = "";
            for(int i = str_.indexOf("WithPUK SaveTo",0)+15; i<str_.size(); i++)
                pathToFile += str_[i];

            qDebug() << pathToFile;
            errHadler->MessWindows(pathToFile);
        }
        return true;
    }

    if (strResult.find("Unknown error: 0x6") != std::string::npos)
    {
        if(str_.indexOf("Unblock",0) != -1)
        {
            errHadler->MessWindows(2);
            errHadler->ErrLongWindows(1);
            errHadler->MessWindows(3);
        }
        return false;
    }
    qDebug() << "exit2";
    return true;
}


ShipkaInfo cmd ::GetInfo(QString str_)
{
    ShipkaInfo shipkaInf;
    shipkaInf.flagDevice = -1;
    shipkaInf.typeDevice = "";

    strResult= "";
    strComand = str_;



    errHadler->Wait(15000);

    size_t pos = strResult.find("DeviceID:");
    if (pos != std::string::npos)
    {
        const char* str = strResult.c_str();
        char k[8];
        char s[255];
        sscanf(str, "%*s%*d%*s%s%*s%s",&s, &k);
        shipkaInf.flagDevice = 0;
        for(int i = 0; i < strlen(k);i++)
            shipkaInf.flagDevice =  shipkaInf.flagDevice + ((k[strlen(k)-1-i] -'0') * pow(2, i));
        shipkaInf.typeDevice = s;

        qDebug() << "type" << s;
        return shipkaInf;
    }
    return shipkaInf;
}


DWORD WINAPI creatThread1(LPVOID t)
{


    qDebug() << strComand;
    wchar_t* wString;
    wString=new wchar_t[strComand.length()+1];
    memset(wString,0,strComand.length()+1);
    int n = strComand.toWCharArray(wString);
    wString[n] = L'\0';
    //MultiByteToWideChar(CP_ACP, 0,str, -1, wString, 1000);





    HANDLE hPipeRead, hPipeWrite;

    SECURITY_ATTRIBUTES saAttr;
    saAttr.nLength = sizeof (saAttr);
    saAttr.bInheritHandle = TRUE;
    saAttr.lpSecurityDescriptor = NULL;

    if (!CreatePipe(&hPipeRead, &hPipeWrite, &saAttr, 0) )
    {
        qDebug() << "err 0";
        return 0;
    }

    STARTUPINFO si;
    ZeroMemory(&si,sizeof(STARTUPINFO));
    si.cb = sizeof(STARTUPINFO);
    si.dwFlags     = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;
    si.hStdOutput  = hPipeWrite;
    si.hStdError   = hPipeWrite;
    si.wShowWindow = SW_HIDE;       // Prevents cmd window from flashing. Requires STARTF_USESHOWWINDOW in dwFlags.

    PROCESS_INFORMATION pi  = { 0 };
    qDebug() << "in CreateProcess";
    string s;
     //qDebug() << QString::fromStdString(s(wString));
    if (! CreateProcess( NULL, wString, NULL, NULL, TRUE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi))
    {
        CloseHandle( hPipeWrite );
        CloseHandle( hPipeRead );
        qDebug() <<GetLastError();
        return 0;
    }
    bool bProcessEnded = false;
    while (!bProcessEnded)
    {
        bProcessEnded = WaitForSingleObject( pi.hProcess, INFINITE) == WAIT_OBJECT_0;
        while (true)
        {
            char buf[1024];
            DWORD dwRead = 0;
            DWORD dwAvail = 0;
            if (!::PeekNamedPipe(hPipeRead, NULL, 0, NULL, &dwAvail, NULL))
                break;
            if (!dwAvail) // no data available, return
                break;

            if (!::ReadFile(hPipeRead, buf, qMin(1024 - 1, (int)dwAvail), &dwRead, NULL) || !dwRead)
                break;
            buf[dwRead] = 0;
            strResult += buf;
        }
    }
    qDebug() << QString::fromStdString(strResult);
    qDebug() << "out CreateProcess";
    CloseHandle( hPipeWrite );
    CloseHandle( hPipeRead );
    CloseHandle( pi.hProcess );
    CloseHandle( pi.hThread );
   //KillProcess();
    delete[] wString ;
 }

