QT       += core gui webchannel

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

SOURCES += \
    MainWindow.cpp \
    TFunctionCalc.cpp \
    main.cpp

HEADERS += \
    MainWindow.h \
    TFunctionCalc.h

FORMS += \
    MainWindow.ui

win32: {
    RC_ICONS = resources/transFunc_icon.ico
    INCLUDEPATH += $$quote("C:/Program Files (x86)/IntelSWTools/compilers_and_libraries_2020.1.216/windows/mkl/include")
    LIBS += -L"C:/Program Files (x86)/IntelSWTools/compilers_and_libraries_2020.1.216/windows/mkl/lib/intel64_win"
} else {
 # to do
}
LIBS +=    -lmkl_core -lmkl_intel_ilp64 -lmkl_intel_lp64 -lmkl_sequential

include(../SimCenterCommon/Common/Common.pri)
include(../SimCenterCommon/SimFigure/SimFigure.pri)
include(./conanhelper.pri)
win32: {
    include(C:\qwt-6.1.5\features\qwt.prf)
}
macos: {
    include(/usr/local/qwt-6.1.5/features/qwt.prf)
}
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    ConanHelper.pri \
    conanfile.py

RESOURCES += \
    resource.qrc

