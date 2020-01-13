#-------------------------------------------------
#
# Project created by QtCreator 2018-12-03T16:50:45
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = k-means
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    descritores.cpp \
    gravaDados.cpp \
    calcula_desc.cpp \
    normalizacao.cpp

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
    descritores.h \
    gravaDados.h \
    calcula_desc.h \
    normalizacao.h
