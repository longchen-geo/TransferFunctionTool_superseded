#include "mainwindow.h"

#include <QApplication>
#include <QDir>
#include <QStandardPaths>

static QString logFilePath;


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QCoreApplication::setApplicationName("NHERI-TFT");
    QCoreApplication::setOrganizationName("SimCenter");
    QCoreApplication::setApplicationVersion("0.9");
    // window scaling
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    MainWindow w;
    w.setWindowTitle("Transfer Function Tool");
    QApplication::setWindowIcon(QIcon(":/resources/NHERI-TFT-Icon.icns"));
    w.show();
    return a.exec();
}
