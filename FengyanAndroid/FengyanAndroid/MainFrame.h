#pragma once

#include <QMainWindow>
#include "ui_MainFrame.h"
#include <QMenu>
#include <QDebug>
#include <QFileDialog>
#include <QSettings>
#include "DMSoft.h"
#include "CommonUtil.h"
#include "MainSingleton.h"
#include "StartThread.h"
#include "MonitorThread.h"
#include "TimeCheckThread.h"

class MainFrame : public QMainWindow
{
	Q_OBJECT

public:
	MainFrame(QWidget *parent = Q_NULLPTR);
	~MainFrame();

private:
	Ui::MainFrame ui;
	int MainFrame::initMainDM();
	Ifire* fire;
	int MainFrame::findAndroidHander();
	MainSingleton* theMain;
	int MainFrame::setUpMainTable();
	int bindSimilatorHandler();
	int MainFrame::setUpAccountTable();
	int MainFrame::saveSingleAccuntSub(int index);
	void MainFrame::loadAllAccouts4Init();
	QString MainFrame::loadScriptConfig();
	QString MainFrame::interpreter(QString source);
	void MainFrame::startMainThread();
	//void MainFrame::loadAllMoney();
signals:
	void showMainWnd();//显示登录对话框信号  
	//void quit();//退出信号  
public slots:
	void receivelogin();
	void onRightClicked(QPoint point);
	void onAccountTableRightClicked(QPoint point);
	void pathBtnClicked();

	void readBtn1Clicked();
	void readBtn2Clicked();
	void readBtn3Clicked();
	void readBtn4Clicked();
	void readBtn5Clicked();

	void writeBtn1Clicked();
	void writeBtn2Clicked();
	void writeBtn3Clicked();
	void writeBtn4Clicked();
	void writeBtn5Clicked();

	void baseConfigBtnClicked();
	void onTableCellClicked(int a, int b);

	void generalConfiguration(QString file);
	void generalLoadConfig(QString file);

	void startBtnClicked();
	void loadAllAccouts();
	void saveAllAccouts();

	void shimenTaskBtnClicked();
	void datiBtnClicked();
	void bangwuBtnClicked();
	void qinxiuBtnClicked();
	void zhanyaoBtnClicked();
	void jishiyuBtnClicked();
	void zhaixinglouBtnClicked();
	void fabaoTiaozhanBtnClicked();
	void bangpaiXiulianBtnClicked();
	void xunxianBtnClicked();
	void duliangBtnClicked();

	void scriptUpBtnClicked();
	void scriptDownBtnClicked();
	void scriptDeleteBtnBtnClicked();
	void scriptClearBtnClicked();

	void terminateWnd();
	void newSingleWnd();

	void allPause();
	void singlePause();
	void singleStop();
	void allStart();
	void singleStart();
	void singleRestart();
	void allStop();
	void standarlizeWnd();
	
	//void accountGenBtnClicked();
	void simulatorGenBtnClicked();
	void simulatorConfigBtnClicked();
	void apkPathSelectBtnClicked();
	void apkInstallBtnClicked();
	void simulatorCloseBtnClicked();
	void downCpuBtnClickedClicked();
	void goldCalculatorBtnClicked();
	void saohuoTaskBtnClicked();
	void IsBuyCheckBoxClicked();
};
