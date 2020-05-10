QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
TARGET = icp
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
    src/Models/clockmodel.cpp \
    src/Models/mapmodel.cpp \
    src/Models/pathmodel.cpp \
    src/Models/pointmodel.cpp \
    src/Models/streetmodel.cpp \
    src/Models/timetablemodel.cpp \
    src/TimeLib.cpp \
    src/Views/busdetailview.cpp \
    src/Views/busstopdetailview.cpp \
    src/Views/busstopview.cpp \
    src/Views/busview.cpp \
    src/Views/clockdetailview.cpp \
    src/Views/clockview.cpp \
    src/Views/detourdetailview.cpp \
    src/Views/mapview.cpp \
    src/Views/streetdetailview.cpp \
    src/Views/streetview.cpp \
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
    src/Models/clockmodel.h \
    src/Models/mapmodel.h \
    src/Models/pathmodel.h \
    src/Models/pointmodel.h \
    src/Models/streetmodel.h \
    src/Models/timetablemodel.h \
    src/TimeLib.h \
    src/Views/busdetailview.h \
    src/Views/busstopdetailview.h \
    src/Views/busstopview.h \
    src/Views/busview.h \
    src/Views/clockdetailview.h \
    src/Views/clockview.h \
    src/Views/detourdetailview.h \
    src/Views/mapview.h \
    src/Views/streetdetailview.h \
    src/Views/streetview.h \
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
