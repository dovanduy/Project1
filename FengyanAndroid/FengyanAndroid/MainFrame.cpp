#include "MainFrame.h"
#include "PskCommonHelper.h"

MainFrame::MainFrame(QWidget *parent)
	: QMainWindow(parent)
{
	
}

void MainFrame::startMainThread() {
	ui.setupUi(this);
	//this->show();

	theMain = MainSingleton::getInstance();
	initMainDM();
	theMain->table = ui.tableWidget;
	theMain->accountTable = ui.accountTableWidget;
	theMain->autoRestartBox = ui.autoRestartBox;
	theMain->windowCounterBox = ui.windowCounter;

	theMain->exeTimelabel = ui.exeTimelabel;
	theMain->exeCountLabel = ui.exeCountLabel;
	theMain->resetTimerSpinBox = ui.resetTimerSpinBox;
	/*QRegExp regx("[a-z]{0,5}");
	QValidator *validator = new QRegExpValidator(regx, ui.accoutPrefixLineEdit);
	ui.accoutPrefixLineEdit->setValidator(validator);*/

	this->setUpMainTable();
	this->setUpAccountTable();
	theMain->mainStarTime = timeGetTime();

	ui.zoneComboBox->addItem(QString::fromLocal8Bit("开天辟地"));
	ui.zoneComboBox->addItem(QString::fromLocal8Bit("五斗群星"));

	ui.itemComboBox->addItem(QString::fromLocal8Bit("枪"));
	ui.itemComboBox->addItem(QString::fromLocal8Bit("杖"));
	ui.itemComboBox->addItem(QString::fromLocal8Bit("剑"));

	QObject::connect(ui.tableWidget, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(onRightClicked(QPoint)));
	QObject::connect(ui.accountTableWidget, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(onAccountTableRightClicked(QPoint)));

	QObject::connect(ui.pathSelectBtn, SIGNAL(clicked()), this, SLOT(pathBtnClicked()));
	QObject::connect(ui.apkPathSelectBtn, SIGNAL(clicked()), this, SLOT(apkPathSelectBtnClicked()));

	QObject::connect(ui.readBtn1, SIGNAL(clicked()), this, SLOT(readBtn1Clicked()));
	QObject::connect(ui.readBtn2, SIGNAL(clicked()), this, SLOT(readBtn2Clicked()));
	QObject::connect(ui.readBtn3, SIGNAL(clicked()), this, SLOT(readBtn3Clicked()));
	QObject::connect(ui.readBtn4, SIGNAL(clicked()), this, SLOT(readBtn4Clicked()));
	QObject::connect(ui.readBtn5, SIGNAL(clicked()), this, SLOT(readBtn5Clicked()));


	QObject::connect(ui.writeBtn1, SIGNAL(clicked()), this, SLOT(writeBtn1Clicked()));
	QObject::connect(ui.writeBtn2, SIGNAL(clicked()), this, SLOT(writeBtn2Clicked()));
	QObject::connect(ui.writeBtn3, SIGNAL(clicked()), this, SLOT(writeBtn3Clicked()));
	QObject::connect(ui.writeBtn4, SIGNAL(clicked()), this, SLOT(writeBtn4Clicked()));
	QObject::connect(ui.writeBtn5, SIGNAL(clicked()), this, SLOT(writeBtn5Clicked()));

	QObject::connect(ui.scriptUp, SIGNAL(clicked()), this, SLOT(scriptUpBtnClicked()));
	QObject::connect(ui.scriptDown, SIGNAL(clicked()), this, SLOT(scriptDownBtnClicked()));
	QObject::connect(ui.scriptDelete, SIGNAL(clicked()), this, SLOT(scriptDeleteBtnBtnClicked()));
	QObject::connect(ui.scriptClear, SIGNAL(clicked()), this, SLOT(scriptClearBtnClicked()));

	QObject::connect(ui.shimenTaskBtn, SIGNAL(clicked()), this, SLOT(shimenTaskBtnClicked()));
	QObject::connect(ui.datiBtn, SIGNAL(clicked()), this, SLOT(datiBtnClicked()));
	QObject::connect(ui.bangwuBtn, SIGNAL(clicked()), this, SLOT(bangwuBtnClicked()));
	QObject::connect(ui.qinxiuBtn, SIGNAL(clicked()), this, SLOT(qinxiuBtnClicked()));
	QObject::connect(ui.zhanyaoBtn, SIGNAL(clicked()), this, SLOT(zhanyaoBtnClicked()));
	QObject::connect(ui.jishiyuBtn, SIGNAL(clicked()), this, SLOT(jishiyuBtnClicked()));
	QObject::connect(ui.zhaixinglouBtn, SIGNAL(clicked()), this, SLOT(zhaixinglouBtnClicked()));
	QObject::connect(ui.fabaoTiaozhanBtn, SIGNAL(clicked()), this, SLOT(fabaoTiaozhanBtnClicked()));
	QObject::connect(ui.bangpaiXiulianBtn, SIGNAL(clicked()), this, SLOT(bangpaiXiulianBtnClicked()));
	QObject::connect(ui.xunxianBtn, SIGNAL(clicked()), this, SLOT(xunxianBtnClicked()));
	QObject::connect(ui.duliangBtn, SIGNAL(clicked()), this, SLOT(duliangBtnClicked()));
	QObject::connect(ui.saohuoTaskBtn, SIGNAL(clicked()), this, SLOT(saohuoTaskBtnClicked()));

	QObject::connect(ui.baseConfigBtn, SIGNAL(clicked()), this, SLOT(baseConfigBtnClicked()));
	QObject::connect(ui.onePunch, SIGNAL(clicked()), this, SLOT(startBtnClicked()));
	//QObject::connect(ui.accountGenBtn, SIGNAL(clicked()), this, SLOT(accountGenBtnClicked()));
	//simulatorConfigBtn
	QObject::connect(ui.simulatorGenBtn, SIGNAL(clicked()), this, SLOT(simulatorGenBtnClicked()));
	QObject::connect(ui.simulatorConfigBtn, SIGNAL(clicked()), this, SLOT(simulatorConfigBtnClicked()));
	QObject::connect(ui.apkInstallBtn, SIGNAL(clicked()), this, SLOT(apkInstallBtnClicked()));
	QObject::connect(ui.simulatorCloseBtn, SIGNAL(clicked()), this, SLOT(simulatorCloseBtnClicked()));
	QObject::connect(ui.downCpuBtnClicked, SIGNAL(clicked()), this, SLOT(downCpuBtnClickedClicked()));
	//QObject::connect(ui.goldCalculatorBtn, SIGNAL(clicked()), this, SLOT(goldCalculatorBtnClicked()));
	QObject::connect(ui.IsBuyCheckBox, SIGNAL(clicked()), this, SLOT(IsBuyCheckBoxClicked()));
	//

	QObject::connect(ui.tableWidget, SIGNAL(cellClicked(int, int)), this, SLOT(onTableCellClicked(int, int)));


	generalLoadConfig("config/base.ini");
	this->loadAllAccouts4Init();
	//this->loadAllMoney();

	MonitorThread* monitor = new MonitorThread();
	monitor->start();

	TimeCheckThread* time = new TimeCheckThread(ui.timeLabel, ui.accountIndicatorLabel);
	time->start();
	return;
}

