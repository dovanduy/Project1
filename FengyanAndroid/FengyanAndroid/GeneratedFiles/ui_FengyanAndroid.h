/********************************************************************************
** Form generated from reading UI file 'FengyanAndroid.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FENGYANANDROID_H
#define UI_FENGYANANDROID_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FengyanAndroidClass
{
public:
    QWidget *centralWidget;
    QPushButton *enterBtn;
    QPushButton *unBindBtn;
    QLabel *label;
    QLineEdit *lineEdit;
    QLabel *label_2;
    QLineEdit *chongzhiLine;
    QPushButton *chongzhiBtn;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *FengyanAndroidClass)
    {
        if (FengyanAndroidClass->objectName().isEmpty())
            FengyanAndroidClass->setObjectName(QStringLiteral("FengyanAndroidClass"));
        FengyanAndroidClass->resize(463, 298);
        centralWidget = new QWidget(FengyanAndroidClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        enterBtn = new QPushButton(centralWidget);
        enterBtn->setObjectName(QStringLiteral("enterBtn"));
        enterBtn->setGeometry(QRect(120, 90, 75, 23));
        unBindBtn = new QPushButton(centralWidget);
        unBindBtn->setObjectName(QStringLiteral("unBindBtn"));
        unBindBtn->setGeometry(QRect(340, 90, 75, 23));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(53, 50, 61, 21));
        lineEdit = new QLineEdit(centralWidget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(110, 50, 321, 20));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(50, 140, 61, 21));
        chongzhiLine = new QLineEdit(centralWidget);
        chongzhiLine->setObjectName(QStringLiteral("chongzhiLine"));
        chongzhiLine->setGeometry(QRect(110, 140, 321, 20));
        chongzhiBtn = new QPushButton(centralWidget);
        chongzhiBtn->setObjectName(QStringLiteral("chongzhiBtn"));
        chongzhiBtn->setGeometry(QRect(220, 180, 75, 23));
        FengyanAndroidClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(FengyanAndroidClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 463, 23));
        FengyanAndroidClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(FengyanAndroidClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        FengyanAndroidClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(FengyanAndroidClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        FengyanAndroidClass->setStatusBar(statusBar);

        retranslateUi(FengyanAndroidClass);

        QMetaObject::connectSlotsByName(FengyanAndroidClass);
    } // setupUi

    void retranslateUi(QMainWindow *FengyanAndroidClass)
    {
        FengyanAndroidClass->setWindowTitle(QApplication::translate("FengyanAndroidClass", "\351\243\216\347\204\261\351\201\223\346\227\240\350\276\271", Q_NULLPTR));
        enterBtn->setText(QApplication::translate("FengyanAndroidClass", "\347\231\273\351\231\206", Q_NULLPTR));
        unBindBtn->setText(QApplication::translate("FengyanAndroidClass", "\350\247\243\347\273\221", Q_NULLPTR));
        label->setText(QApplication::translate("FengyanAndroidClass", "\346\263\250\345\206\214\347\240\201\357\274\232", Q_NULLPTR));
        label_2->setText(QApplication::translate("FengyanAndroidClass", "\345\205\205\345\200\274\345\215\241\357\274\232", Q_NULLPTR));
        chongzhiBtn->setText(QApplication::translate("FengyanAndroidClass", "\345\205\205\345\200\274\346\214\211\351\222\256", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class FengyanAndroidClass: public Ui_FengyanAndroidClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FENGYANANDROID_H
