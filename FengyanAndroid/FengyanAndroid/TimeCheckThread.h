#pragma once

#include <QThread>
#include <QLabel>

#include "baibao\QFLicense.h"
#include "CommonUtil.h"
#include "MainSingleton.h"

class TimeCheckThread : public QThread
{
	Q_OBJECT

public:
	TimeCheckThread(QLabel* timeLabel, QLabel* accountIndicatorLabel);
	TimeCheckThread(QObject *parent);
	TimeCheckThread();
	~TimeCheckThread();

private:
	QLabel *timeLabel;
	QLabel *accountIndicatorLabel;
	void run();
	int TimeCheckThread::reInitializer(int resetPrefixTime, int resetSuffixTime);
	void TimeCheckThread::allStart();
	int TimeCheckThread::getExecutionTime();
};