MainFrame::~MainFrame()
{
}

void MainFrame::scriptUpBtnClicked() {
	qDebug() << "scriptUpBtnClicked";

	QListWidgetItem* item = ui.scriptSortList->currentItem();
	if (item == NULL) {
		return;
	}
	qDebug() << item->text();

	QListWidgetItem* upperItem = ui.scriptSortList->item(ui.scriptSortList->currentRow() - 1);
	if (upperItem == NULL) {
		return;
	}
	qDebug() << upperItem->text();
	QString tempText = item->text();
	item->setText(upperItem->text());
	upperItem->setText(tempText);

	ui.scriptSortList->setCurrentRow(ui.scriptSortList->currentRow() - 1);
}

void MainFrame::scriptDownBtnClicked() {
	qDebug() << "scriptDownBtnClicked";
	QListWidgetItem* item = ui.scriptSortList->currentItem();
	if (item == NULL) {
		return;
	}
	qDebug() << item->text();

	QListWidgetItem* lowerItem = ui.scriptSortList->item(ui.scriptSortList->currentRow() + 1);
	if (lowerItem == NULL) {
		return;
	}
	qDebug() << lowerItem->text();
	QString tempText = item->text();
	item->setText(lowerItem->text());
	lowerItem->setText(tempText);

	ui.scriptSortList->setCurrentRow(ui.scriptSortList->currentRow() + 1);
}

void MainFrame::scriptDeleteBtnBtnClicked() {
	qDebug() << "scriptDeleteBtnBtnClicked";
	/*QListWidgetItem* item = ui.scriptSortList->currentItem();
	ui.scriptSortList->removeItemWidget(item);
	*/
	int row = ui.scriptSortList->currentRow();
	ui.scriptSortList->takeItem(row);
}

void MainFrame::scriptClearBtnClicked() {
	qDebug() << "scriptClearBtnClicked";
	int row = ui.scriptSortList->count();

	while (row != 0) {
		ui.scriptSortList->takeItem(row - 1);
		//row = ui.scriptSortList->currentRow();
		row = ui.scriptSortList->count();
	}
}

void MainFrame::shimenTaskBtnClicked() {
	qDebug() << "shimenTaskBtnClicked";
	ui.scriptSortList->addItem(QString::fromLocal8Bit("师门任务"));
	ui.scriptSortList->setCurrentRow(ui.scriptSortList->count() - 1);
}

void MainFrame::datiBtnClicked() {
	qDebug() << "datiBtnClicked";
	ui.scriptSortList->addItem(QString::fromLocal8Bit("答题任务"));
	ui.scriptSortList->setCurrentRow(ui.scriptSortList->count() - 1);
}
//bangwuBtnClicked
void MainFrame::bangwuBtnClicked() {
	qDebug() << "bangwuBtnClicked";
	ui.scriptSortList->addItem(QString::fromLocal8Bit("帮派任务"));
	ui.scriptSortList->setCurrentRow(ui.scriptSortList->count() - 1);
}
//qinxiuBtnClicked
void MainFrame::qinxiuBtnClicked() {
	qDebug() << "qinxiuBtnClicked";
	ui.scriptSortList->addItem(QString::fromLocal8Bit("勤修不倦"));
	ui.scriptSortList->setCurrentRow(ui.scriptSortList->count() - 1);
}
//zhanyaoBtnClicked
void MainFrame::zhanyaoBtnClicked() {
	qDebug() << "zhanyaoBtnClicked";
	ui.scriptSortList->addItem(QString::fromLocal8Bit("斩妖除魔"));
	ui.scriptSortList->setCurrentRow(ui.scriptSortList->count() - 1);
}
//jishiyuBtnClicked
void MainFrame::jishiyuBtnClicked() {
	qDebug() << "jishiyuBtnClicked";
	ui.scriptSortList->addItem(QString::fromLocal8Bit("及时雨"));
	ui.scriptSortList->setCurrentRow(ui.scriptSortList->count() - 1);
}
//zhaixinglouBtnClicked
void MainFrame::zhaixinglouBtnClicked() {
	qDebug() << "zhaixinglouBtnClicked";
	ui.scriptSortList->addItem(QString::fromLocal8Bit("摘星楼"));
	ui.scriptSortList->setCurrentRow(ui.scriptSortList->count() - 1);
}
//fabaoTiaozhanBtnClicked
void MainFrame::fabaoTiaozhanBtnClicked() {
	qDebug() << "fabaoTiaozhanBtnClicked";
	ui.scriptSortList->addItem(QString::fromLocal8Bit("法宝挑战"));
	ui.scriptSortList->setCurrentRow(ui.scriptSortList->count() - 1);
}
//bangpaiXiulianBtnClicked
void MainFrame::bangpaiXiulianBtnClicked() {
	qDebug() << "bangpaiXiulianBtnClicked";
	ui.scriptSortList->addItem(QString::fromLocal8Bit("帮派修炼"));
	ui.scriptSortList->setCurrentRow(ui.scriptSortList->count() - 1);
}
//xunxianBtnClicked
void MainFrame::xunxianBtnClicked() {
	qDebug() << "xunxianBtnClicked";
	ui.scriptSortList->addItem(QString::fromLocal8Bit("寻仙问道"));
	ui.scriptSortList->setCurrentRow(ui.scriptSortList->count() - 1);
}
//duliangBtnClicked
void MainFrame::duliangBtnClicked() {
	qDebug() << "duliangBtnClicked";
	ui.scriptSortList->addItem(QString::fromLocal8Bit("督粮"));
	ui.scriptSortList->setCurrentRow(ui.scriptSortList->count() - 1);
}
//saohuoTaskBtnClicked
void MainFrame::saohuoTaskBtnClicked() {
	qDebug() << "saohuoTaskBtnClicked";
	ui.scriptSortList->addItem(QString::fromLocal8Bit("寄售购买"));
	ui.scriptSortList->setCurrentRow(ui.scriptSortList->count() - 1);
}

