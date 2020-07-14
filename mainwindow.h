#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <simfigure.h>
#include "TFunctionCalc.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void doubleValueChanged(double doubleValue);
    void intValueChanged(int intValue);

private slots:
    void setDamping(double damping);
    void setVs(double Vs);
    void setHs(double H);

    void notifyIntValueChanged(int value) {
         double doubleValue = value / 10.0;
         emit doubleValueChanged(doubleValue);
     }

    void notifyDoubleValueChanged(double value) {
         int intValue = value * 10;
         emit intValueChanged(intValue);
     }

    /*
    void newFile();
    void open();
    void openFile(QString filename);
    bool save();
    bool saveAs();
    */
    void open();
    void about();
    void version();
    void copyright();

private:
    Ui::MainWindow *ui;
    TFunctionCalc m_TFunctionCalc;

    void createActions();
    void updatePlots();
    void loadFile(const QString &fileName);

    QVector<double> m_accInput;
    QVector<double> m_accOutput;
    QVector<double> m_time;
    QVector<double> m_freq;
    QVector<double> m_soilTF;

    SimFigure *AccOFig;
    SimFigure *FOFig;
    SimFigure *HFig;
    SimFigure *AccIFig;
    SimFigure *FIFig;

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
