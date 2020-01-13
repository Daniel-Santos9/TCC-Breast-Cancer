#-------------------------------------------------
#
# Project created by QtCreator 2019-04-05T21:40:58
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = Validacao_e_interpretacao
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp

INCLUDEPATH += "C:\OpenCV-QT\install\include"
LIBS += -L"C:\OpenCV-QT\install\x86\mingw\bin" \
    libopencv_core320 \
    libopencv_highgui320 \
    libopencv_videoio320 \
    libopencv_imgcodecs320 \
    libopencv_imgproc320 \
    libopencv_features2d320 \
    libopencv_calib3d320
