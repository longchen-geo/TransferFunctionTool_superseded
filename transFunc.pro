QT       += core gui webchannel

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
    MainWindow.cpp \
    TFunctionCalc.cpp \
    main.cpp

HEADERS += \
    MainWindow.h \
    TFunctionCalc.h

FORMS += \
    MainWindow.ui

INCLUDEPATH += $$quote("C:/Program Files (x86)/IntelSWTools/compilers_and_libraries_2020.1.216/windows/mkl/include")

LIBS += -L"C:/Program Files (x86)/IntelSWTools/compilers_and_libraries_2020.1.216/windows/mkl/lib/intel64_win" \
    -lmkl_core -lmkl_intel_ilp64 -lmkl_intel_lp64 -lmkl_sequential

include(../SimCenterCommon/Common/Common.pri)
include(../SimCenterCommon/SimFigure/SimFigure.pri)
win32: include(C:\qwt-6.1.5\features\qwt.prf)

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

