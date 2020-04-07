QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/Models/basemodel.cpp \
    src/Models/buslinemodel.cpp \
    src/Models/busmodel.cpp \
    src/Models/busstopmodel.cpp \
    src/Models/mapmodel.cpp \
    src/Models/pointmodel.cpp \
    src/Models/streetmodel.cpp \
    src/Models/timesetmodel.cpp \
    src/Models/timetablemodel.cpp \
    src/TimeLib.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    src/mapcreator.cpp \
    src/tinyxml/tinystr.cpp \
    src/tinyxml/tinyxml.cpp \
    src/tinyxml/tinyxmlerror.cpp \
    src/tinyxml/tinyxmlparser.cpp

HEADERS += \
    src/Models/basemodel.h \
    src/Models/buslinemodel.h \
    src/Models/busmodel.h \
    src/Models/busstopmodel.h \
    src/Models/mapmodel.h \
    src/Models/pointmodel.h \
    src/Models/streetmodel.h \
    src/Models/timesetmodel.h \
    src/Models/timetablemodel.h \
    src/TimeLib.h \
    src/mainwindow.h \
    src/mapcreator.h \
    src/tinyxml/tinystr.h \
    src/tinyxml/tinyxml.h

FORMS += \
    views/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
