#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_FengyanAndroid.h"
#include <QDebug>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QScrollBar>
#include <QtCore/QDebug>
#include <QTextCodec>
#include <QMessageBox>
#include "MainFrame.h"
#include "baibao\QFLicense.h"

class FengyanAndroid : public QMainWindow
{
	Q_OBJECT

public:
	FengyanAndroid(QWidget *parent = Q_NULLPTR);
signals:
	void showmainwindow();//显示主窗口信号  
	//void quit();//退出信号  

private:
	Ui::FengyanAndroidClass ui;
	int FengyanAndroid::regCodeVerify();
	int FengyanAndroid::tokenVerify();

public slots:
	void enterBtnClicked();
	void unBindBtnClicked();
	void chongzhiBtnClicked();
};
