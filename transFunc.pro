QT       += core gui webchannel
unix: QT += svg opengl concurrent
win32: QT += opengl printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

win32 {
    RC_ICONS = resources/NHERI-TFT-Icon.ico
} else {
    mac {
    ICON = icons/NHERI-TFT-Icon.icns
    }
}

LIBS +=    -lmkl_core -lmkl_intel_ilp64 -lmkl_intel_lp64 -lmkl_sequential

#win32:include(../SimCenterCommon/Common/Common.pri)
win32:include(../SimCenterCommon/SimFigure/SimFigure.pri)

include(./ConanHelper.pri)


win32: include(C:\qwt-6.1.5\features\qwt.prf)
unix: include(/usr/local/qwt-6.1.4/features/qwt.prf)

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


SOURCES += \
    mainwindow.cpp \
    TFunctionCalc.cpp \
    main.cpp

HEADERS += \
    mainwindow.h \
    TFunctionCalc.h

FORMS += \
    mainwindow.ui

DISTFILES += \
    ConanHelper.pri \
    conanfile.py

RESOURCES += \
    resource.qrc

