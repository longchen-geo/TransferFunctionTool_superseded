#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QRect>
#include <QGuiApplication>
#include <QScreen>
#include <QVBoxLayout>
#include <HeaderWidget.h>
#include <FooterWidget.h>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>
#include <QDesktopServices>
#include <QUrl>
#include <QDoubleSpinBox>
#include <QLabel>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QRect rec = QGuiApplication::primaryScreen()->geometry();
    int height = this->height()<int(0.35*rec.height())?int(0.35*rec.height()):this->height();
    int width  = this->width()<int(0.35*rec.width())?int(0.35*rec.width()):this->width();
    this->resize(width, height);

    //
    // add SimCenter Header
    //

    QString appName = "<P><b><i><FONT COLOR='#000000' FONT SIZE = 4>";
    appName.append(QString("Transfer Function Tool"));
    appName.append("</i></b></P></br>");
    ui->header->setHeadingText(appName);

    // ------------------------------------------------------------------------
    // Add figures
    ui->AccOFig->showAxisControls(false);
    ui->AccOFig->setMinimumHeight(150);
    ui->AccOFig->setXLabel("Time [s]");
    ui->AccOFig->setYLabel("Accel. [g]");
    ui->AccOFig->setLabelFontSize(8);

    ui->FOFig->showAxisControls(false);
    ui->FOFig->setMinimumHeight(150);
    ui->FOFig->setXLabel("Freq. [Hz]");
    ui->FOFig->setYLabel("F. Ampl. [g-s]");
    ui->FOFig->setLabelFontSize(8);

    ui->HFig->showAxisControls(false);
    ui->HFig->setMinimumHeight(150);
    ui->HFig->setXLabel("Freq. [Hz]");
    ui->HFig->setYLabel("[H]");
    ui->HFig->setLabelFontSize(8);

    ui->FIFig->showAxisControls(false);
    ui->FIFig->setMinimumHeight(150);
    ui->FIFig->setXLabel("Freq. [Hz]");
    ui->FIFig->setYLabel("F. Ampl. [g-s]");
    ui->FIFig->setLabelFontSize(8);

    ui->AccIFig->showAxisControls(false);
    ui->AccIFig->setMinimumHeight(150);
    ui->AccIFig->setXLabel("Time [s]");
    ui->AccIFig->setYLabel("Accel. [g]");
    ui->AccIFig->setLabelFontSize(8);

    // initial values
    double damping = 10;
    double max_damping = 30;
    double Hs = 100.0;
    double max_Hs = 200;
    double Vs = 500.0;
    double max_Vs = 1000;
    m_TFunctionCalc = TFunctionCalc(damping, Hs, Vs);
    updatePlots();

    // ------------------------------------------------------------------------
    // Controls Boxes

    ui->vsSpinBox->setRange(0.1, max_Vs);
    ui->vsSpinBox->setValue(Vs);
    ui->vsSpinBox->setSingleStep(0.1);

    ui->vsSlider->setRange(1, max_Vs * 10);
    ui->vsSlider->setValue(Vs * 10);

    connect(ui->vsSpinBox, SIGNAL(valueChanged(double)),this,SLOT(notifyVsDoubleValueChanged(double)));
    connect(this, SIGNAL(intVsValueChanged(int)), ui->vsSlider, SLOT(setValue(int)));
    connect(ui->vsSlider,SIGNAL(valueChanged(int)),this,SLOT(notifyVsIntValueChanged(int)));
    connect(this, SIGNAL(doubleVsValueChanged(double)), ui->vsSpinBox, SLOT(setValue(double)));
    connect(ui->vsSpinBox,SIGNAL(valueChanged(double)),this,SLOT(setVs(double)));

    ui->thicknessSpinBox->setRange(0.1, max_Hs);
    ui->thicknessSpinBox->setValue(Hs);
    ui->thicknessSpinBox->setSingleStep(0.1);

    ui->thicknessSlider->setRange(1, max_Hs * 10);
    ui->thicknessSlider->setValue(Hs * 10);

    connect(ui->thicknessSpinBox, SIGNAL(valueChanged(double)),this,SLOT(notifyHsDoubleValueChanged(double)));
    connect(this, SIGNAL(intHsValueChanged(int)), ui->thicknessSlider, SLOT(setValue(int)));
    connect(ui->thicknessSlider,SIGNAL(valueChanged(int)),this,SLOT(notifyHsIntValueChanged(int)));
    connect(this, SIGNAL(doubleHsValueChanged(double)), ui->thicknessSpinBox, SLOT(setValue(double)));
    connect(ui->thicknessSpinBox,SIGNAL(valueChanged(double)),this,SLOT(setHs(double)));

    ui->dampingSpinBox->setRange(0.01, max_damping);
    ui->dampingSpinBox->setValue(damping);
    ui->dampingSpinBox->setSingleStep(0.01);

    ui->dampingSlider->setRange(1, max_damping * 100);
    ui->dampingSlider->setValue(damping * 100);

    connect(ui->dampingSpinBox, SIGNAL(valueChanged(double)),this,SLOT(notifyDampingDoubleValueChanged(double)));
    connect(this, SIGNAL(intDampingValueChanged(int)), ui->dampingSlider, SLOT(setValue(int)));
    connect(ui->dampingSlider,SIGNAL(valueChanged(int)),this,SLOT(notifyDampingIntValueChanged(int)));
    connect(this, SIGNAL(doubleDampingValueChanged(double)), ui->dampingSpinBox, SLOT(setValue(double)));
    connect(ui->dampingSpinBox,SIGNAL(valueChanged(double)),this, SLOT(setDamping(double)));

    this->createActions();

    ui->btn_earthquake->setChecked(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::createActions() {
    QMenu *helpMenu = menuBar()->addMenu(tr("&Help"));
    QAction *versionAct = helpMenu->addAction(tr("&Version"), this, &MainWindow::version);
    QAction *aboutAct = helpMenu->addAction(tr("&About"), this, &MainWindow::about);
    QAction *copyrightAct = helpMenu->addAction(tr("&License"), this, &MainWindow::copyright);
}


void MainWindow::on_btn_earthquake_clicked()
{
    m_TFunctionCalc.earthquakeRecord();
    updatePlots();
}
void MainWindow::on_btn_sine_clicked()
{
    m_TFunctionCalc.sinRecord();
    updatePlots();
}

void MainWindow::on_btn_cos_clicked()
{
    m_TFunctionCalc.cosRecord();
    updatePlots();
}
void MainWindow::on_btn_sweep_clicked()
{
    m_TFunctionCalc.sweepRecord();
    updatePlots();
}

void MainWindow::on_loadMotion_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this);
    if (!fileName.isEmpty())
        loadFile(fileName);
}

