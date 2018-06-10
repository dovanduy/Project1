/********************************************************************************
** Form generated from reading UI file 'QtGuiApplication4GitTest.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTGUIAPPLICATION4GITTEST_H
#define UI_QTGUIAPPLICATION4GITTEST_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QtGuiApplication4GitTestClass
{
public:
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *QtGuiApplication4GitTestClass)
    {
        if (QtGuiApplication4GitTestClass->objectName().isEmpty())
            QtGuiApplication4GitTestClass->setObjectName(QStringLiteral("QtGuiApplication4GitTestClass"));
        QtGuiApplication4GitTestClass->resize(600, 400);
        centralWidget = new QWidget(QtGuiApplication4GitTestClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        QtGuiApplication4GitTestClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(QtGuiApplication4GitTestClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 23));
        QtGuiApplication4GitTestClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(QtGuiApplication4GitTestClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        QtGuiApplication4GitTestClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(QtGuiApplication4GitTestClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        QtGuiApplication4GitTestClass->setStatusBar(statusBar);

        retranslateUi(QtGuiApplication4GitTestClass);

        QMetaObject::connectSlotsByName(QtGuiApplication4GitTestClass);
    } // setupUi

    void retranslateUi(QMainWindow *QtGuiApplication4GitTestClass)
    {
        QtGuiApplication4GitTestClass->setWindowTitle(QApplication::translate("QtGuiApplication4GitTestClass", "QtGuiApplication4GitTest", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class QtGuiApplication4GitTestClass: public Ui_QtGuiApplication4GitTestClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTGUIAPPLICATION4GITTEST_H
