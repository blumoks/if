#include "shipkalogfile.h"



ShipkaLogFile::ShipkaLogFile()
{
    PathToFolderShipka = PathToFolderInfoShipka();
    Log = CreateLog();
    //Log = false;
    if(Log)
        PathToLogShipka = PathToLog();

    LangUtil = IdentifyLanguage();
}



QString ShipkaLogFile :: PathToFolderInfoShipka()
{
    QSettings cfg(QSettings::IniFormat, QSettings::UserScope, "application");
    QString config_dir = (QFileInfo(cfg.fileName()).absolutePath());
    config_dir = config_dir + "/OKB SAPR JSC";
    if(!QDir().exists(config_dir))
        QDir().mkdir(config_dir);

    config_dir = config_dir + "/ACShipka";
    if(!QDir().exists(config_dir))
        QDir().mkdir(config_dir);

    return config_dir;
}


bool ShipkaLogFile :: WriteToLog(char* str)
{
    FileLog = fopen(PathToLog(), "a+");
    fprintf(FileLog,str);
    fclose(FileLog);


}

BOOL ShipkaLogFile :: CreateLog()
{
    CHAR langId[MAX_SIZE];
    memset(langId, 0, MAX_SIZE);
    bool logYes;
    QString strPath = PathToFolderShipka + "/AcshParams.ini";
    QByteArray ba = strPath.toLocal8Bit();
    char* strCh = ba.data();
    GetPrivateProfileStringA(("LogFile"), ("FileName"), ("Default"), langId, MAX_SIZE, strCh);

    if(GetLastError() == 0)
        return TRUE;
    else
        return FALSE;
}


char* ShipkaLogFile :: PathToLog()
{
    CHAR langId[MAX_SIZE];
    memset(langId, 0, MAX_SIZE);
    bool logYes;
    QString strPath = PathToFolderShipka + "/AcshParams.ini";
    QByteArray ba = strPath.toLocal8Bit();
    char* strCh = ba.data();
    GetPrivateProfileStringA(("LogFile"), ("FileName"), ("Default"), langId, MAX_SIZE, strCh);
    return langId;
}

int ShipkaLogFile :: IdentifyLanguage()
{
    CHAR langId[MAX_SIZE];
    memset(langId, 0, MAX_SIZE);
    QString strPath = PathToFolderShipka + "/ShInit.ini";
    QByteArray ba = strPath.toLocal8Bit();
    char *str = ba.data();
    GetPrivateProfileStringA(("LANGUAGE"), ("LangId"), ("Default"), langId, MAX_SIZE, str);

    if(GetLastError() == 2)
    {
        int ret = GetSystemDefaultLangID();
        if (ret == 1049)
        {
            return 1049;
        }
         else
        {
            return 516;
        }
    }
    else
    {
        if(GetLastError() == 0)
        {
            QString string(langId);

            if(string == "516")
            {
                 return 516;
            }
            if(string == "1049")
            {
                 return 1049;
            }
        }
    }
}

void ShipkaLogFile :: ChangeLanguage(char* lang)
{
    QString strPath = PathToFolderShipka + "/ShInit.ini";
    QByteArray ba = strPath.toLocal8Bit();
    char *str = ba.data();
    WritePrivateProfileStringA(("LANGUAGE"),("LangId"), (lang),(str));

}
