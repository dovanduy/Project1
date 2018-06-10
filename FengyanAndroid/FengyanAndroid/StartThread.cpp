#include "StartThread.h"
#include "MainSingleton.h"

StartThread::StartThread(QObject *parent)
	: QThread(parent)
{
}

StartThread::~StartThread()
{

}

StartThread::StartThread(string path)
{
	this->handlerPath = path;
}

StartThread::StartThread(string path, string folder, int count)
{
	this->handlerPath = path;
	this->folderPath = folder;
	this->windowCount = count;
	this->memoryNumber = 2048;
	this->cpuNumber = 2;
}

StartThread::StartThread(string path, string folder, int count, int lag, QString config)
{
	this->handlerPath = path;
	this->folderPath = folder;
	this->windowCount = count;
	this->open_lag = lag;
	this->config = config;
	this->memoryNumber = 2048;
	this->cpuNumber = 2;
	this->isAutoReset = false;
}

StartThread::StartThread(string path, string folder, int row, QString config)
{
	this->handlerPath = path;
	this->folderPath = folder;
	this->row = row;
	this->config = config;
	this->isAutoReset = false;
}

int StartThread::setOperationParameter(int param) {
	this->operationParam = param;
	return 0;
}

void StartThread::run()
{
	MainSingleton* theMain = MainSingleton::getInstance();
	switch (operationParam) {
		case OPEN_SIMULATOR: {
			openHandler();
		}
		break;
		case OPEN_WINDOW: {

			QString COMMAND_ST = QString::fromStdString(this->folderPath) + "//dnconsole.exe modify --index ";

			for (int i = 1; i <= this->windowCount; i++) {
				if (i > theMain->totalAccountNum + theMain->genAccountNum) {
					break;
				}

				int index = theMain->windowCount;
				string command = this->getStartCommand(index + 1);

				if (this->isAutoReset) {
					QString temp = COMMAND_ST + QString::number(i) + " --resolution 800,450,160 --cpu " + QString::number(this->cpuNumber) + "--memory " + QString::number(this->memoryNumber) + " --imei auto --simserial auto --mac auto --androidid auto --imsi auto --lockwindow 1";
					WinExec(temp.toStdString().c_str(), SW_NORMAL);
				}
				

				Sleep(3000);
				WinExec(command.c_str(), SW_NORMAL);
				//CommonUtil::ExeCmd(command.c_str());

				Sleep(1000 * this->open_lag);

				createGameThread();
			}
		}
		break;
		case REOPEN_WINDOW: {
			resumeGameThread();
		}
	    break;
		case SIMPLE_RESTART: {
			simpleRestart();
		}
	    break;
	}
}

void StartThread::simpleRestart() {
	MainSingleton* theMain = MainSingleton::getInstance();

	QTableWidgetItem* item = theMain->table->item(row, 1);
	if (item == NULL) {
		return;
	}

	QString tHWND = item->text();

	QHash<int, int>::iterator iter = theMain->rowAccountMap.find(row + 1);
	int accountIndex = iter.value();

	long temp = tHWND.toLong();
	MainScriptThread* thread = new MainScriptThread(temp, config, row + 1, accountIndex);
	thread->start();

}

int StartThread::resumeGameThread() {
	string command = this->getStartCommand(row + 1);
	WinExec(command.c_str(), SW_NORMAL);

	Sleep(6000);

	MainSingleton* theMain = MainSingleton::getInstance();
	Ifire* fire = theMain->fire;

	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	bstr = fire->PskEnumWindow(0, "", "LDPlayerMainFrame", 2 + 4 + 32);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, ",");

	int resultCount = result.size();
	int mapSize = result.size() - 1;
	if (mapSize < 0) {
		return 0;
	}

	int lHWND = atol(result[mapSize].c_str());

	theMain->table->setItem(row, 0, new QTableWidgetItem(QString::fromLocal8Bit("RUNNING")));
	theMain->table->setItem(row, 1, new QTableWidgetItem(QString::number(lHWND)));

	QHash<int, int>::iterator iter = theMain->rowAccountMap.find(row + 1);
	int accountIndex = iter.value();

	if (accountIndex > theMain->totalAccountNum) {
		MessageBox(NULL, L"账号已经上万了！", L"警告！", MB_OK);
		return 0;
	}

	//DWORD processID = clicker->GetWindowProcessId(lHWND);
	DEVMODE NewDevMode;
	EnumDisplaySettings(0, ENUM_CURRENT_SETTINGS, &NewDevMode);

	SetWindowPos((HWND)lHWND, 0, 0, 0, -1, -1, SWP_SHOWWINDOW | SWP_NOZORDER | SWP_NOSIZE);

	MainScriptThread* thread = new MainScriptThread(lHWND, config, row + 1, accountIndex);
	thread->start();


	return 0;
}

