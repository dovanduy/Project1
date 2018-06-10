#pragma once

#include <QThread>
#include "CommonUtil.h"
#include "MainSingleton.h"
#include "MainScriptThread.h"

#define OPEN_SIMULATOR 0
#define OPEN_WINDOW 1
#define REOPEN_WINDOW 2
#define SIMPLE_RESTART 4

class StartThread : public QThread
{
	Q_OBJECT

public:
	StartThread(QObject *parent);
	StartThread(string path);
	StartThread(string path, string folder, int count);
	StartThread(string path, string folder, int count, int lag, QString config);
	StartThread(string path, string folder, int row, QString config);
	~StartThread();
	int setOperationParameter(int param);
	int cpuNumber;
	int memoryNumber;
	bool isAutoReset;

private:
	string handlerPath;
	string folderPath;
	int row;
	int windowCount;
	int operationParam;
	int open_lag;
	

	QString config;

	void run();
	int openHandler();
	string StartThread::getStartCommand(int index);

	int StartThread::createGameThread();
	void StartThread::getWindowInfo(long lHWND);
	int StartThread::resumeGameThread();
	void StartThread::simpleRestart();
	int StartThread::getTheAccountIndex(int accountIndex);
};
