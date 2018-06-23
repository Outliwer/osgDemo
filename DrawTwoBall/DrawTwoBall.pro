QT += core
QT -= gui
QT += opengl
CONFIG += c++11

TARGET = DrawTwoBall
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    drawtwoball.cpp \
    pickhandler.cpp

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

HEADERS += \
    drawtwoball.h \
    pickhandler.h \
    libs.h


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../OpenSceneGraph-3.6.1_lib_qt/lib/ -losg
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../OpenSceneGraph-3.6.1_lib_qt/lib/ -losgd
else:unix: LIBS += -L$$PWD/../../OpenSceneGraph-3.6.1_lib_qt/lib/ -losg

INCLUDEPATH += $$PWD/../../OpenSceneGraph-3.6.1_lib_qt/include
DEPENDPATH += $$PWD/../../OpenSceneGraph-3.6.1_lib_qt/include

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../osgQt_lib/lib/ -losgQt5
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../osgQt_lib/lib/ -losgQt5d
else:unix: LIBS += -L$$PWD/../../osgQt_lib/lib/ -losgQt5

INCLUDEPATH += $$PWD/../../osgQt_lib/include
DEPENDPATH += $$PWD/../../osgQt_lib/include