int MainFrame::setUpMainTable() {
	ui.tableWidget->setRowCount(30);
	ui.tableWidget->setColumnCount(10);
	for (int i = 0; i < 30; i++) {
		ui.tableWidget->setRowHeight(i, 20);
	}

	QStringList header;
	header << QString::fromLocal8Bit("窗口名称") << QString::fromLocal8Bit("窗口句柄")
		<< QString::fromLocal8Bit("当前任务") << QString::fromLocal8Bit("活跃值")
		<< QString::fromLocal8Bit("金币数量") << QString::fromLocal8Bit("存货")
		<< QString::fromLocal8Bit("错误") << QString::fromLocal8Bit("时") << QString::fromLocal8Bit("等级")
		<< QString::fromLocal8Bit("所属账号");
	ui.tableWidget->setHorizontalHeaderLabels(header);
	ui.tableWidget->horizontalHeader()->setStretchLastSection(true);
	ui.tableWidget->setContextMenuPolicy(Qt::CustomContextMenu);
	ui.tableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
	ui.tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
	ui.tableWidget->setColumnWidth(0, 60);
	ui.tableWidget->setColumnWidth(1, 60);
	ui.tableWidget->setColumnWidth(2, 80);
	ui.tableWidget->setColumnWidth(3, 50);
	ui.tableWidget->setColumnWidth(4, 60);
	ui.tableWidget->setColumnWidth(5, 80);
	ui.tableWidget->setColumnWidth(6, 50);
	ui.tableWidget->setColumnWidth(7, 50);
	ui.tableWidget->setColumnWidth(8, 50);
	ui.tableWidget->setColumnWidth(9, 50);

	//ui.tableWidget->setFocus();
	//ui.tableWidget->editItem(ui.tableWidget->item(1, 1));

	ui.tableWidget->setStyleSheet(
		"color:black;"
		/*"gridline-color:blue;"*/   /*表格中的网格线条颜色*/
		"background:white;"
		/*"alternate-background-color:red;"*/  /*设置交替颜色*/
		"selection-color:red;"
		"selection-background-color:yellow;"
		"border:1px solid gray;"
	);
	return 0;
}

int MainFrame::setUpAccountTable() {
	int ROW_COUNT = 1000;
	ui.accountTableWidget->setRowCount(ROW_COUNT);
	ui.accountTableWidget->setColumnCount(6);
	for (int i = 0; i < ROW_COUNT; i++) {
		ui.accountTableWidget->setRowHeight(i, 20);
	}

	QStringList header;
	header << QString::fromLocal8Bit("   ID   ")  << QString::fromLocal8Bit("   账号   ") << QString::fromLocal8Bit("   密码   ")
		<< QString::fromLocal8Bit("   区服   ") << QString::fromLocal8Bit("  金子  ") << QString::fromLocal8Bit("  总存货  ");

	ui.accountTableWidget->setHorizontalHeaderLabels(header);
	ui.accountTableWidget->horizontalHeader()->setStretchLastSection(true);
	ui.accountTableWidget->setContextMenuPolicy(Qt::CustomContextMenu);
	//ui.accountTableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
	//ui.accountTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
	ui.accountTableWidget->setColumnWidth(0, 60);
	ui.accountTableWidget->setColumnWidth(1, 100);
	ui.accountTableWidget->setColumnWidth(2, 100);
	ui.accountTableWidget->setColumnWidth(3, 100);
	ui.accountTableWidget->setColumnWidth(4, 60);
	ui.accountTableWidget->setColumnWidth(5, 80);

	//ui.tableWidget->setFocus();
	//ui.tableWidget->editItem(ui.tableWidget->item(1, 1));

	ui.accountTableWidget->setStyleSheet(
		"color:black;"
		/*"gridline-color:blue;"*/   /*表格中的网格线条颜色*/
		"background:white;"
		/*"alternate-background-color:red;"*/  /*设置交替颜色*/
		"selection-color:red;"
		"selection-background-color:yellow;"
		"border:1px solid gray;"
	);

	for (int i = 0; i<ui.accountTableWidget->rowCount(); i++)
	{
		
		QTableWidgetItem* item = new QTableWidgetItem();
		ui.accountTableWidget->setItem(i, 0, item);
		item->setFlags(item->flags() & (~Qt::ItemIsEditable));
	}
	return 0;
}

/* a row, b column*/
void MainFrame::onTableCellClicked(int a, int b) {
	qDebug() << "onTableCellClicked";
	qDebug() << QString::number(a);
	qDebug() << QString::number(b);

	QTableWidgetItem* item = ui.tableWidget->item(a, 1);
	if (item == NULL) {
		return;
	}

	QString tHWND = item->text();
	qDebug() << tHWND;

	long lHWND = tHWND.toLong();

	SetWindowPos((HWND)lHWND, HWND_NOTOPMOST, -1, -1, -1, -1, SWP_NOSIZE | SWP_NOMOVE);
}

int MainFrame::initMainDM() {
	fire = DMSoft::getInstance()->newDMObject();
	int result = 0;
	string code = fire->GetMachineCode();
	

	//result = fire->PskReg("pskfire20928db6b002f54b0b0f1d5dcc665316", "ambition");
	result = PskCommonHelper::CommonReg(fire, "pskfire20928db6b002f54b0b0f1d5dcc665316", "ambition");
	//qDebug() << PskCommonHelper::CommonGetVer(fire).c_str();

	if (result != 1) {
		qDebug() << "reg error";

	}
	else {
		qDebug() << "reg success!" << PskCommonHelper::CommonGetVer(fire).c_str();
	}

	////result = fire->PskGuard(1, "np");
	//result = PskCommonHelper::CommonGuard(fire, 1, "np");
	//if (result != 1) {
	//	qDebug() << "DmGuard np error";
	//}

	//result = PskCommonHelper::CommonGuard(fire, 1, "memory");
	////result = fire->PskGuard(1, "memory");
	//if (result != 1) {
	//	qDebug() << "DmGuard memory error";
	//}

	//result = PskCommonHelper::CommonGuard(fire, 1, "block");
	////result = fire->PskGuard(1, "block");
	//if (result != 1) {
	//	qDebug() << "DmGuard block error";
	//}

	//result = PskCommonHelper::CommonGuard(fire, 1, "b2");
	////result = fire->PskGuard(1, "b2");
	//if (result != 1) {
	//	qDebug() << "DmGuard b2 error ";
	//}
	//
	//result = PskCommonHelper::CommonGuard(fire, 1, "f1");
	////result = fire->PskGuard(1, "f1");
	//if (result != 1) {
	//	qDebug() << "DmGuard f1 error";
	//}

	theMain->fire = fire;

	return 0;
}

