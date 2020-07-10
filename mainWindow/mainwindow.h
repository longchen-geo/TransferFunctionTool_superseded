#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <simfigure.h>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    /*
    void newFile();
    void open();
    void openFile(QString filename);
    bool save();
    bool saveAs();
    */

    void about();
    void version();
    void copyright();

private:
    Ui::MainWindow *ui;

    // RockOutcrop *theRockOutcropWidget;

    void createActions();
    void setCurrentFile(const QString &fileName);
    bool saveFile(const QString &fileName);
    void loadFile(const QString &fileName);

    QMenu *fileMenu;
    QMenu *editMenu;
    QWidget *centralWidget;

    QString currentFile;

    /*
    QMenu *selectSubMenu;
    QMenu *toolsMenu;
    QMenu *optionsMenu;
    QMenu *helpMenu;
    QToolBar *fileToolBar;
    QToolBar *editToolBar;
*/
};
#endif // MAINWINDOW_H
