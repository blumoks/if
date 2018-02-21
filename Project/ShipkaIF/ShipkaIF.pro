#-------------------------------------------------
#
# Project created by QtCreator 2016-08-26T14:17:04
#
#-------------------------------------------------

QT       += core gui




greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ShipkaIF
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    dlg_mess_pin.cpp \
    dlg_err_pin.cpp \
    dlg_aboutprog.cpp \
    initlogic.cpp \
    cmd.cpp \
    dlglongerr.cpp \
    dlq_input_pin.cpp \
    dlg_wait.cpp \
    errorhandler.cpp \
    shipkalogfile.cpp

HEADERS  += mainwindow.h \
    dlg_mess_pin.h \
    dlg_err_pin.h \
    dlg_aboutprog.h \
    InitLogic  \
    InitLogic \ 
    initlogic.h \
    cmd.h \
    dlglongerr.h \
    dlq_input_pin.h \
    dlg_wait.h \
    errorhandler.h \
    shipkalogfile.h

FORMS    += mainwindow.ui \
    dlg_mess_pin.ui \
    dlg_err_pin.ui \
    dlg_aboutprog.ui \
    dlglongerr.ui \
    dlq_input_pin.ui \
    dlg_wait.ui

RESOURCES += \
    resources.qrc

TRANSLATIONS += QtLanguage_en.ts
CODECFORSRC     = UTF-8

win32 {
    RC_FILE = shipka.rc

}
