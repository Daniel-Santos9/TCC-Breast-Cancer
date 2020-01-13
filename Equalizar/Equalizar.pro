#-------------------------------------------------
#
# Project created by QtCreator 2018-10-20T16:38:16
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = Equalizar
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    realce.cpp

INCLUDEPATH += "C:\OpenCV-QT\install\include"
LIBS += -L"C:\OpenCV-QT\install\x86\mingw\bin" \
    libopencv_core320 \
    libopencv_highgui320 \
    libopencv_videoio320 \
    libopencv_imgcodecs320 \
    libopencv_imgproc320 \
    libopencv_features2d320 \
    libopencv_calib3d320

HEADERS += \
    realce.h
