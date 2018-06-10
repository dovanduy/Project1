#include "MonitorThread.h"

MonitorThread::MonitorThread()
{
}

MonitorThread::~MonitorThread()
{
}

void MonitorThread::run() {
	MainSingleton* theMain = MainSingleton::getInstance();

	while (true) {
		if (theMain->accountIndex <= theMain->totalAccountNum) {
			for (int i = 1; i <= theMain->windowCount; i++) {
				this->autoRestartWnd(i);
				
			}
		}
		
		if (theMain->autoRestartBox->isChecked()) {
			if (theMain->accountIndex >= theMain->totalAccountNum) {
				theMain->accountIndex = 1;
			}
		}
		Sleep(10000);
	}
	
	if (theMain->genAccountNum == 0) {
		MessageBox(NULL, L"已经都结束了！", L"提示：", MB_OK);
	}
}

int MonitorThread::autoRestartWnd(int index) {
	MainSingleton* theMain = MainSingleton::getInstance();
	QTableWidgetItem* item = theMain->table->item(index - 1, 0);
	if (item == NULL) {
		return 0;
	}

	QString text = item->text();
	if ("000019" == text) {

		string folder = theMain->folder;
		QString command = QString::fromStdString(folder) + "//dnconsole.exe quit --index " + QString::number(index);
		qDebug() << "command = " << command;
		WinExec(command.toStdString().c_str(), SW_NORMAL);

		Sleep(10000);

		command = QString::fromStdString(folder) + "//dnconsole.exe launch --index " + QString::number(index);
		qDebug() << "command = " << command;
		WinExec(command.toStdString().c_str(), SW_NORMAL);

		Sleep(10000);

		StartThread* thread = new StartThread(theMain->path, theMain->folder, index - 1, theMain->config);
		thread->setOperationParameter(REOPEN_WINDOW);
		thread->start();
	}

	return 0;
}