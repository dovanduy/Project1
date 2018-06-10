#include "TimeCheckThread.h"
#define MAX_ERROR_NUM 5   // 最大的容错次数，可以自行修改
#include <Windows.h>

TimeCheckThread::TimeCheckThread(QObject *parent)
	: QThread(parent)
{
}

TimeCheckThread::~TimeCheckThread()
{
}

TimeCheckThread::TimeCheckThread(QLabel *timeLabel, QLabel* accountIndicatorLabel)
{
	this->timeLabel = timeLabel;
	this->accountIndicatorLabel = accountIndicatorLabel;
}

TimeCheckThread::TimeCheckThread()
{
	
}

void TimeCheckThread::run() {
	int nErrorCount = 0;
	int nResult = 0;

	MainSingleton* theMain = MainSingleton::getInstance();

	while (true)
	{
		this->accountIndicatorLabel->setText(QString::number(theMain->accountIndex));
		this->getExecutionTime();

		string todayStr = CommonUtil::getCurrentDateStr(-1);
		int resetPrefixTime = CommonUtil::GetTimeStampByStr(todayStr.c_str());
		todayStr = CommonUtil::getCurrentDateStr(0);
		todayStr.append(" 01:00:00");
		int resetSuffixTime = CommonUtil::GetTimeStampByStr(todayStr.c_str());
		
		reInitializer(resetPrefixTime, resetSuffixTime);
		Sleep(5000);
		
		nResult = GetRegCodeTimeW();
		if (nResult > 0)
		{
			nErrorCount = 0;
			timeLabel->setText(QString::number(nResult));

			//g_csRemainTime.Format(_T("注册码剩余时间：%d小时%d分钟"), (int)(nResult / 60), nResult % 60); // 记录剩余时间
		}
		else
		{
			nErrorCount++;
			if (nErrorCount > MAX_ERROR_NUM)
			{
				TCHAR buffer[1024] = { 0 };
				GetLastErrorInfoW(buffer, 1024);
				//::AfxMessageBox(_T("注册码使用结束，原因：") + CString(buffer));
				exit(-1);
			}
		}
		Sleep(60 * 1000);
	}
}

int TimeCheckThread::reInitializer(int resetPrefixTime, int resetSuffixTime) {
	int currentTime = CommonUtil::getCurrentTimeInt();
	if (currentTime > resetPrefixTime && currentTime < resetSuffixTime) {
		allStart();
	}
	return 0;
}

int TimeCheckThread::getExecutionTime() {
	MainSingleton* theMain = MainSingleton::getInstance();
	DWORD theTime = timeGetTime() - theMain->mainStarTime;
	long theMin = theTime / 1000 / 60;
	theMain->exeTimelabel->setText(QString::number(theMin));
	int resetTime = theMain->resetTimerSpinBox->text().toInt();

	if (theMin >= resetTime && theMin < resetTime + 1) {
		theMain->mainStarTime = timeGetTime();
		int runCounter = theMain->exeCountLabel->text().toInt();
		theMain->exeCountLabel->setText(QString:: number(runCounter + 1));
		theMain->accountIndex = 1;
	}

	return 0;
}

void TimeCheckThread::allStart() {
	/*TianxiaSingleton* tianxia = TianxiaSingleton::getInstance();
	qDebug() << "allStart";

	if (tianxia->isAutoRestart == false) {
		return;
	}

	for (int i = 0; i < tianxia->windowCount; i++) {

		QTableWidgetItem* item = tianxia->table->item(i, 0);
		if (item == NULL) {
			return;
		}

		QString tHWND = item->text();
		qDebug() << tHWND;

		if ("222222" != tHWND || "000000" == tHWND) {
			continue;
		}

		QString config = tianxia->config;


		QString file = "";
		OpenWindowThread* thread = new OpenWindowThread(512, file.toStdString(), config, i);

		tianxia->table->setItem(i, 2, new QTableWidgetItem(QString::fromLocal8Bit("开始中")));
		tianxia->table->setItem(i, 0, new QTableWidgetItem(QString::fromLocal8Bit("RUNNING")));
		thread->start();

		Sleep(1000);
	}*/
}