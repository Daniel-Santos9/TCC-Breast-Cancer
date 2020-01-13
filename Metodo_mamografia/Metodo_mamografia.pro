#-------------------------------------------------
#
# Project created by QtCreator 2018-05-08T09:11:13
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = Metodo_mamografia
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    coletaPontos.cpp \
    descritores.cpp \
    gravaDados.cpp \
    calculo_descritores.cpp

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
    coletaPontos.h \
    descritores.h \
    gravaDados.h \
    calculo_descritores.h
