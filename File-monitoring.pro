QT = core

CONFIG += c++17 cmdline

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        FileRunner.cpp \
        consolefilelog.cpp \
        fileinfo.cpp \
        fileobserver.cpp \
        main.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    FileRunner.h \
    consolefilelog.h \
    fileinfo.h \
    fileobserver.h \
    iFileInfo.h \
    iFileLog.h \
    iFileObserver.h \
    iRunner.h