int MainFrame::findAndroidHander() {
	HWND simulatorWnd = FindWindowA("LDMultiPlayerMainFrame","雷电多开器");
	long lHWND = (long)simulatorWnd;
	theMain->simulatorHandlerHWND = lHWND;
	return 0;
}

void MainFrame::receivelogin() {
	
	this->startMainThread();
	this->show();
}

void MainFrame::onRightClicked(QPoint point) {
	qDebug() << "onRightClicked";
	int a = ui.tableWidget->currentColumn();
	int b = ui.tableWidget->currentRow();

	QMenu menu;
	menu.addAction(QString::fromLocal8Bit("刷新列表"), this, SLOT(test()));
	menu.addSeparator();
	menu.addAction(QString::fromLocal8Bit("全部暂停"), this, SLOT(allPause()));
	menu.addAction(QString::fromLocal8Bit("单个暂停"), this, SLOT(singlePause()));
	menu.addAction(QString::fromLocal8Bit("暂停恢复"), this, SLOT(singleRestart()));
	menu.addSeparator();
	menu.addAction(QString::fromLocal8Bit("全部停止"), this, SLOT(allStop()));
	menu.addAction(QString::fromLocal8Bit("单个停止"), this, SLOT(singleStop()));
	menu.addAction(QString::fromLocal8Bit("单个开始"), this, SLOT(singleStart()));
	menu.addAction(QString::fromLocal8Bit("全部开始"), this, SLOT(allStart()));
	menu.addSeparator();
	menu.addAction(QString::fromLocal8Bit("单个结束"), this, SLOT(terminateWnd()));
	menu.addAction(QString::fromLocal8Bit("单个启动"), this, SLOT(newSingleWnd()));
	menu.addSeparator();
	menu.addAction(QString::fromLocal8Bit("窗口归位"), this, SLOT(standarlizeWnd()));

	menu.exec(QCursor::pos());

}

void MainFrame::newSingleWnd() {
	qDebug() << "newSingleWnd";
	int a = ui.tableWidget->currentColumn();
	int b = ui.tableWidget->currentRow();

	qDebug() << "column =" << a;
	qDebug() << "row =" << b;

	QTableWidgetItem* item = ui.tableWidget->item(b, 1);
	if (item == NULL) {
		return;
	}

	QString tHWND = item->text();
	qDebug() << tHWND;

	if ("000000" != tHWND) {
		return;
	}


	ui.tableWidget->setItem(b, 1, new QTableWidgetItem(QString::fromLocal8Bit("000001")));
	QString file = ui.gamePathEditor->text();

	QString config = this->loadScriptConfig();
	string path = ui.gamePathEditor->text().toStdString();
	string folder = ui.gamePathEditor2->text().toStdString();
	int windowCount = ui.windowCounter->text().toInt();
	int open_lag = ui.open_lag->text().toInt();

	StartThread* thread = new StartThread(path,folder,b,config);
	thread->setOperationParameter(REOPEN_WINDOW);
	thread->cpuNumber = ui.cpuNumSpinBox->text().toInt();
	thread->memoryNumber = ui.memoryNumSpinBox->text().toInt();
	thread->isAutoReset = ui.autoResetBox->isChecked();
	thread->start();
	

}

void MainFrame::standarlizeWnd() {
	qDebug() << "standarlizeWnd";
	int a = ui.tableWidget->currentColumn();
	int b = ui.tableWidget->currentRow();

	qDebug() << "column =" << a;
	qDebug() << "row =" << b;

	QTableWidgetItem* item = ui.tableWidget->item(b, 1);
	if (item == NULL) {
		return;
	}

	QString tHWND = item->text();
	qDebug() << tHWND;

	if ("000000" == tHWND) {
		return;
	}

	SetWindowPos((HWND)tHWND.toLong(), 0, 0, 0, -1, -1, SWP_SHOWWINDOW | SWP_NOZORDER | SWP_NOSIZE);
}

void MainFrame::singleRestart() {
	qDebug() << "singleRestart";
	int a = ui.tableWidget->currentColumn();
	int b = ui.tableWidget->currentRow();

	qDebug() << "column =" << a;
	qDebug() << "row =" << b;
	MainSingleton* theMain = MainSingleton::getInstance();


	ui.tableWidget->setItem(b, 2, new QTableWidgetItem(QString::fromLocal8Bit("暂停恢复")));
	ui.tableWidget->setItem(b, 0, new QTableWidgetItem(QString::fromLocal8Bit("RUNNING")));

}

void MainFrame::allStop() {
	MainSingleton* theMain = MainSingleton::getInstance();
	qDebug() << "allStop";
	for (int i = 0; i < theMain->windowCount; i++) {

		QTableWidgetItem* item = ui.tableWidget->item(i, 0);
		QString tHWND = item->text();
		qDebug() << tHWND;

		if ("222222" == tHWND || "222220" == tHWND) {
			continue;
		}

		ui.tableWidget->setItem(i, 2, new QTableWidgetItem(QString::fromLocal8Bit("停止中")));
		ui.tableWidget->setItem(i, 0, new QTableWidgetItem(QString::fromLocal8Bit("222220")));
	}

}

void MainFrame::singleStop() {
	qDebug() << "singleStop";
	int a = ui.tableWidget->currentColumn();
	int b = ui.tableWidget->currentRow();

	qDebug() << "column =" << a;
	qDebug() << "row =" << b;
	//MainSingleton* theMain = MainSingleton::getInstance();
	QTableWidgetItem* item = ui.tableWidget->item(b, 0);
	if (item == NULL) {
		return;
	}

	QString tHWND = item->text();
	qDebug() << tHWND;

	if ("222222" == tHWND || "222220" == tHWND) {
		return;
	}

	ui.tableWidget->setItem(b, 2, new QTableWidgetItem(QString::fromLocal8Bit("停止中")));
	ui.tableWidget->setItem(b, 0, new QTableWidgetItem(QString::fromLocal8Bit("222220")));
}