int StartThread::createGameThread() {

	MainSingleton* theMain = MainSingleton::getInstance();
	Ifire* fire = theMain->fire;

	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	bstr = fire->PskEnumWindow(0, "", "LDPlayerMainFrame", 2 + 4 + 32);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, ",");

	int resultCount = result.size();
	int mapSize = result.size() - 1;
	if (mapSize < 0) {
		return 0;
	}
	/*if (mapSize >= result.size()) {
	return 0;
	}*/

	int lHWND = atol(result[mapSize].c_str());

	getWindowInfo(lHWND);
	
	//DWORD processID = clicker->GetWindowProcessId(lHWND);
	DEVMODE NewDevMode;
	EnumDisplaySettings(0, ENUM_CURRENT_SETTINGS, &NewDevMode);

	theMain->windowCount++;
	
	int theAccountIndex = theMain->getTheAccountIndex();

	SetWindowPos((HWND)lHWND, 0, 0, 0, -1, -1, SWP_SHOWWINDOW | SWP_NOZORDER | SWP_NOSIZE);

	theMain->idsMap.insert(theMain->accountIndex, theMain->accountIndex);
	theMain->rowAccountMap.insert(theMain->windowCount, theMain->accountIndex);

	MainScriptThread* thread = new MainScriptThread(lHWND, config, theMain->windowCount, theAccountIndex);
	thread->start();
	

	return 0;
}



string StartThread::getStartCommand(int index) {
	string result;
	//WinExec("F:\\ChangZhi2\\dnplayer2\\dnconsole.exe launch --index 1", SW_NORMAL);
	string temp = this->folderPath;
	result = temp.append("//dnconsole.exe launch --index ").append(CommonUtil::Long2STR(index));


	return result;
}

void StartThread::getWindowInfo(long lHWND) {

	MainSingleton* theMain = MainSingleton::getInstance();

	theMain->table->setItem(theMain->windowCount, 0, new QTableWidgetItem(QString::fromLocal8Bit("RUNNING")));
	theMain->table->setItem(theMain->windowCount, 1, new QTableWidgetItem(QString::number(lHWND)));

}

int StartThread::openHandler()
{
	MainSingleton* theMain = MainSingleton::getInstance();

	STARTUPINFOA si;
	memset(&si, 0, sizeof(STARTUPINFO));//初始化si在内存块中的值（详见memset函数）
	si.cb = sizeof(STARTUPINFO);
	si.dwFlags = STARTF_USESHOWWINDOW;
	si.wShowWindow = SW_SHOW;
	PROCESS_INFORMATION pi;//必备参数设置结束
	if (!CreateProcessA(handlerPath.c_str(),
		NULL,
		NULL,
		NULL,
		FALSE,
		0,
		NULL,
		NULL,
		&si,
		&pi
	)) {
		qDebug() << "CreateFail!" << endl;
		exit(1);
	}
	else {
		HWND hwnd = CommonUtil::GetHwndFromPID(pi.dwProcessId);
		Sleep(10000);
		HWND simulatorWnd = FindWindowA("LDMultiPlayerMainFrame", "雷电多开器");
		long lHWND = (long)simulatorWnd;
	
		theMain->simulatorHandlerHWND = lHWND;

		
	}
	return 0;
}
