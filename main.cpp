#include "MainWindow.h"

#include <QApplication>
#include <QDir>
#include <QStandardPaths>

static QString logFilePath;


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QCoreApplication::setApplicationName("transFunc");
    QCoreApplication::setOrganizationName("SimCenter");
    QCoreApplication::setApplicationVersion("0.0");

    MainWindow w;
    w.setWindowTitle("Transfer Function Tool");
    QApplication::setWindowIcon(QIcon(":/resources/NHERI-TFT-Icon.icns"));
    w.show();
    return a.exec();
}
