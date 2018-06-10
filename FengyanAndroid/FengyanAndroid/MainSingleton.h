#pragma once
#include "CommonUtil.h"
#include "DMSoft.h"
#include <QTableWidget>
#include <QCheckBox>
#include <QHash>
#include <QSpinbox>
#include <QLineEdit>
#include <QLabel>
#include <QMutex>  

class MainSingleton
{
public:
	
	~MainSingleton();

	static MainSingleton* getInstance();
	long simulatorHandlerHWND;
	Ifire* fire;
	QTableWidget* table;
	QTableWidget* accountTable;
	int windowCount;
	int accountIndex;
	long totalAccountNum;
	DWORD mainStarTime;

	QCheckBox* autoRestartBox;
	QSpinBox* windowCounterBox;
	QLabel* exeTimelabel;
	QLabel* exeCountLabel;
	QSpinBox* resetTimerSpinBox;

	int genAccountNum;

	QHash<int, int> rowAccountMap;
	QHash<int, int> idsMap;

	QString config;
	string path;
	string folder;
	void setRegisterID(int registerID);
	int getRegisterID();
	void setStartAccountID(int startAccountID);
	int MainSingleton::getTheAccountIndex();
private:
	MainSingleton();
	static MainSingleton* instance;
	int registerID;

};

