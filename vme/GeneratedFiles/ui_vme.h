/********************************************************************************
** Form generated from reading UI file 'vme.ui'
**
** Created: Fri 13. Sep 01:35:33 2013
**      by: Qt User Interface Compiler version 4.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VME_H
#define UI_VME_H

#include <ImagePlane.h>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDockWidget>
#include <QtGui/QFrame>
#include <QtGui/QGraphicsView>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>
#include "FlatPlane.h"
#include "VolumePlane.h"

QT_BEGIN_NAMESPACE

class Ui_vmeClass
{
public:
    QAction *m_tbarOpenImageButton;
    QAction *actionMy;
    QAction *actionKid_s_head;
    QAction *actionSave_settings;
    QAction *actionLoad_settings;
    QAction *m_tbarExitButton;
    QAction *m_tbarOpeStudyButton;
    QWidget *centralWidget;
    CImagePlane *m_imagesPlane;
    CFlatPlane *m_2dStackTab;
    CVolumePlane *m_3dVoxTab;
    CVolumePlane *m_3dMeshTab;
    QToolBar *mainToolBar;
    QStatusBar *m_statusBar;
    QDockWidget *m_visPanel;
    QWidget *dockWidgetContents_2;
    QGraphicsView *m_visTF;
    QPushButton *m_vis3D;
    QPushButton *m_visLoadButton;
    QPushButton *m_visSaveButton;
    QPushButton *m_visDefaultButton;
    QPushButton *m_visUpdateButton;
    QFrame *line;
    QMenuBar *m_menuBar;
    QMenu *menuFIle;
    QMenu *menuTest;
    QMenu *menuEdit;
    QMenu *menu3D;

    void setupUi(QMainWindow *vmeClass)
    {
        if (vmeClass->objectName().isEmpty())
            vmeClass->setObjectName(QString::fromUtf8("vmeClass"));
        vmeClass->setEnabled(true);
        vmeClass->resize(961, 613);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(vmeClass->sizePolicy().hasHeightForWidth());
        vmeClass->setSizePolicy(sizePolicy);
        vmeClass->setMinimumSize(QSize(909, 613));
        vmeClass->setTabShape(QTabWidget::Rounded);
        m_tbarOpenImageButton = new QAction(vmeClass);
        m_tbarOpenImageButton->setObjectName(QString::fromUtf8("m_tbarOpenImageButton"));
        actionMy = new QAction(vmeClass);
        actionMy->setObjectName(QString::fromUtf8("actionMy"));
        actionKid_s_head = new QAction(vmeClass);
        actionKid_s_head->setObjectName(QString::fromUtf8("actionKid_s_head"));
        actionSave_settings = new QAction(vmeClass);
        actionSave_settings->setObjectName(QString::fromUtf8("actionSave_settings"));
        actionLoad_settings = new QAction(vmeClass);
        actionLoad_settings->setObjectName(QString::fromUtf8("actionLoad_settings"));
        m_tbarExitButton = new QAction(vmeClass);
        m_tbarExitButton->setObjectName(QString::fromUtf8("m_tbarExitButton"));
        m_tbarOpeStudyButton = new QAction(vmeClass);
        m_tbarOpeStudyButton->setObjectName(QString::fromUtf8("m_tbarOpeStudyButton"));
        centralWidget = new QWidget(vmeClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        centralWidget->setEnabled(true);
        m_imagesPlane = new CImagePlane(centralWidget);
        m_imagesPlane->setObjectName(QString::fromUtf8("m_imagesPlane"));
        m_imagesPlane->setEnabled(true);
        m_imagesPlane->setGeometry(QRect(80, 10, 512, 542));
        m_imagesPlane->setMinimumSize(QSize(0, 0));
        m_imagesPlane->setBaseSize(QSize(0, 0));
        m_imagesPlane->setLayoutDirection(Qt::LeftToRight);
        m_imagesPlane->setAutoFillBackground(false);
        m_imagesPlane->setStyleSheet(QString::fromUtf8("QTabBar::tab { height: 30px; width: 100px; }"));
        m_imagesPlane->setTabShape(QTabWidget::Rounded);
        m_imagesPlane->setIconSize(QSize(16, 16));
        m_imagesPlane->setMovable(true);
        m_2dStackTab = new CFlatPlane();
        m_2dStackTab->setObjectName(QString::fromUtf8("m_2dStackTab"));
        m_imagesPlane->addTab(m_2dStackTab, QString());
        m_3dVoxTab = new CVolumePlane();
        m_3dVoxTab->setObjectName(QString::fromUtf8("m_3dVoxTab"));
        m_imagesPlane->addTab(m_3dVoxTab, QString());
        m_3dMeshTab = new CVolumePlane();
        m_3dMeshTab->setObjectName(QString::fromUtf8("m_3dMeshTab"));
        m_imagesPlane->addTab(m_3dMeshTab, QString());
        vmeClass->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(vmeClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        mainToolBar->setEnabled(true);
        vmeClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        m_statusBar = new QStatusBar(vmeClass);
        m_statusBar->setObjectName(QString::fromUtf8("m_statusBar"));
        m_statusBar->setEnabled(true);
        vmeClass->setStatusBar(m_statusBar);
        m_visPanel = new QDockWidget(vmeClass);
        m_visPanel->setObjectName(QString::fromUtf8("m_visPanel"));
        sizePolicy.setHeightForWidth(m_visPanel->sizePolicy().hasHeightForWidth());
        m_visPanel->setSizePolicy(sizePolicy);
        m_visPanel->setMinimumSize(QSize(320, 560));
        m_visPanel->setMaximumSize(QSize(320, 560));
        QPalette palette;
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Base, brush);
        QBrush brush1(QColor(199, 199, 199, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        m_visPanel->setPalette(palette);
        m_visPanel->setFeatures(QDockWidget::DockWidgetMovable);
        m_visPanel->setAllowedAreas(Qt::LeftDockWidgetArea|Qt::RightDockWidgetArea);
        dockWidgetContents_2 = new QWidget();
        dockWidgetContents_2->setObjectName(QString::fromUtf8("dockWidgetContents_2"));
        m_visTF = new QGraphicsView(dockWidgetContents_2);
        m_visTF->setObjectName(QString::fromUtf8("m_visTF"));
        m_visTF->setGeometry(QRect(10, 10, 300, 200));
        sizePolicy.setHeightForWidth(m_visTF->sizePolicy().hasHeightForWidth());
        m_visTF->setSizePolicy(sizePolicy);
        m_vis3D = new QPushButton(dockWidgetContents_2);
        m_vis3D->setObjectName(QString::fromUtf8("m_vis3D"));
        m_vis3D->setGeometry(QRect(130, 430, 51, 23));
        m_visLoadButton = new QPushButton(dockWidgetContents_2);
        m_visLoadButton->setObjectName(QString::fromUtf8("m_visLoadButton"));
        m_visLoadButton->setGeometry(QRect(40, 490, 51, 23));
        m_visSaveButton = new QPushButton(dockWidgetContents_2);
        m_visSaveButton->setObjectName(QString::fromUtf8("m_visSaveButton"));
        m_visSaveButton->setGeometry(QRect(100, 490, 51, 23));
        m_visDefaultButton = new QPushButton(dockWidgetContents_2);
        m_visDefaultButton->setObjectName(QString::fromUtf8("m_visDefaultButton"));
        m_visDefaultButton->setGeometry(QRect(220, 490, 51, 23));
        m_visUpdateButton = new QPushButton(dockWidgetContents_2);
        m_visUpdateButton->setObjectName(QString::fromUtf8("m_visUpdateButton"));
        m_visUpdateButton->setGeometry(QRect(160, 490, 51, 23));
        line = new QFrame(dockWidgetContents_2);
        line->setObjectName(QString::fromUtf8("line"));
        line->setGeometry(QRect(50, 460, 211, 20));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        m_visPanel->setWidget(dockWidgetContents_2);
        vmeClass->addDockWidget(static_cast<Qt::DockWidgetArea>(1), m_visPanel);
        m_menuBar = new QMenuBar(vmeClass);
        m_menuBar->setObjectName(QString::fromUtf8("m_menuBar"));
        m_menuBar->setEnabled(true);
        m_menuBar->setGeometry(QRect(0, 0, 961, 21));
        m_menuBar->setLayoutDirection(Qt::LeftToRight);
        menuFIle = new QMenu(m_menuBar);
        menuFIle->setObjectName(QString::fromUtf8("menuFIle"));
        menuTest = new QMenu(menuFIle);
        menuTest->setObjectName(QString::fromUtf8("menuTest"));
        menuEdit = new QMenu(m_menuBar);
        menuEdit->setObjectName(QString::fromUtf8("menuEdit"));
        menu3D = new QMenu(m_menuBar);
        menu3D->setObjectName(QString::fromUtf8("menu3D"));
        vmeClass->setMenuBar(m_menuBar);

        m_menuBar->addAction(menuFIle->menuAction());
        m_menuBar->addAction(menuEdit->menuAction());
        m_menuBar->addAction(menu3D->menuAction());
        menuFIle->addAction(m_tbarOpeStudyButton);
        menuFIle->addAction(m_tbarOpenImageButton);
        menuFIle->addAction(menuTest->menuAction());
        menuFIle->addAction(actionSave_settings);
        menuFIle->addAction(actionLoad_settings);
        menuFIle->addAction(m_tbarExitButton);
        menuTest->addAction(actionMy);
        menuTest->addAction(actionKid_s_head);

        retranslateUi(vmeClass);

        m_imagesPlane->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(vmeClass);
    } // setupUi

    void retranslateUi(QMainWindow *vmeClass)
    {
        vmeClass->setWindowTitle(QApplication::translate("vmeClass", "volume medical engine", 0, QApplication::UnicodeUTF8));
        m_tbarOpenImageButton->setText(QApplication::translate("vmeClass", "Open Image", 0, QApplication::UnicodeUTF8));
        actionMy->setText(QApplication::translate("vmeClass", "my", 0, QApplication::UnicodeUTF8));
        actionKid_s_head->setText(QApplication::translate("vmeClass", "kid's head", 0, QApplication::UnicodeUTF8));
        actionSave_settings->setText(QApplication::translate("vmeClass", "Save settings", 0, QApplication::UnicodeUTF8));
        actionLoad_settings->setText(QApplication::translate("vmeClass", "Load settings", 0, QApplication::UnicodeUTF8));
        m_tbarExitButton->setText(QApplication::translate("vmeClass", "Exit", 0, QApplication::UnicodeUTF8));
        m_tbarOpeStudyButton->setText(QApplication::translate("vmeClass", "Open study", 0, QApplication::UnicodeUTF8));
        m_imagesPlane->setTabText(m_imagesPlane->indexOf(m_2dStackTab), QApplication::translate("vmeClass", "2D stack", 0, QApplication::UnicodeUTF8));
        m_imagesPlane->setTabText(m_imagesPlane->indexOf(m_3dVoxTab), QApplication::translate("vmeClass", "3D model", 0, QApplication::UnicodeUTF8));
        m_imagesPlane->setTabText(m_imagesPlane->indexOf(m_3dMeshTab), QApplication::translate("vmeClass", "3D Mesh", 0, QApplication::UnicodeUTF8));
        m_visPanel->setWindowTitle(QApplication::translate("vmeClass", "Visual panel", 0, QApplication::UnicodeUTF8));
        m_vis3D->setText(QApplication::translate("vmeClass", "3D", 0, QApplication::UnicodeUTF8));
        m_visLoadButton->setText(QApplication::translate("vmeClass", "Load", 0, QApplication::UnicodeUTF8));
        m_visSaveButton->setText(QApplication::translate("vmeClass", "Save", 0, QApplication::UnicodeUTF8));
        m_visDefaultButton->setText(QApplication::translate("vmeClass", "Default", 0, QApplication::UnicodeUTF8));
        m_visUpdateButton->setText(QApplication::translate("vmeClass", "Update", 0, QApplication::UnicodeUTF8));
        menuFIle->setTitle(QApplication::translate("vmeClass", "FIle", 0, QApplication::UnicodeUTF8));
        menuTest->setTitle(QApplication::translate("vmeClass", "test", 0, QApplication::UnicodeUTF8));
        menuEdit->setTitle(QApplication::translate("vmeClass", "Edit", 0, QApplication::UnicodeUTF8));
        menu3D->setTitle(QApplication::translate("vmeClass", "3D", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class vmeClass: public Ui_vmeClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VME_H