void MainFrame::allStart() {
	MainSingleton* theMain = MainSingleton::getInstance();
	qDebug() << "allStart";

	for (int i = 0; i < theMain->windowCount; i++) {

		QTableWidgetItem* item = ui.tableWidget->item(i, 0);
		if (item == NULL) {
			return;
		}

		QString tHWND = item->text();
		qDebug() << tHWND;

		if ("222222" != tHWND || "000000" == tHWND) {
			continue;
		}

		QString config = loadScriptConfig();
		string path = ui.gamePathEditor->text().toStdString();
		string folder = ui.gamePathEditor2->text().toStdString();


		theMain->config = config;
		theMain->path = path;
		theMain->folder = folder;
		
		QString file = ui.gamePathEditor->text();
		StartThread* thread = new StartThread(path, folder, i, config);
		thread->setOperationParameter(SIMPLE_RESTART);
		thread->cpuNumber = ui.cpuNumSpinBox->text().toInt();
		thread->memoryNumber = ui.memoryNumSpinBox->text().toInt();
		thread->isAutoReset = ui.autoResetBox->isChecked();
		thread->start();

		ui.tableWidget->setItem(i, 2, new QTableWidgetItem(QString::fromLocal8Bit("开始中")));
		ui.tableWidget->setItem(i, 0, new QTableWidgetItem(QString::fromLocal8Bit("RUNNING")));

		Sleep(1000);
	}
}

void MainFrame::singleStart() {
	qDebug() << "singleStart";
	int a = ui.tableWidget->currentColumn();
	int b = ui.tableWidget->currentRow();

	qDebug() << "column =" << a;
	qDebug() << "row =" << b;

	QTableWidgetItem* item = ui.tableWidget->item(b, 0);
	if (item == NULL) {
		return;
	}

	QString tHWND = item->text();
	qDebug() << tHWND;

	if ("222222" != tHWND || "000000" == tHWND) {
		return;
	}


	QString config = loadScriptConfig();
	string path = ui.gamePathEditor->text().toStdString();
	string folder = ui.gamePathEditor2->text().toStdString();

	theMain->config = config;
	theMain->path = path;
	theMain->folder = folder;

	QString file = ui.gamePathEditor->text();
	StartThread* thread = new StartThread(path, folder, b, config);
	thread->setOperationParameter(SIMPLE_RESTART);
	thread->cpuNumber = ui.cpuNumSpinBox->text().toInt();
	thread->memoryNumber = ui.memoryNumSpinBox->text().toInt();
	thread->isAutoReset = ui.autoResetBox->isChecked();
	thread->start();

	ui.tableWidget->setItem(b, 2, new QTableWidgetItem(QString::fromLocal8Bit("开始中")));
	ui.tableWidget->setItem(b, 0, new QTableWidgetItem(QString::fromLocal8Bit("RUNNING")));
	thread->start();
}

void MainFrame::singlePause() {
	qDebug() << "singlePause";
	int a = ui.tableWidget->currentColumn();
	int b = ui.tableWidget->currentRow();

	qDebug() << "column =" << a;
	qDebug() << "row =" << b;
	MainSingleton* theMain = MainSingleton::getInstance();
	QTableWidgetItem* item = ui.tableWidget->item(b, 0);
	if (item == NULL) {
		return;
	}

	QString tHWND = item->text();
	qDebug() << tHWND;

	if ("222222" == tHWND || "222220" == tHWND) {
		return;
	}

	ui.tableWidget->setItem(b, 2, new QTableWidgetItem(QString::fromLocal8Bit("已暂停")));
	ui.tableWidget->setItem(b, 0, new QTableWidgetItem(QString::fromLocal8Bit("111111")));

}

void MainFrame::allPause() {
	MainSingleton* theMaian = MainSingleton::getInstance();
	qDebug() << "allPause";
	for (int i = 0; i < theMaian->windowCount; i++) {

		QTableWidgetItem* item = ui.tableWidget->item(i, 0);
		if (item == NULL) {
			return;
		}

		QString tHWND = item->text();
		qDebug() << tHWND;

		if ("222222" == tHWND || "222220" == tHWND) {
			continue;
		}

		ui.tableWidget->setItem(i, 2, new QTableWidgetItem(QString::fromLocal8Bit("已暂停")));
		ui.tableWidget->setItem(i, 0, new QTableWidgetItem(QString::fromLocal8Bit("111111")));
	}

}

void MainFrame::terminateWnd() {
	qDebug() << "terminateWnd";
	int a = ui.tableWidget->currentColumn();
	int b = ui.tableWidget->currentRow();

	qDebug() << "a =" << a;
	qDebug() << "b =" << b;

	QTableWidgetItem* item = ui.tableWidget->item(b, 1);
	if (item == NULL) {
		return;
	}

	QString tHWND = item->text();
	qDebug() << tHWND;

	if ("000008" == tHWND || "000000" == tHWND) {
		return;
	}

	item = ui.tableWidget->item(b, 0);
	if (item == NULL) {
		return;
	}

	tHWND = item->text();
	qDebug() << tHWND;

	if ("222220" == tHWND || "000009" == tHWND) {
		MessageBoxA(NULL, "停止状态下无法结束！", "警告", ERROR);
		return;
	}

	QString folder = ui.gamePathEditor2->text();
	QString command = folder + "//dnconsole.exe quit --index " + QString::number(b + 1);
	qDebug() << "command = " << command;
	WinExec(command.toStdString().c_str(), SW_NORMAL);

	if ("000019" == tHWND || "222222" == tHWND) {
		ui.tableWidget->setItem(b, 2, new QTableWidgetItem(QString::fromLocal8Bit("已结束")));
		ui.tableWidget->setItem(b, 1, new QTableWidgetItem(QString::fromLocal8Bit("000000")));
		
	}
	else {
		ui.tableWidget->setItem(b, 2, new QTableWidgetItem(QString::fromLocal8Bit("结束中")));
		ui.tableWidget->setItem(b, 1, new QTableWidgetItem(QString::fromLocal8Bit("000008")));
	}

}

void MainFrame::onAccountTableRightClicked(QPoint point) {
	qDebug() << "onAccountTableRightClicked";
	int a = ui.tableWidget->currentColumn();
	int b = ui.tableWidget->currentRow();

	QMenu menu;
	menu.addAction(QString::fromLocal8Bit("刷新列表"), this, SLOT(loadAllAccouts()));
	menu.addAction(QString::fromLocal8Bit("全部保存"), this, SLOT(saveAllAccouts()));
	menu.addSeparator();
	/*menu.addAction(QString::fromLocal8Bit("单个保存"), this, SLOT(loadAllAccouts()));
	menu.addAction(QString::fromLocal8Bit("单个读取"), this, SLOT(loadAllAccouts()));
	menu.addAction(QString::fromLocal8Bit("单个移除"), this, SLOT(loadAllAccouts()));*/


	menu.exec(QCursor::pos());

}

