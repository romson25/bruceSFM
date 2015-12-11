#-------------------------------------------------
#
# Project created by QtCreator 2015-12-09T20:38:04
#
#-------------------------------------------------

TARGET = bruceSFM
TEMPLATE = lib
CONFIG += c++11

DEFINES += BRUCESFM_LIBRARY

SOURCES += sfm.cpp \
    calibrator.cpp \
    ioprocessor.cpp

HEADERS += sfm.h\
        brucesfm_global.h \
    calibrator.h \
    ioprocessor.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

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
