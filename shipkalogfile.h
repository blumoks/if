#ifndef SHIPKALOGFILE_H
#define SHIPKALOGFILE_H

#include <QString>
#include <QDir>
#include <QLibraryInfo>
#include <QSettings>
#include <stdio.h>

#include <windows.h>

#define MAX_SIZE 255
#include <QTranslator>

class ShipkaLogFile
{
public:
    ShipkaLogFile();

    QString PathToFolderShipka;
    bool Log;
    int LangUtil;
    FILE* FileLog;

    void ChangeLanguage(char* lang);
    int IdentifyLanguage();
    bool WriteToLog(char* str);

private:
    QString PathToFolderInfoShipka();
    BOOL CreateLog();
    char* PathToLog();
    QString PathToLogShipka;
};

#endif // SHIPKALOGFILE_H