void MainFrame::loadAllAccouts() {
	qDebug() << "loadAllAccouts";
	int selectedRow = ui.accountTableWidget->currentRow();
	QSettings configIniRead("config/accounts.ini", QSettings::IniFormat);
	MainSingleton* theMain = MainSingleton::getInstance();
	

	for (int i = 0; i < 1000 + 1; i++) {
		QString temp = configIniRead.value("/account_list/" + QString::number(i + 1)).toString();
		std::vector<std::string> result = CommonUtil::split(temp.toStdString(), "---");
		if (result.size() >= 2) {
			string account = result[0];
			string password = result[1];

			theMain->totalAccountNum = i + 1;

			//table->setItem(index - 1, 2, new QTableWidgetItem(QString::fromLocal8Bit("已掉线")));
			ui.accountTableWidget->setItem(i, 0, new QTableWidgetItem(QString::number(i + 1)));
			ui.accountTableWidget->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(account)));
			ui.accountTableWidget->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(password)));
		}
		else {
			break;
		}
	}
}

//void MainFrame::loadAllMoney() {
//	qDebug() << "loadAllMoney";
//	QSettings configIniRead("logs/aaa.ini", QSettings::IniFormat);
//	MainSingleton* theMain = MainSingleton::getInstance();
//
//	int totalAmount = 0;
//	for (int i = 0; i < theMain->totalAccountNum + 1; i++) {
//		QString temp = configIniRead.value("/gold_sum/" + QString::number(i + 1)).toString();
//		ui.accountTableWidget->setItem(i, 4, new QTableWidgetItem(temp));
//		totalAmount += temp.toInt();
//	}
//
//	ui.totalGoldLabel->setText(QString::number(totalAmount));
//}

void MainFrame::loadAllAccouts4Init() {
	qDebug() << "loadAllAccouts4Init";
	QSettings configIniRead("config/accounts.ini", QSettings::IniFormat);

	MainSingleton* theMain = MainSingleton::getInstance();

	for (int i = 0; i < 1000 + 1; i++) {
		QString temp = configIniRead.value("/account_list/" + QString::number(i + 1)).toString();
		std::vector<std::string> result = CommonUtil::split(temp.toStdString(), "---");
		if (result.size() >= 2) {
			string account = result[0];
			string password = result[1];

			theMain->totalAccountNum = i + 1;

			//table->setItem(index - 1, 2, new QTableWidgetItem(QString::fromLocal8Bit("已掉线")));
			ui.accountTableWidget->setItem(i, 0, new QTableWidgetItem(QString::number(i + 1)));
			ui.accountTableWidget->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(account)));
			ui.accountTableWidget->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(password)));
		}
		else {
			break;
		}
	}
}

void MainFrame::saveAllAccouts() {
	qDebug() << "saveAllAccouts";
	int selectedRow = ui.accountTableWidget->currentRow();
	qDebug() << "currentRow = " << selectedRow;

	for (int i = 0; i < 1000 + 1; i++) {
		if (saveSingleAccuntSub(i) == 0) {
			break;
		}
	}
}

int MainFrame::saveSingleAccuntSub(int index) {
	QTableWidgetItem* item = ui.accountTableWidget->item(index, 0);
	int id = item->text().toInt();

	if (id == 0) {
		id = index + 1;
	}

	qDebug() << "id = " << id;

	item = ui.accountTableWidget->item(index, 1);
	if (item == NULL) {
		return 0;
	}
	QString account = item->text();
	qDebug() << "account = " << account;

	item = ui.accountTableWidget->item(index, 2);
	if (item == NULL) {
		return 0;
	}
	QString password = item->text();
	qDebug() << "password = " << password;

	QSettings settings("config/accounts.ini", QSettings::IniFormat);
	settings.beginGroup("account_list");
	settings.setValue(QString::number(id), account + "---" + password);
	settings.endGroup();

	return 1;
}

void MainFrame::pathBtnClicked() {

	QFileInfo fileInfo = QFileDialog::getOpenFileName(this, QString::fromLocal8Bit("多开器exe"), QString(), QString::fromLocal8Bit("dnmultiplayer.exe(*.exe);;All files(*.*)"));

	QString file = fileInfo.absoluteFilePath();
	QString fileFolder = fileInfo.absolutePath();

	if (file.isEmpty()) {
		return;
	}

	qDebug() << file;

	ui.gamePathEditor->setText(file);
	ui.gamePathEditor2->setText(fileFolder);
}
//apkPathSelectBtnClicked
void MainFrame::apkPathSelectBtnClicked() {

	QFileInfo fileInfo = QFileDialog::getOpenFileName(this, QString::fromLocal8Bit("apk"), QString(), QString::fromLocal8Bit("道无边apk(*.apk);;All files(*.*)"));

	QString file = fileInfo.absoluteFilePath();
	QString fileFolder = fileInfo.absolutePath();

	if (file.isEmpty()) {
		return;
	}

	qDebug() << file;

	ui.apkPathEditor->setText(file);
}

void MainFrame::generalConfiguration(QString file) {

	QSettings settings(file, QSettings::IniFormat); // 当前目录的INI文件

													/* 区服设置 */
	settings.beginGroup("system_config");

	settings.setValue("path", ui.gamePathEditor->text());
	settings.setValue("folder", ui.gamePathEditor2->text());

	settings.endGroup();

	settings.beginGroup("start_config");

	settings.setValue("window_count", ui.windowCounter->value());
	settings.setValue("open_lag", ui.open_lag->value());

	settings.endGroup();

	settings.beginGroup("script_config");

	if (ui.zhuxianCheckBox->isChecked()) {
		settings.setValue("isZhuxian", "1");
	}
	else {
		settings.setValue("isZhuxian", "0");
	}
	settings.setValue("zone", ui.zoneComboBox->currentIndex());
	settings.setValue("time_limit", ui.timeLimitSpinBox->value());
	settings.setValue("main_time_limit", ui.mainTaskTimeLimitSpinBox->value());

	settings.setValue("count", QString::number(ui.scriptSortList->count(), 10));
	for (int i = 0; i < ui.scriptSortList->count(); i++) {
		QListWidgetItem* item = ui.scriptSortList->item(i);
		qDebug() << "item = " << item->text();
		settings.setValue(QString::number(i, 10), item->text());
	}

	settings.endGroup();

}

