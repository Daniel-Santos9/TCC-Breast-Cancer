#-------------------------------------------------
#
# Project created by QtCreator 2019-01-29T14:52:56
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = identifica_blob
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    encontra_area_blob.cpp

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
    encontra_area_blob.h
