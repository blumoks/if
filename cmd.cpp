#include "cmd.h"
#include "initlogic.h"

wchar_t* wString;
int FLAG_BLOC = 0;
extern int flagPinBlock;
DWORD WINAPI creatThread1(LPVOID t);
QString strResult;

 QStringList cmd :: FoundComandList()
 {
     int numbDev = 0;
     QStringList list;

     TCHAR cmd[]=TEXT("ShInit.exe GetDeviceList");

     string strResult;
     HANDLE hPipeRead, hPipeWrite;

     SECURITY_ATTRIBUTES saAttr;
     saAttr.nLength = sizeof (saAttr);
     saAttr.bInheritHandle = TRUE;
     saAttr.lpSecurityDescriptor = NULL;

     if (!CreatePipe(&hPipeRead, &hPipeWrite, &saAttr, 0))
        return list; // меняем

     STARTUPINFO si;
     ZeroMemory(&si,sizeof(STARTUPINFO));
     si.cb = sizeof(STARTUPINFO);
     si.dwFlags     = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;
     si.hStdOutput  = hPipeWrite;
     si.hStdError   = hPipeWrite;
     si.wShowWindow = SW_HIDE;       // Prevents cmd window from flashing. Requires STARTF_USESHOWWINDOW in dwFlags.

     PROCESS_INFORMATION pi  = { 0 };


     qDebug() << "cmd";


     if (! CreateProcess( NULL, cmd, NULL, NULL, TRUE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi))
     {
        CloseHandle( hPipeWrite );
        CloseHandle( hPipeRead );
        qDebug() << "GetLastError   "<< GetLastError();
        return list;
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

      CloseHandle( hPipeWrite );
      CloseHandle( hPipeRead );
      CloseHandle( pi.hProcess );
      CloseHandle( pi.hThread );

      stringstream data;
      data << strResult;
      string str;

      while (getline(data, str, '\n'))
      {
          stringstream ss;
          ss << str;
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

    /* if(str_.indexOf("WithPUK SaveTo",0) != -1)
     {
         QString pathToFile = "";
         for(int i = str_.indexOf("WithPUK SaveTo",0)+15; i<str_.size(); i++)
            pathToFile += str_[i];
         qDebug() << pathToFile;
     }*/

    strResult= "";

    initLogic* logic = new initLogic();
    logic = new initLogic();
    qDebug() << str_;
    QByteArray ba = str_.toLocal8Bit();
    char *str = ba.data();
    wString=new wchar_t[1000];
    MultiByteToWideChar(CP_ACP, 0,str , -1, wString, 1000);


     if(str_.indexOf("Format",0) != -1)
     {
         logic->Wait(0);
     }
     else
         logic->Wait(1);

      qDebug() << strResult;

     // для смены пина

      if(strResult.indexOf("Function ChangePIN succeeded!",0) != -1 )
      {
          logic->MessWindows(0);
          return true;
      }

      if(strResult.indexOf("Function UnblockDevice failed!\r\nError: invalid PUK format.\r\nPUK can contain only symbols from 0 to 9 and from A to F",0) != -1)
      {
          logic->ErrWindows(3);
          return false;
      }

      if(strResult.indexOf("Function UnblockDevice failed!\r\nError: incorrect old PIN",0) != -1)
      {
          logic->ErrWindows(3);
          return false;
      }
      if(strResult.indexOf("Function UnblockDevice succeeded",0) != -1)
      {
          logic->MessWindows(2);
          return true;
      }
      if(strResult.indexOf("Error: invalid PUK length",0) != -1)
      {
          logic->ErrWindows(4);
          return false;
      }
      if(strResult.indexOf("Error: incorrect old PIN",0) != -1)
      {
         logic->ErrWindows(0);
          return false;
      }
      if(strResult.indexOf("Error: entered new PINs are not equal",0) != -1)
      {
          logic->ErrWindows(1);
          return false;
      }
    /*  if(strResult.indexOf("Error: Wrong length of PIN",0) != -1)
      {
          logic->ErrWindows(1);
          return false;
      }*/
      if(strResult.indexOf("Error: PUK wasn't generated. Try again after formating with PUK",0) != -1)
      {
          logic->MessWindows(8);
          return true;
      }
      if(strResult.indexOf("Error: enter old PIN to be changed",0) != -1)
      {
          logic->ErrWindows(5);
          return false;
      }

      if(strResult.indexOf("Error: PIN doesn't contain symbols from all alfabets needed",0) != -1)
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
              logic->ErrLongWindows(2);
              return false;
          }

      }

      if(strResult.indexOf("Error: entered new PINs are not equal",0) != -1)
      {
          logic->ErrWindows(6);
          return false;
      }
//if(strResult.indexOf("Function FormatDevice failed!\r\nError: Device is blocked (PIN)",0) != -1)
      if(strResult.indexOf("Error: device is blocked (PIN)",0) != -1)
      {
          logic->MessWindows(1);
          flagPinBlock = 1;
          return false;
      }
//if(strResult.indexOf("Function FormatDevice failed!\r\nError: Device is blocked (PUK)",0) != -1)
      if(strResult.indexOf("Error: Device is blocked (PUK)",0) != -1)
      {
          logic->ErrLongWindows(3);
          return false;
      }

      if(strResult.indexOf("Error: Wrong length of PIN",0) != -1)
      {
          logic->ErrLongWindows(4);
          return false;
      }

      if(strResult.indexOf("Function FormatDevice failed!",0) != -1)
      {
          logic->ErrWindows(2);
          return false;
      }
      if(strResult.indexOf("Wrong input data!",0) != -1)
      {
          return false;
      }
      if(strResult.indexOf("Cannot save PUK to file",0) != -1)
      {
          logic->MessWindows(7);
          int num = strResult.indexOf("PUK:",0);

          if(num != -1)
          {
              QString PUK = "";
              num = num+4;
              while(strResult[++num] != '\r')
                  PUK = PUK + strResult[num];
              logic->MessWindows(PUK);
          }
          return true;
      }

      if(strResult.indexOf("Function FormatDevice succeeded!",0) != -1)
      {

          logic->MessWindows(4);
          if(str_.indexOf("WithPUK SaveTo",0) != -1)
          {
                   QString pathToFile = "";
                   for(int i = str_.indexOf("WithPUK SaveTo",0)+15; i<str_.size(); i++)
                      pathToFile += str_[i];
                   qDebug() << pathToFile;
                   logic->MessWindows(pathToFile);
          }
          return true;
      }
      if(strResult.indexOf("Unknown error: 0x6",0) != -1)
      {
          if(str_.indexOf("Unblock",0) != -1)
          {
              //сделать открытие по закрытию
              logic->MessWindows(2);
              logic->ErrLongWindows(1);
              logic->MessWindows(3);
          }
          return false;
      }

      return true;
// добавить еще ошибок по разблокировке

}



 ShipkaInfo cmd ::GetInfo(QString str_)
 {
     ShipkaInfo shipkaInf;
     shipkaInf.flagDevice = -1;
     shipkaInf.typeDevice = "";
     qDebug() << str_;
     QByteArray ba = str_.toLatin1();
     char *str = ba.data();
     wchar_t* wString=new wchar_t[100];
     MultiByteToWideChar(CP_ACP, 0,str , -1, wString, 100);

     string strResult;
     HANDLE hPipeRead, hPipeWrite;

     SECURITY_ATTRIBUTES saAttr;
     saAttr.nLength = sizeof (saAttr);
     saAttr.bInheritHandle = TRUE;
     saAttr.lpSecurityDescriptor = NULL;

     if ( !CreatePipe(&hPipeRead, &hPipeWrite, &saAttr, 0) )
     {
        qDebug() << "err 0";
        return shipkaInf;
     }

     STARTUPINFO si;
     ZeroMemory(&si,sizeof(STARTUPINFO));
     si.cb = sizeof(STARTUPINFO);
     si.dwFlags     = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;
     si.hStdOutput  = hPipeWrite;
     si.hStdError   = hPipeWrite;
     si.wShowWindow = SW_HIDE;       // Prevents cmd window from flashing. Requires STARTF_USESHOWWINDOW in dwFlags.

     PROCESS_INFORMATION pi  = { 0 };

     if (! CreateProcess( NULL, wString, NULL, NULL, TRUE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi))
     {
        CloseHandle( hPipeWrite );
        CloseHandle( hPipeRead );
        qDebug() << GetLastError();
        return shipkaInf;
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

      CloseHandle( hPipeWrite );
      CloseHandle( hPipeRead );
      CloseHandle( pi.hProcess );
      CloseHandle( pi.hThread );

      qDebug() <<QString::fromStdString(strResult);
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

      CloseHandle( hPipeWrite );
      CloseHandle( hPipeRead );
      CloseHandle( pi.hProcess );
      CloseHandle( pi.hThread );

 }