void MainFrame::generalLoadConfig(QString file) {
	QSettings configIniRead(file, QSettings::IniFormat);

	QString path = configIniRead.value("/system_config/path").toString();
	ui.gamePathEditor->setText(path);
	QString folder = configIniRead.value("/system_config/folder").toString();
	ui.gamePathEditor2->setText(folder);

	ui.windowCounter->setValue(configIniRead.value("/start_config/window_count").toInt());
	ui.open_lag->setValue(configIniRead.value("/start_config/open_lag").toInt());

	QString isZhuxian = configIniRead.value("/script_config/isZhuxian").toString();
	if (isZhuxian == "0") {
		ui.zhuxianCheckBox->setChecked(false);
	}
	else {
		ui.zhuxianCheckBox->setChecked(true);
	}

	int scriptCount = configIniRead.value("/script_config/count").toInt();

	//timeLimitSpinBox
	int time_limit = configIniRead.value("/script_config/time_limit").toInt();
	if (time_limit != 0) {
		ui.timeLimitSpinBox->setValue(time_limit);
	}

	int main_time_limit = configIniRead.value("/script_config/main_time_limit").toInt();
	if (main_time_limit != 0) {
		ui.mainTaskTimeLimitSpinBox->setValue(main_time_limit);
	}

	//settings.setValue("charaComboBox", ui.charaComboBox->currentIndex());
	int zone = configIniRead.value("/script_config/zone").toInt();
	
	ui.zoneComboBox->setCurrentIndex(zone);
	

	scriptClearBtnClicked();
	for (int i = 0; i < scriptCount; i++) {
		QString path = "/script_config/";
		path.append(QString::number(i));

		QString temp = configIniRead.value(path).toString();
		ui.scriptSortList->addItem(temp);
	}
}

QString MainFrame::loadScriptConfig() {
	QJsonObject json;
	string folder = ui.gamePathEditor2->text().toStdString();
	json.insert("folder", QString::fromStdString(folder));

	

	QJsonArray scriptArray;
	for (int i = 0; i < ui.scriptSortList->count(); i++) {
		QListWidgetItem* item = ui.scriptSortList->item(i);
		QString itemString = item->text();
		qDebug() << "item = " << itemString;

		QString interpreted = interpreter(itemString);
		scriptArray.append(interpreted);
	}

	json.insert("scriptArray", QJsonValue(scriptArray));
	if (ui.zhuxianCheckBox->isChecked()) {
		json.insert("isZhuxian", "1");
	}
	else {
		json.insert("isZhuxian", "0");
	}

	if (ui.onlyJulingBox->isChecked()) {
		json.insert("isOnlyJuling", "1");
	}
	else {
		json.insert("isOnlyJuling", "0");
	}

	if (ui.autoResetBox->isChecked()) {
		json.insert("isAutoReset", "1");
	}
	else {
		json.insert("isAutoReset", "0");
	}

	if (ui.isGenAccountBox->isChecked()) {
		json.insert("isGen", "1");
	}
	else {
		json.insert("isGen", "0");
	}
	json.insert("time_limit", ui.timeLimitSpinBox->text());
	json.insert("main_time_limit", ui.mainTaskTimeLimitSpinBox->text());
	json.insert("zone", QString::number(ui.zoneComboBox->currentIndex()));

	json.insert("item_name_parameter", QString::number(ui.itemComboBox->currentIndex()));
	json.insert("item_ye_parameter", ui.yeSpinBox->text());
	json.insert("item_num_parameter", ui.itemNumSpinBox->text());
	
	if (ui.IsBuyCheckBox->isChecked()) {
		json.insert("IsBuyCheckBox", "1");
	}
	else {
		json.insert("IsBuyCheckBox", "0");
	}

	QJsonDocument document;
	document.setObject(json);
	QByteArray byteArray = document.toJson(QJsonDocument::Compact);
	QString strJson(byteArray);
	qDebug() << strJson;

	return strJson;
}

QString MainFrame::interpreter(QString source) {
	if (QString::fromLocal8Bit("师门任务") == source) {
		return "SMRW";
	}

	if (QString::fromLocal8Bit("答题任务") == source) {
		return "DTRW";
	}

	if (QString::fromLocal8Bit("帮派任务") == source) {
		return "BPRW";
	}

	if (QString::fromLocal8Bit("勤修不倦") == source) {
		return "QXBJ";
	}

	if (QString::fromLocal8Bit("斩妖除魔") == source) {
		return "ZYCM";
	}

	if (QString::fromLocal8Bit("及时雨") == source) {
		return "JSY";
	}

	if (QString::fromLocal8Bit("摘星楼") == source) {
		return "ZXL";
	}

	if (QString::fromLocal8Bit("法宝挑战") == source) {
		return "FBTZ";
	}

	if (QString::fromLocal8Bit("帮派修炼") == source) {
		return "BPXL";
	}

	if (QString::fromLocal8Bit("寻仙问道") == source) {
		return "XXWD";
	}

	if (QString::fromLocal8Bit("督粮") == source) {
		return "DLRW";
	}


	if (QString::fromLocal8Bit("寄售购买") == source) {
		return "JSGM";
	}

	return "";
}

//void MainFrame::accountGenBtnClicked() {
//	qDebug() << "accountGenBtnClicked";
//	MainSingleton* theMain = MainSingleton::getInstance();
//
//	int genNumber = ui.accountGenNumSpinbox->text().toInt();
//	theMain->genAccountNum += genNumber;
//	
//	for (int i = 0; i < genNumber; i++) {
//		QString temp1 = "";
//		QString temp2 = "";
//		CommonUtil::setRandAlpabeticString(temp1);
//		CommonUtil::setRandNumberString(temp2);
//		QString account = ui.accoutPrefixLineEdit->text() + temp1 + temp2;
//		QString password = ui.accoutPrefixLineEdit->text() + temp1;
//
//		ui.accountTableWidget->setItem(i + theMain->totalAccountNum, 1, new QTableWidgetItem(account));
//		ui.accountTableWidget->setItem(i + theMain->totalAccountNum, 2, new QTableWidgetItem(password));
//		Sleep(200);
//	}
//
//	ui.windowCounter->setValue(5);
//	ui.isGenAccountBox->setChecked(true);
//}

void MainFrame::simulatorGenBtnClicked() {
	qDebug() << "simulatorGenBtnClicked";

	int genNumber = ui.simulatorNumSpinBox->text().toInt();
	QString command = ui.gamePathEditor2->text() + "//dnconsole.exe add --name";

	for (int i = 0; i < genNumber; i++) {
		WinExec(command.toStdString().c_str(), SW_NORMAL);
		Sleep(1000);
	}


}

