#pragma once

#include <QThread>
#include "CommonUtil.h"
#include "MainSingleton.h"
#include "StartThread.h"


class MonitorThread : public QThread
{
	Q_OBJECT

public:
	MonitorThread();

	~MonitorThread();

private:
	void run();
	int MonitorThread::autoRestartWnd(int index);
};
