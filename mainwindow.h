#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "simfigure.h"
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
    void doubleVsValueChanged(double doubleValue);
    void intVsValueChanged(int intValue);
    void doubleHsValueChanged(double doubleValue);
    void intHsValueChanged(int intValue);
    void doubleDampingValueChanged(double doubleValue);
    void intDampingValueChanged(int intValue);
    void doubleFrequencyValueChanged(double doubleValue);
    void intFrequencyValueChanged(int intValue);

private slots:
    void setDamping(double damping);
    void setVs(double Vs);
    void setHs(double H);
    void setFrequency(double f);
    void on_loadMotion_clicked();
    void on_btn_earthquake_clicked();
    void on_btn_sine_clicked();
    void on_btn_sweep_clicked();
    void on_btn_loadMotion_clicked();

    void notifyVsIntValueChanged(int value) {
         double doubleValue = value / 10.0;
         emit doubleVsValueChanged(doubleValue);
     }

    void notifyVsDoubleValueChanged(double value) {
         int intValue = value * 10;
         emit intVsValueChanged(intValue);
     }

    void notifyHsIntValueChanged(int value) {
         double doubleValue = value / 10.0;
         emit doubleHsValueChanged(doubleValue);
     }

    void notifyHsDoubleValueChanged(double value) {
         int intValue = value * 10;
         emit intHsValueChanged(intValue);
     }

    void notifyDampingIntValueChanged(int value) {
         double doubleValue = value / 100.0;
         emit doubleDampingValueChanged(doubleValue);
     }

    void notifyDampingDoubleValueChanged(double value) {
         int intValue = value * 100;
         emit intDampingValueChanged(intValue);
     }

    void notifyFrequencyIntValueChanged(int value) {
         double doubleValue = value / 100.0;
         emit doubleFrequencyValueChanged(doubleValue);
     }

    void notifyFrequencyDoubleValueChanged(double value) {
         int intValue = value * 100;
         emit intFrequencyValueChanged(intValue);
     }

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

    void on_MotionSelectioncomboBox_currentIndexChanged(int index);

private:
    Ui::MainWindow *ui;
    TFunctionCalc m_TFunctionCalc;

    void createActions();
    void updatePlots();
    void loadFile(const QString &fileName);

    QVector<double> m_accInput;
    QVector<double> m_accOutput;
    QVector<double> m_absFft;
    QVector<double> m_absIFft;
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