void MainFrame::simulatorConfigBtnClicked() {
	qDebug() << "simulatorConfigBtnClicked";
	int start = ui.startConfigSpinBox->text().toInt();
	int end = ui.endConfigSpinBox->text().toInt();

	QString COMMAND_ST = ui.gamePathEditor2->text() + "//dnconsole.exe modify --index ";
	QString memory = ui.memoryNumSpinBox->text();

	for (int i = start; i <= end; i++) {
		QString temp = COMMAND_ST + QString::number(i) + " --resolution 800,450,160 --cpu " + ui.cpuNumSpinBox->text() + "--memory " + memory + " --imei auto --simserial auto --mac auto --androidid auto --imsi auto --lockwindow 1";
		WinExec(temp.toStdString().c_str(), SW_NORMAL);
		Sleep(1000);
	}
}

void MainFrame::apkInstallBtnClicked() {
	qDebug() << "apkInstallBtnClicked";
	int start = ui.startConfigSpinBox->text().toInt();
	int end = ui.endConfigSpinBox->text().toInt();

	QString apkPath = ui.apkPathEditor->text();
	if ("" == apkPath) {
		MessageBox(NULL, L"请先配置APK路径！", L"警告!", MB_OK);
		return;
	}
	QString COMMAND_ST = ui.gamePathEditor2->text() + "//dnconsole.exe installapp --index ";

	for (int i = start; i <= end; i++) {
		QString temp = COMMAND_ST + QString::number(i) + " --filename " + ui.apkPathEditor->text();
		WinExec(temp.toStdString().c_str(), SW_NORMAL);
		Sleep(1000);
	}
}
///simulatorCloseBtnClicked
void MainFrame::simulatorCloseBtnClicked() {
	qDebug() << "simulatorCloseBtnClicked";
	int start = ui.startConfigSpinBox->text().toInt();
	int end = ui.endConfigSpinBox->text().toInt();

	QString COMMAND_ST = ui.gamePathEditor2->text() + "//dnconsole.exe quit --index ";

	for (int i = start; i <= end; i++) {
		QString temp = COMMAND_ST + QString::number(i);
		WinExec(temp.toStdString().c_str(), SW_NORMAL);
		Sleep(1000);
	}
}
//downCpuBtnClickedClicked
void MainFrame::downCpuBtnClickedClicked() {
	qDebug() << "downCpuBtnClickedClicked";
	int start = ui.startConfigSpinBox->text().toInt();
	int end = ui.endConfigSpinBox->text().toInt();

	QString COMMAND_ST = ui.gamePathEditor2->text() + "//dnconsole.exe downcpu --index ";

	for (int i = start; i <= end; i++) {
		QString temp = COMMAND_ST + QString::number(i) +  " --rate 50";
		WinExec(temp.toStdString().c_str(), SW_NORMAL);
		Sleep(1000);
	}
}

void MainFrame::goldCalculatorBtnClicked() {
	qDebug() << "goldCalculatorBtnClicked";
	//loadAllMoney();
}
//

void MainFrame::IsBuyCheckBoxClicked() {
	qDebug() << "IsBuyCheckBoxClicked";
	if (ui.IsBuyCheckBox->isChecked()) {
		ui.onlyJulingBox->setChecked(false);
	}
	//
	if (ui.zhuxianCheckBox->isChecked()) {
		ui.zhuxianCheckBox->setChecked(false);
	}
	scriptClearBtnClicked();
	saohuoTaskBtnClicked();
}

void MainFrame::startBtnClicked() {
	qDebug() << "startBtnClicked";
	findAndroidHander();
	string path = ui.gamePathEditor->text().toStdString();
	string folder = ui.gamePathEditor2->text().toStdString();
	int windowCount = ui.windowCounter->text().toInt();
	int open_lag = ui.open_lag->text().toInt();
	if (path == "") {
		MessageBoxA(NULL, "请设置模拟器路径！", "警告！", MB_OK);
		return;
	}

	QString config = this->loadScriptConfig();

	theMain->config = config;
	theMain->path = path;
	theMain->folder = folder;

	if (theMain->accountIndex == 0) {
		int tempInt = ui.startIDSpinBox->text().toInt();
		theMain->setStartAccountID(tempInt - 1);
	}

	StartThread* thread = new StartThread(path, folder, windowCount, open_lag, config);
	thread->setOperationParameter(OPEN_WINDOW);
	thread->cpuNumber = ui.cpuNumSpinBox->text().toInt();
	thread->memoryNumber = ui.memoryNumSpinBox->text().toInt();
	thread->isAutoReset = ui.autoResetBox->isChecked();
	thread->start();
}

int MainFrame::bindSimilatorHandler() {

	return 0;
}


void MainFrame::baseConfigBtnClicked() {
	qDebug() << "baseConfigBtnClicked";

	generalConfiguration("config/base.ini");
}

void MainFrame::readBtn1Clicked() {

	qDebug() << "readBtn1Clicked";
	generalLoadConfig("config/config1.ini");
}

void MainFrame::readBtn2Clicked() {

	qDebug() << "readBtn2Clicked";
	generalLoadConfig("config/config2.ini");
}

void MainFrame::readBtn3Clicked() {

	qDebug() << "readBtn3Clicked";
	generalLoadConfig("config/config3.ini");
}

void MainFrame::readBtn4Clicked() {

	qDebug() << "readBtn4Clicked";
	generalLoadConfig("config/config4.ini");
}

void MainFrame::readBtn5Clicked() {

	qDebug() << "readBtn5Clicked";
	generalLoadConfig("config/config5.ini");
}

void MainFrame::writeBtn1Clicked() {

	qDebug() << "writeBtn1Clicked";
	generalConfiguration("config/config1.ini");
}

void MainFrame::writeBtn2Clicked() {

	qDebug() << "writeBtn2Clicked";
	generalConfiguration("config/config2.ini");
}

void MainFrame::writeBtn3Clicked() {

	qDebug() << "writeBtn3Clicked";
	generalConfiguration("config/config3.ini");
}

void MainFrame::writeBtn4Clicked() {

	qDebug() << "writeBtn4Clicked";
	generalConfiguration("config/config4.ini");
}

void MainFrame::writeBtn5Clicked() {

	qDebug() << "writeBtn5Clicked";
	generalConfiguration("config/config5.ini");
}

