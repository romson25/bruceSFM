#-------------------------------------------------
#
# Project created by QtCreator 2015-12-11T21:42:02
#
#-------------------------------------------------

QT       += testlib

TARGET = tst_matchertest
CONFIG   += console
CONFIG   += c++11

TEMPLATE = app

SOURCES += \
    matchertest.cpp

HEADERS += \
    matchertest.h

DEFINES += SRCDIR=\\\"$$PWD/\\\"


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../bruceSFM/build/release/ -lbruceSFM
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../bruceSFM/build/debug/ -lbruceSFM
else:unix:!macx: LIBS += -L$$PWD/../../bruceSFM/build/ -lbruceSFM

INCLUDEPATH += $$PWD/../../bruceSFM
DEPENDPATH += $$PWD/../../bruceSFM

INCLUDEPATH += /usr/local/include
LIBS += -L/usr/local/lib
LIBS += -lopencv_calib3d
LIBS += -lopencv_ccalib
LIBS += -lopencv_core
LIBS += -lopencv_highgui
LIBS += -lopencv_features2d
LIBS += -lopencv_xfeatures2d
LIBS += -lopencv_imgproc
LIBS += -lopencv_imgcodecs

DEPENDPATH += $$PWD/../commons
INCLUDEPATH += $$PWD/../commons
SOURCES += $$PWD/../commons/commons.cpp
HEADERS += $$PWD/../commons/commons.h
