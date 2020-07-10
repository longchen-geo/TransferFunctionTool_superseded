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
#include <QSpinBox>
#include <QLabel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QRect rec = QGuiApplication::primaryScreen()->geometry();
    int height = this->height()<int(0.35*rec.height())?int(0.35*rec.height()):this->height();
    int width  = this->width()<int(0.35*rec.width())?int(0.35*rec.width()):this->width();
    this->resize(width, height);

    centralWidget = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout();
    centralWidget->setLayout(layout);

    //
    // add SimCenter Header
    //

    QString appName = "<P><b><i><FONT COLOR='#000000' FONT SIZE = 4>";
    appName.append(QString("Transfer Function Tool"));
    appName.append("</i></b></P></br>");
    HeaderWidget *header = new HeaderWidget();
    header->setHeadingText(appName);
    layout->addWidget(header);

    SimFigure *AccOFig = new SimFigure();
    layout->addWidget(AccOFig);
    AccOFig->removeButtons();

    SimFigure *FOFig = new SimFigure();
    layout->addWidget(FOFig);
    FOFig->removeButtons();

    SimFigure *HFig = new SimFigure();
    layout->addWidget(HFig);
    HFig->removeButtons();

    SimFigure *FIFig = new SimFigure();
    layout->addWidget(FIFig);
    FIFig->removeButtons();

    SimFigure *AccIFig = new SimFigure();
    layout->addWidget(AccIFig);
    AccIFig->removeButtons();


    // initial values
    double damping = 10;
    double max_damping = 30;
    double Hs = 100.0;
    double max_Hs = 200;
    double Vs = 500.0;
    double max_Vs = 1000;

    // ------------------------------------------------------------------------
    // Controls Boxes
    QGroupBox *groupBox = new QGroupBox(tr("Controls"));

    QHBoxLayout *layoutB = new QHBoxLayout;
    // layoutB->setColumnStretch(0,0);
    // layoutB->setRowStretch(0,0);

    QSpinBox *vsSpinBox = new QSpinBox;
    vsSpinBox->setRange(0, max_Vs);
    vsSpinBox->setValue(Vs);

    QSlider *vsSlider = new QSlider(Qt::Horizontal);
    vsSlider->setRange(0, max_Vs);
    vsSlider->setValue(Vs);

    connect(vsSpinBox, SIGNAL(valueChanged(int)),vsSlider,SLOT(setValue(int)));
    connect(vsSlider,SIGNAL(valueChanged(int)),vsSpinBox,SLOT(setValue(int)));

    QSpinBox *thicknessSpinBox = new QSpinBox;
    thicknessSpinBox->setRange(0, max_Hs);
    thicknessSpinBox->setValue(Hs);

    QSlider *thicknessSlider = new QSlider(Qt::Horizontal);
    thicknessSlider->setRange(0, max_Hs);
    thicknessSlider->setValue(Hs);

    connect(thicknessSpinBox, SIGNAL(valueChanged(int)),thicknessSlider,SLOT(setValue(int)));
    connect(thicknessSlider,SIGNAL(valueChanged(int)),thicknessSpinBox,SLOT(setValue(int)));

    QSpinBox *dampingSpinBox = new QSpinBox;
    dampingSpinBox->setRange(0, max_damping);
    dampingSpinBox->setValue(damping);

    QSlider *dampingSlider = new QSlider(Qt::Horizontal);
    dampingSlider->setRange(0, max_damping);
    dampingSlider->setValue(damping);

    connect(dampingSpinBox, SIGNAL(valueChanged(int)),dampingSlider,SLOT(setValue(int)));
    connect(dampingSlider,SIGNAL(valueChanged(int)),dampingSpinBox,SLOT(setValue(int)));

    // Add Widgets to Layout
    QGroupBox *vsBox = new QGroupBox(tr("Shear Wave Velocity [m/sec]:"));
    QVBoxLayout *layoutVs = new QVBoxLayout;
    layoutVs->addWidget(vsSpinBox);
    layoutVs->addWidget(vsSlider);
    vsBox->setLayout(layoutVs);
    layoutB->addWidget(vsBox);

    QGroupBox *thBox = new QGroupBox(tr("Thickness [m]:"));
    QVBoxLayout *layoutTh = new QVBoxLayout;
    layoutTh->addWidget(thicknessSpinBox);
    layoutTh->addWidget(thicknessSlider);
    thBox->setLayout(layoutTh);
    layoutB->addWidget(thBox);

    QGroupBox *dampingBox = new QGroupBox(tr("Damping [%]:"));
    QVBoxLayout *layoutDamping = new QVBoxLayout;
    layoutDamping->addWidget(dampingSpinBox);
    layoutDamping->addWidget(dampingSlider);
    dampingBox->setLayout(layoutDamping);
    layoutB->addWidget(dampingBox);

    groupBox->setLayout(layoutB);
    layout->addWidget(groupBox);

    this->setCentralWidget(centralWidget);

    //
    // add SimCenter footer
    //

    FooterWidget *footer = new FooterWidget();
    layout->addWidget(footer);

    //
    this->createActions();

}

MainWindow::~MainWindow()
{
    // delete ui;
}


void MainWindow::createActions() {
    QMenu *helpMenu = menuBar()->addMenu(tr("&Help"));
    QAction *versionAct = helpMenu->addAction(tr("&Version"), this, &MainWindow::version);
    QAction *aboutAct = helpMenu->addAction(tr("&About"), this, &MainWindow::about);
    QAction *copyrightAct = helpMenu->addAction(tr("&License"), this, &MainWindow::copyright);
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