void MainWindow::loadFile(const QString &fileName)
{

}

void MainWindow::version()
{
    QString versionText("Version 0.0");
    QMessageBox msgBox;
    QSpacerItem *theSpacer = new QSpacerItem(700, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
    msgBox.setText(versionText);
    QGridLayout *layout = (QGridLayout*)msgBox.layout();
    layout->addItem(theSpacer, layout->rowCount(),0,1,layout->columnCount());
    msgBox.exec();
}

void MainWindow::about()
{
    QString aboutText("A SimCenter Tool For Transfer Function Calculation");
    QMessageBox msgBox;
    QSpacerItem *theSpacer = new QSpacerItem(700, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
    msgBox.setText(aboutText);
    QGridLayout *layout = (QGridLayout*)msgBox.layout();
    layout->addItem(theSpacer, layout->rowCount(),0,1,layout->columnCount());
    msgBox.exec();
}

void MainWindow::copyright()
{
  QMessageBox msgBox;
  QString copyrightText = QString("\
                          <p>\
                          The source code is licensed under a BSD 2-Clause License:<p>\
                          \"Copyright (c) 2017-2019, The Regents of the University of California (Regents).\"\
                          All rights reserved.<p>\
                          <p>\
                          Redistribution and use in source and binary forms, with or without \
                          modification, are permitted provided that the following conditions are met:\
                          <p>\
                          1. Redistributions of source code must retain the above copyright notice, this\
                          list of conditions and the following disclaimer.\
                          \
                          \
                          2. Redistributions in binary form must reproduce the above copyright notice,\
                          this list of conditions and the following disclaimer in the documentation\
                          and/or other materials provided with the distribution.\
                          <p>\
                          THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS \"AS IS\" AND\
                          ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED\
                          WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE\
                          DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR\
                          ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES\
                          (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;\
                          LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND\
          ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT\
          (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS\
          SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.\
          <p>\
          The views and conclusions contained in the software and documentation are those\
          of the authors and should not be interpreted as representing official policies,\
          either expressed or implied, of the FreeBSD Project.\
          <p>\
          REGENTS SPECIFICALLY DISCLAIMS ANY WARRANTIES, INCLUDING, BUT NOT LIMITED TO, \
          THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.\
          THE SOFTWARE AND ACCOMPANYING DOCUMENTATION, IF ANY, PROVIDED HEREUNDER IS \
          PROVIDED \"AS IS\". REGENTS HAS NO OBLIGATION TO PROVIDE MAINTENANCE, SUPPORT,\
          UPDATES, ENHANCEMENTS, OR MODIFICATIONS.\
          <p>\
          ------------------------------------------------------------------------------------\
          <p>\
          The compiled binary form of this application is licensed under a GPL Version 3 license.\
          The licenses are as published by the Free Software Foundation and appearing in the LICENSE file\
          included in the packaging of this application. \
          <p>\
          ------------------------------------------------------------------------------------\
          <p>\
          This software makes use of the QT packages (unmodified): core, gui, widgets and network\
                                                                   <p>\
                                                                   QT is copyright \"The Qt Company Ltd&quot; and licensed under the GNU Lesser General \
                                                                   Public License (version 3) which references the GNU General Public License (version 3)\
    <p>\
    The licenses are as published by the Free Software Foundation and appearing in the LICENSE file\
    included in the packaging of this application. \
    <p>\
    ");

  QSpacerItem *theSpacer = new QSpacerItem(700, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
  msgBox.setText(copyrightText);
  QGridLayout *layout = (QGridLayout*)msgBox.layout();
  layout->addItem(theSpacer, layout->rowCount(),0,1,layout->columnCount());
  msgBox.exec();

}


void MainWindow::setDamping(double damping)
{
    m_TFunctionCalc.setDamping(damping);
    m_TFunctionCalc.calculate();
    updatePlots();
}

void MainWindow::setHs(double Hs)
{
    m_TFunctionCalc.setHs(Hs);
    m_TFunctionCalc.calculate();
    updatePlots();
}

void MainWindow::setVs(double Vs)
{
    m_TFunctionCalc.setVs(Vs);
    m_TFunctionCalc.calculate();
    updatePlots();
}

void MainWindow::updatePlots()
{
    m_time = m_TFunctionCalc.getTime();
    m_accInput = m_TFunctionCalc.getAccel();
    m_freq = m_TFunctionCalc.getFreq();
    m_soilTF = m_TFunctionCalc.getSoilTF();
    m_absFft = m_TFunctionCalc.getFft();
    m_absIFft = m_TFunctionCalc.getIFft();
    m_accOutput = m_TFunctionCalc.getAccelT();

    ui->AccOFig->clear();
    ui->AccOFig->plot(m_time, m_accOutput, SimFigure::LineType::Solid, Qt::blue);

    ui->FOFig->clear();
    ui->FOFig->plot(m_freq, m_absIFft, SimFigure::LineType::Solid, Qt::black);

    ui->HFig->clear();
    ui->HFig->plot(m_freq, m_soilTF, SimFigure::LineType::Solid, Qt::red);

    ui->FIFig->clear();
    ui->FIFig->plot(m_freq, m_absFft, SimFigure::LineType::Solid, Qt::black);

    ui->AccIFig->clear();
    ui->AccIFig->plot(m_time, m_accInput, SimFigure::LineType::Solid, Qt::blue);

}
