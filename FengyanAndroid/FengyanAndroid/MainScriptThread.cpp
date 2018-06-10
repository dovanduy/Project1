#include "MainScriptThread.h"
#include "CommonUtil.h"
#include "PskCommonHelper.h"

MainScriptThread::MainScriptThread(QObject *parent)
	: QThread(parent)
{
	
}

MainScriptThread::~MainScriptThread()
{
}

MainScriptThread::MainScriptThread(long HWND, QString config, int index, int accountIndex) {
	this->lHWND = HWND;
	this->config = config;
	this->index = index;
	this->accountIndex = accountIndex;
	this->mainStepIndex = MAIN_STEPS::WAIT_LOGIN;
	this->scriptIndex = 0;
	this->huodongSkipCounter = 0;
	this->currentLevel = 0;
	this->isBanghui = false;
	this->bangpaiCounter = 0;
	this->shimenCounter = 0;
	this->zhanyaoCounter = 0;
	this->xunxianCounter = 0;
	this->lastJulingTime = 0;
	this->errorCounter = 0;
	this->isGen = false;
	this->huiheCounter = 0;
	this->enterGameCounter = 0;
	this->isFuliGot = false;
	this->currentMoney = 0;
	this->isSkillUpdated = false;
}

void MainScriptThread::run() {
	CoInitializeEx(NULL, COINIT_MULTITHREADED);
	MainSingleton* main = MainSingleton::getInstance();

	this->getThreadFire();
	this->getThreadAccount(this->accountIndex);
	this->getConfig(this->config);
	this->startTime = timeGetTime();

	int ret = this->bindMyWnd(this->lHWND);
	if(ret != 1) {
		long error = this->myFire->PskGetLastError();

		string msg = "绑定失败！原因是：";
		msg.append(CommonUtil::Long2STR(error).c_str());
		MessageBoxA(NULL, msg.c_str(), "Error", MB_OK);
		return;
	}

	int myCounter = 0;
	while (this->getIsEnded() == false) {
		//int ret = PskCommonHelper::CommonCapture(this->myFire, 0, 0, 500, 500, "test.jpg");
		if (this->getIsPaused()) {
			Sleep(10000);
			continue;
		}

		main->table->setItem(index - 1, 6, new QTableWidgetItem(QString::number(errorCounter)));

		findZhinengZudui();
		clickShiyongBtn();
		clickCenterQuedingBtn();
		clickFangzhiBtn();
		clickChuanshangBtn();
		clickSubCloseBtn(false);
		this->timerChecker();
		this->getCurrentMoney();
		this->updateSkills();

		if (this->currentLevel == 0 && this->IsBuyCheckBox == false) {
			this->getCurrentLevel();
		}

		if (this->lastJulingTime == 0) {
			this->forJuling();
		}

		this->getMyFuli();

		myCounter++;
		if (myCounter == 20) {
			this->movePigIcon();
			forJuling();
			this->getCurrentLevel();
			myCounter = 0;
		}

		if (this->isGen) {
			this->mainStepIndex = MAIN_STEPS::REGISTER;
		}

		switch (this->mainStepIndex)
		{
		case MAIN_STEPS::WAIT_LOGIN : {
			this->EnterGameSubScript();
		}break;
		case MAIN_STEPS::MAIN_TASK: {
			if (this->isZhuxian == false) {
				this->mainStepIndex = MAIN_STEPS::GENERAL_TASK;
				break;
			}

			this->MainTaskSubScript();
		}break;
		case MAIN_STEPS::GENERAL_TASK: {
			
			this->GeneralTaskSubScript();
		}break;
		case MAIN_STEPS::REGISTER: {
			this->accountIndex = this->index + main->totalAccountNum;
			main->setRegisterID(main->totalAccountNum + 1);
			int tempCounter = 0;
			while (findAndEnterGame(1) == 0) {
				Sleep(2000);
				tempCounter++;
				if (tempCounter > 10) {
					tempCounter = 0;
					break;
				}
			}
			Sleep(2000);
			clickZhidaoBtn();

			for (int i = 0; i < main->genAccountNum; i+= main->windowCounterBox->text().toInt()) {
				this->RegisterSubScript();
			}
			
			if (this->isGen) {
				main->table->setItem(index - 1, 2, new QTableWidgetItem(QString::fromLocal8Bit("注册完毕")));
				main->table->setItem(index - 1, 0, new QTableWidgetItem("222220"));

				return;
			}

			

		}break;
		default:
			break;
		}

		if (doLibaoTask() == 1) {
			PskCommonHelper::CommonMoveTo(this->myFire, 605, 200);
			PskCommonHelper::CommonLClick(this->myFire);
			Sleep(2000);
		}

		if (doShengjicailiaoTask() == 1) {
			PskCommonHelper::CommonMoveTo(this->myFire, 545, 165);
			PskCommonHelper::CommonLClick(this->myFire);
			Sleep(2000);
			PskCommonHelper::CommonMoveTo(this->myFire, 475, 300);
			PskCommonHelper::CommonLClick(this->myFire);
			Sleep(2000);
			PskCommonHelper::CommonMoveTo(this->myFire, 620, 420);
			PskCommonHelper::CommonLClick(this->myFire);
			Sleep(2000);
			PskCommonHelper::CommonMoveTo(this->myFire, 210, 265);
			PskCommonHelper::CommonLClick(this->myFire);
			Sleep(2000);
			PskCommonHelper::CommonMoveTo(this->myFire, 400, 185);
			PskCommonHelper::CommonLClick(this->myFire);
			Sleep(2000);
		}

		if (doLibaoTask() == 1) {
			PskCommonHelper::CommonMoveTo(this->myFire, 605, 200);
			PskCommonHelper::CommonLClick(this->myFire);
			Sleep(2000);
		}

		if (doKaishiTask() == 1) {
			PskCommonHelper::CommonMoveTo(this->myFire, 730, 180);
			PskCommonHelper::CommonLClick(this->myFire);
			Sleep(2000);
		}



		if (doChongwuTask() == 1) {
			PskCommonHelper::CommonMoveTo(this->myFire, 605, 70);
			PskCommonHelper::CommonLClick(this->myFire);
			Sleep(2000);
			PskCommonHelper::CommonMoveTo(this->myFire, 605, 440);
			PskCommonHelper::CommonLClick(this->myFire);
			Sleep(2000);
		}

		if (doFashuTask() == 1) {
			movePigIcon();
			Sleep(2000);
			PskCommonHelper::CommonMoveTo(this->myFire, 780, 285);
			PskCommonHelper::CommonLClick(this->myFire);
			Sleep(2000);
			PskCommonHelper::CommonMoveTo(this->myFire, 705, 365);
			PskCommonHelper::CommonLClick(this->myFire);
			Sleep(2000);
			PskCommonHelper::CommonMoveTo(this->myFire, 645, 365);
			PskCommonHelper::CommonLClick(this->myFire);
			Sleep(2000);
			PskCommonHelper::CommonMoveTo(this->myFire, 250, 215);
			PskCommonHelper::CommonLClick(this->myFire);
			Sleep(2000);

		}

		if (this->doFuliTask() == 1) {
			PskCommonHelper::CommonMoveTo(this->myFire, 705, 285);
			PskCommonHelper::CommonLClick(this->myFire);
			Sleep(2000);
			PskCommonHelper::CommonMoveTo(this->myFire, 620, 300);
			PskCommonHelper::CommonLClick(this->myFire);
			Sleep(2000);
		}

		if (currentLevel < 35) {
			if (doGudingduiTask() == 1) {
				PskCommonHelper::CommonMoveTo(this->myFire, 610, 460);
				PskCommonHelper::CommonLClick(this->myFire);
				Sleep(2000);
				PskCommonHelper::CommonMoveTo(this->myFire, 710, 210);
				PskCommonHelper::CommonLClick(this->myFire);
				Sleep(2000);
				PskCommonHelper::CommonMoveTo(this->myFire, 610, 435);
				PskCommonHelper::CommonLClick(this->myFire);
				Sleep(2000);
				PskCommonHelper::CommonMoveTo(this->myFire, 200, 435);
				PskCommonHelper::CommonLClick(this->myFire);
				Sleep(2000);
			}

			

			if (this->doQianghuaTask() == 1) {
				PskCommonHelper::CommonMoveTo(this->myFire, 560, 455);
				PskCommonHelper::CommonLClick(this->myFire);
				Sleep(2000);
				PskCommonHelper::CommonMoveTo(this->myFire, 710, 355);
				PskCommonHelper::CommonLClick(this->myFire);
				Sleep(2000);
				PskCommonHelper::CommonMoveTo(this->myFire, 220, 180);
				PskCommonHelper::CommonLClick(this->myFire);
				Sleep(2000);
				PskCommonHelper::CommonMoveTo(this->myFire, 420, 180);
				PskCommonHelper::CommonLClick(this->myFire);
				Sleep(2000);
				PskCommonHelper::CommonMoveTo(this->myFire, 550, 200);
				PskCommonHelper::CommonLClick(this->myFire);
				Sleep(2000);
				PskCommonHelper::CommonMoveTo(this->myFire, 495, 300);
				PskCommonHelper::CommonLClick(this->myFire);
				Sleep(2000);
				PskCommonHelper::CommonMoveTo(this->myFire, 610, 430);
				PskCommonHelper::CommonLClick(this->myFire);
				Sleep(2000);
				PskCommonHelper::CommonMoveTo(this->myFire, 220, 240);
				PskCommonHelper::CommonLClick(this->myFire);
				Sleep(2000);
				PskCommonHelper::CommonMoveTo(this->myFire, 420, 180);
				PskCommonHelper::CommonLClick(this->myFire);
				Sleep(2000);
				PskCommonHelper::CommonMoveTo(this->myFire, 550, 200);
				PskCommonHelper::CommonLClick(this->myFire);
				Sleep(2000);
				PskCommonHelper::CommonMoveTo(this->myFire, 610, 425);
				PskCommonHelper::CommonLClick(this->myFire);
				Sleep(2000);
			}

			if (this->doPaihangbangTask() == 1) {
				PskCommonHelper::CommonMoveTo(this->myFire, 720, 460);
				PskCommonHelper::CommonLClick(this->myFire);
				Sleep(2000);
			}

			if (this->doJulingTask() == 1) {
				PskCommonHelper::CommonMoveTo(this->myFire, 355, 70);
				PskCommonHelper::CommonLClick(this->myFire);
				Sleep(2000);
				PskCommonHelper::CommonMoveTo(this->myFire, 195, 170);
				PskCommonHelper::CommonLClick(this->myFire);
				Sleep(2000);
				PskCommonHelper::CommonMoveTo(this->myFire, 635, 170);
				PskCommonHelper::CommonLClick(this->myFire);
				Sleep(2000);
				PskCommonHelper::CommonMoveTo(this->myFire, 620, 435);
				PskCommonHelper::CommonLClick(this->myFire);
				Sleep(2000);
				PskCommonHelper::CommonMoveTo(this->myFire, 420, 185);
				PskCommonHelper::CommonLClick(this->myFire);
				Sleep(2000);
			}

			if (this->doChuandaiTask() == 1) {
				PskCommonHelper::CommonMoveTo(this->myFire, 665, 385);
				PskCommonHelper::CommonLClick(this->myFire);
				Sleep(2000);
			}

			if (this->doSouhuTask() == 1) {
				PskCommonHelper::CommonMoveTo(this->myFire, 720, 460);
				PskCommonHelper::CommonLClick(this->myFire);
				Sleep(2000);
				PskCommonHelper::CommonMoveTo(this->myFire, 620, 140);
				PskCommonHelper::CommonLClick(this->myFire);
				Sleep(2000);
				PskCommonHelper::CommonMoveTo(this->myFire, 400, 145);
				PskCommonHelper::CommonLClick(this->myFire);
				Sleep(2000);
				PskCommonHelper::CommonMoveTo(this->myFire, 180, 195);
				PskCommonHelper::CommonLClick(this->myFire);
				Sleep(1000);
				PskCommonHelper::CommonLClick(this->myFire);
				Sleep(2000);
				PskCommonHelper::CommonMoveTo(this->myFire, 650, 140);
				PskCommonHelper::CommonLClick(this->myFire);
				Sleep(2000);
				PskCommonHelper::CommonMoveTo(this->myFire, 620, 390);
				PskCommonHelper::CommonLClick(this->myFire);
				Sleep(2000);
				PskCommonHelper::CommonMoveTo(this->myFire, 620, 320);
				PskCommonHelper::CommonLClick(this->myFire);
				Sleep(2000);
				PskCommonHelper::CommonMoveTo(this->myFire, 560, 275);
				PskCommonHelper::CommonLClick(this->myFire);
				Sleep(2000);
				clickCloseBtn();
			}

			if (findShuxingJiadian() == 1) {
				PskCommonHelper::CommonMoveTo(this->myFire, 255, 365);
				PskCommonHelper::CommonLClick(this->myFire);
				Sleep(2000);
				PskCommonHelper::CommonMoveTo(this->myFire, 615, 135);
				PskCommonHelper::CommonLClick(this->myFire);
				Sleep(2000);
			}

			if (doRenwushuxingTask() == 1) {
				PskCommonHelper::CommonMoveTo(this->myFire, 770, 80);
				PskCommonHelper::CommonLClick(this->myFire);
				Sleep(2000);
				PskCommonHelper::CommonMoveTo(this->myFire, 710, 360);
				PskCommonHelper::CommonLClick(this->myFire);
				Sleep(2000);
				PskCommonHelper::CommonMoveTo(this->myFire, 405, 195);
				PskCommonHelper::CommonLClick(this->myFire);
				Sleep(2000);
				PskCommonHelper::CommonMoveTo(this->myFire, 615, 450);
				PskCommonHelper::CommonLClick(this->myFire);
				Sleep(2000);
				clickCloseBtn();
			}

			if (doJiangliTask() == 1) {
				movePigIcon();
				PskCommonHelper::CommonMoveTo(this->myFire, 12, 285);
				PskCommonHelper::CommonLClick(this->myFire);
				Sleep(2000);
				PskCommonHelper::CommonMoveTo(this->myFire, 600, 200);
				PskCommonHelper::CommonLClick(this->myFire);
				Sleep(2000);
				PskCommonHelper::CommonMoveTo(this->myFire, 660, 385);
				PskCommonHelper::CommonLClick(this->myFire);
				Sleep(2000);
				clickCloseBtn();
			}

			if (doShangzhenTask() == 1) {
				PskCommonHelper::CommonMoveTo(this->myFire, 660, 405);
				PskCommonHelper::CommonLClick(this->myFire);
				Sleep(2000);
			}

			if (doBangpaiTask() == 1) {
				PskCommonHelper::CommonMoveTo(this->myFire, 665, 460);
				PskCommonHelper::CommonLClick(this->myFire);
				Sleep(2000);
				PskCommonHelper::CommonMoveTo(this->myFire, 315, 230);
				PskCommonHelper::CommonLClick(this->myFire);
				Sleep(2000);
				PskCommonHelper::CommonMoveTo(this->myFire, 635, 440);
				PskCommonHelper::CommonLClick(this->myFire);
				Sleep(2000);
				clickCloseBtn();
			}

			if (doZhangaiTask() == 1) {
				PskCommonHelper::CommonMoveTo(this->myFire, 395, 125);
				PskCommonHelper::CommonLClick(this->myFire);
				Sleep(2000);
				PskCommonHelper::CommonMoveTo(this->myFire, 480, 195);
				PskCommonHelper::CommonLClick(this->myFire);
				Sleep(2000);
				PskCommonHelper::CommonMoveTo(this->myFire, 620, 450);
				PskCommonHelper::CommonLClick(this->myFire);
				Sleep(2000);
				clickCloseBtn();
			}
		}

		

		Sleep(5000);
	}

	

	QTableWidget* table = main->table;
	QTableWidgetItem* item = table->item(index - 1, 1);
	if (item == NULL) {
		return;
	}

	QString text = item->text();
	if (text == "000008") {
		table->setItem(index - 1, 2, new QTableWidgetItem(QString::fromLocal8Bit("已结束")));
		table->setItem(index - 1, 1, new QTableWidgetItem(QString::fromLocal8Bit("000000")));
	}


	item = table->item(index - 1, 0);
	if (item == NULL) {
		return;
	}

	text = item->text();
	if (text == "222220") {
		table->setItem(index - 1, 2, new QTableWidgetItem(QString::fromLocal8Bit("已停止")));
		table->setItem(index - 1, 0, new QTableWidgetItem(QString::fromLocal8Bit("222222")));
	}

	if (text == "222221") {
		table->setItem(index - 1, 2, new QTableWidgetItem(QString::fromLocal8Bit("已完成")));
		table->setItem(index - 1, 0, new QTableWidgetItem(QString::fromLocal8Bit("222222")));
	}

	if (text == "000009") {
		table->setItem(index - 1, 2, new QTableWidgetItem(QString::fromLocal8Bit("单个角色结束")));
		table->setItem(index - 1, 0, new QTableWidgetItem(QString::fromLocal8Bit("000019")));
	}

	PskCommonHelper::CommonUnbindWindow(this->myFire);
	PskCommonHelper::CommonRelease(this->myFire);
}

bool MainScriptThread::getIsEnded()
{
	MainSingleton* main = MainSingleton::getInstance();
	QTableWidget* table = main->table;
	QTableWidgetItem* item = table->item(index - 1, 1);
	if (item == NULL) {
		return false;
	}

	QString tHWND = item->text();
	if (tHWND == "000000" || tHWND == "000008" ) {
		return true;
	}

	item = table->item(index - 1, 0);
	if (item == NULL) {
		return false;
	}

	tHWND = item->text();
	if (tHWND == "222220" || tHWND == "222222" || tHWND == "222220" || tHWND == "222221" || tHWND == "000009" || tHWND == "000019") {
		return true;
	}

	return false;
}

int MainScriptThread::GeneralTaskSubScript() {
	QString currentTask;
	MainSingleton* main = MainSingleton::getInstance();
	QJsonValue value = this->scriptList.at(scriptIndex);
	if (value.isString()) {
		currentTask = value.toString();
	}

	
	qDebug() << "currentTask = " << currentTask;
	//this->movePigIcon();
	if (currentTask == "SMRW") {
		clickJinruzhandouBtn();
		while (findHuiheIcon() == 1 && getIsEnded() == false) {
			main->table->setItem(index - 1, 2, new QTableWidgetItem(QString::fromLocal8Bit("师门回合")));
			Sleep(3000);
		}
		shimenCounter++;
		if (shimenCounter > 100) {
			this->scriptIndex++;
			this->clickDuihuaCloseBtn(1);
			shimenCounter = 0;
			return 0;
		}

		main->table->setItem(index - 1, 2, new QTableWidgetItem(QString::fromLocal8Bit("师门任务")));
		if (clickHuodongBtn() == 1){
			if (canjiaShimenHuodong() == 0) {
				this->huodongSkipCounter++;
			}
			else {
				this->huodongSkipCounter = 0;
			}
			if (huodongSkipCounter >= 5) {
				this->scriptIndex++;
				huodongSkipCounter = 0;
				return 0;
			}
			huiheCounter = 0;
		}
		else {

			huiheCounter++;
			if (huiheCounter > 300) {
				this->scriptIndex = this->scriptList.size();
			}
			clickCloseBtn();
		}
		return 0;
	}

	if (currentTask == "JSGM") {
		shangchengGoumai();

		return 0;
	}

	if (currentTask == "JSY") {
		if (this->currentLevel < 40) {

			this->scriptIndex++;
			return 0;
		}

		clickJinruzhandouBtn();
		
		main->table->setItem(index - 1, 2, new QTableWidgetItem(QString::fromLocal8Bit("及时雨")));
		if (clickHuodongBtn() == 1) {
			if (canjiaJishiyuHuodong() == 0) {
				this->huodongSkipCounter++;
			}
			else {
				this->huodongSkipCounter = 0;
			}
			if (huodongSkipCounter >= 3) {
				this->scriptIndex++;
				huodongSkipCounter = 0;
				return 0;
			}
		}
		else {
			clickCloseBtn();
		}

		if(clickJishiyuBtn() == 1) {
			Sleep(1000);
			clickJishiyuSubBtn();
		}
		return 0;
	}

	if (currentTask == "ZXL") {
		clickJinruzhandouBtn();

		main->table->setItem(index - 1, 2, new QTableWidgetItem(QString::fromLocal8Bit("摘星楼")));
		if (clickHuodongBtn() == 1) {
			if (canjiaZhaixinglouHuodong() == 0) {
				this->huodongSkipCounter++;
			}
			else {
				this->huodongSkipCounter = 0;
			}
			if (huodongSkipCounter >= 3) {
				this->scriptIndex++;
				huodongSkipCounter = 0;
				return 0;
			}
		}
		else {
			clickCloseBtn();
		}

		if (clickZhaixinglouBtn() == 1) {
			Sleep(1000);
			clickZhaixingJingyanBtn();
			Sleep(1000);
			clickZhaixingDaohangBtn();
			Sleep(5000);
			clickZhaixingSub();
			Sleep(3000);
			
		}

		clickJinruzhandouBtn();
		return 0;
	}

	if (currentTask == "FBTZ") {
		clickJinruzhandouBtn();

		while (findHuiheIcon() == 1 && getIsEnded() == false) {
			main->table->setItem(index - 1, 2, new QTableWidgetItem(QString::fromLocal8Bit("法宝回合")));
			Sleep(3000);
		}

		main->table->setItem(index - 1, 2, new QTableWidgetItem(QString::fromLocal8Bit("法宝挑战")));
		if (clickHuodongBtn() == 1) {
			if (canjiaFabaoHuodong() == 0) {
				this->huodongSkipCounter++;
			}
			else {
				this->huodongSkipCounter = 0;
			}
			if (huodongSkipCounter >= 3) {
				this->scriptIndex++;
				huodongSkipCounter = 0;
				return 0;
			}
		}
		else {
			clickCloseBtn();
		}

		int random = CommonUtil::generateRandomNumberEx(2);
		if (random == 0) {
			if (this->clickFabaoTiaozhanBtn() == 1) {
				Sleep(3000);
				if (this->findTiaozhanWnd() == 1) {
					PskCommonHelper::CommonMoveTo(this->myFire, 210, 260);
					PskCommonHelper::CommonLClick(this->myFire);
					Sleep(1000);
					clickFabaoJinzhanBtn();
					Sleep(1000);
					PskCommonHelper::CommonMoveTo(this->myFire, 610, 260);
					PskCommonHelper::CommonLClick(this->myFire);
					Sleep(1000);
					clickFabaoJinzhanBtn();
					Sleep(1000);
				}
				
			}
			
		}
		else {
			if (this->clickShouhuTiaozhanBtn() == 1) {
				Sleep(3000);
				if (this->findTiaozhanWnd() == 1) {
					PskCommonHelper::CommonMoveTo(this->myFire, 210, 260);
					PskCommonHelper::CommonLClick(this->myFire);
					Sleep(1000);
					clickFabaoJinzhanBtn();
					Sleep(1000);
					PskCommonHelper::CommonMoveTo(this->myFire, 610, 260);
					PskCommonHelper::CommonLClick(this->myFire);
					Sleep(1000);
					clickFabaoJinzhanBtn();
					Sleep(1000);
				}
				
			}
		}

		clickCloseBtn();

		return 0;
	}

	if (currentTask == "BPXL") {
		clickJinruzhandouBtn();

		while (findHuiheIcon() == 1 && getIsEnded() == false) {
			main->table->setItem(index - 1, 2, new QTableWidgetItem(QString::fromLocal8Bit("帮派回合")));
			Sleep(3000);
		}

		main->table->setItem(index - 1, 2, new QTableWidgetItem(QString::fromLocal8Bit("帮派修炼")));
		if (clickHuodongBtn() == 1) {
			if (canjiaBangxiuHuodong() == 0) {
				this->huodongSkipCounter++;
			}
			else {
				this->huodongSkipCounter = 0;
			}
			if (huodongSkipCounter >= 3) {
				this->scriptIndex++;
				huodongSkipCounter = 0;
				return 0;
			}
		}
		else {
			clickCloseBtn();
		}

		clickBangxiuBtn();
		clickCloseBtn();

		return 0;
	}

	if (currentTask == "XXWD") {
		clickJinruzhandouBtn();

		if (this->currentLevel < 30) {
			this->scriptIndex++;
			return 0;
		}

		while (findHuiheIcon() == 1 && getIsEnded() == false) {
			main->table->setItem(index - 1, 2, new QTableWidgetItem(QString::fromLocal8Bit("寻仙回合")));
			Sleep(3000);
		}

		xunxianCounter++;
		if (xunxianCounter > 50) {
			this->scriptIndex++;
			xunxianCounter = 0;
			return 0;
		}

		int zuduiRet = 0;
		if (isInDuiwu() == 1) {
			zuduiRet = 1;
		}

		int isXunxianClickNeeded = 0;
		if (zuduiRet == 0) {
			isXunxianClickNeeded = 1;
		}

		main->table->setItem(index - 1, 2, new QTableWidgetItem(QString::fromLocal8Bit("寻仙问道")));
		int isEntered = 0;
		if (clickHuodongBtn() == 1) {
			if (xunxianwendao(isXunxianClickNeeded) == 0) {
				this->huodongSkipCounter++;
			}
			else {
				isEntered = 1;
				this->huodongSkipCounter = 0;
			}
			if (huodongSkipCounter >= 5) {
				this->scriptIndex++;
				this->tuichuDuiwu();
				huodongSkipCounter = 0;
				return 0;
			}
		}
		else {
			clickCloseBtn();
		}

		if (isXunxianClickNeeded == 1 && isEntered == 1) {
			Sleep(10000);
			int tempCounter = 0;
			while (this->clickKuaijiezuduiBtn(0) == 0 && getIsEnded() == false) {
				tempCounter++;
				this->clickDuihuaCloseBtn(1);
				if (tempCounter > 10) {
					break;
				}
				Sleep(3000);
			}

			if (this->clickKuaijiezuduiBtn(1) == 1) {
				Sleep(1000);
				clickZidongpipeiBtn();
				Sleep(2000);
				clickCloseBtn();
				Sleep(1000);
			}
		}
		clickCloseBtn();

		if (clickZuduiBtn() == 1) {
			if (findTuiduiBtn(0) == 1) {
				Sleep(1000);
				clickCloseBtn();
				Sleep(10000);

				//如果一直没有打怪，退队
				int tempCounter = 0;
				while (findHuiheIcon() == 0 && getIsEnded() == false) {
					tempCounter++;
					if (tempCounter > 10) {
						break;
					}
					Sleep(2000);
				}

				if (findHuiheIcon() == 0) {
					tuichuDuiwu();
				}

				//如果在打怪
				while (findHuiheIcon() == 1 && getIsEnded() == false) {
					Sleep(20000);
				}
			}
			else if (findShenqingliebiao(0) == 1) {
				//此乃队长
				/*int tempCounter = 0;
				while (clickTongyiruduiBtn() == 1 && getIsEnded() == false) {
				tempCounter++;
				if (tempCounter > 5) {
				break;
				}
				}

				clickCloseBtn();*/
				PskCommonHelper::CommonMoveTo(this->myFire, 185, 125);
				PskCommonHelper::CommonLClick(this->myFire);
				Sleep(1000);
				findJiesanBtn(1);
			}
			else {
				findJiesanBtn(1);
			}
		}

		return 0;
	}

	if (currentTask == "DLRW") {
		clickJinruzhandouBtn();

		if (this->currentLevel < 25) {
			this->scriptIndex++;
			return 0;
		}

		zhanyaoCounter++;
		if (zhanyaoCounter > 50) {
			this->scriptIndex++;
			this->clickDuihuaCloseBtn(1);
			zhanyaoCounter = 0;
			return 0;
		}

		while (findHuiheIcon() == 1 && getIsEnded() == false) {
			main->table->setItem(index - 1, 2, new QTableWidgetItem(QString::fromLocal8Bit("督粮回合")));
			Sleep(3000);
		}

		int zuduiRet = 0;
		if (isInDuiwu() == 1) {
			zuduiRet = 1;
		}

		int isDLClickNeeded = 0;
		if (zuduiRet == 0) {
			isDLClickNeeded = 1;
		}

		main->table->setItem(index - 1, 2, new QTableWidgetItem(QString::fromLocal8Bit("督粮任务")));
		int isEntered = 0;
		if (clickHuodongBtn() == 1) {
			if (canjiaDuliangHuodong(isDLClickNeeded) == 0) {
				this->huodongSkipCounter++;
			}
			else {
				isEntered = 1;
				this->huodongSkipCounter = 0;
			}
			if (huodongSkipCounter >= 5) {
				this->scriptIndex++;
				this->tuichuDuiwu();
				huodongSkipCounter = 0;
				return 0;
			}
		}
		else {
			clickCloseBtn();
		}

		if (isDLClickNeeded == 1 && isEntered == 1) {
			Sleep(10000);
			int tempCounter = 0;
			while (this->clickKuaijiezuduiBtn(0) == 0 && getIsEnded() == false) {
				tempCounter++;
				if (tempCounter > 10) {
					break;
				}
				Sleep(3000);
			}

			if (this->clickKuaijiezuduiBtn(1) == 1) {
				Sleep(1000);
				clickZidongpipeiBtn();
				Sleep(2000);
				clickCloseBtn();
				Sleep(1000);
			}
		}
		clickCloseBtn();

		if (clickZuduiBtn() == 1) {
			if (findTuiduiBtn(0) == 1) {
				Sleep(1000);
				clickCloseBtn();
				Sleep(10000);

				//如果一直没有打怪，退队
				int tempCounter = 0;
				while (findHuiheIcon() == 0 && getIsEnded() == false) {
					tempCounter++;
					if (tempCounter > 10) {
						break;
					}
					Sleep(2000);
				}

				if (findHuiheIcon() == 0) {
					tuichuDuiwu();
				}

				//如果在打怪
				while (findHuiheIcon() == 1 && getIsEnded() == false) {
					Sleep(20000);
				}
			}
			else if (findShenqingliebiao(0) == 1) {
				//此乃队长
				/*int tempCounter = 0;
				while (clickTongyiruduiBtn() == 1 && getIsEnded() == false) {
				tempCounter++;
				if (tempCounter > 5) {
				break;
				}
				}

				clickCloseBtn();*/
				PskCommonHelper::CommonMoveTo(this->myFire, 185, 125);
				PskCommonHelper::CommonLClick(this->myFire);
				Sleep(1000);
				findJiesanBtn(1);
			}
			else {
				findJiesanBtn(1);
			}
		}

		return 0;
	}

	if (currentTask == "BPRW") {

		if (this->currentLevel < 25) {
			this->scriptIndex++;
			return 0;
		}

		while (findHuiheIcon() == 1 && getIsEnded() == false) {
			main->table->setItem(index - 1, 2, new QTableWidgetItem(QString::fromLocal8Bit("帮派回合")));
			Sleep(3000);
		}

		bangpaiCounter++;
		if (bangpaiCounter > 100) {
			this->scriptIndex++;
			bangpaiCounter = 0;
			return 0;
		}


		if (this->isBanghui == false) {
			jiaruBangpai();
		}

		clickJinruzhandouBtn();
		this->clickLingquBangwuBtn();
		main->table->setItem(index - 1, 2, new QTableWidgetItem(QString::fromLocal8Bit("帮派任务")));
		if (clickHuodongBtn() == 1) {
			if (canjiaBangpaiRenwu() == 0) {
				this->huodongSkipCounter++;
			}
			else {
				
				this->huodongSkipCounter = 0;
			}
			if (huodongSkipCounter >= 5) {
				this->scriptIndex++;
				huodongSkipCounter = 0;
				return 0;
			}

		}
		else {
			clickCloseBtn();
		}

		return 0;
	}

	if (currentTask == "") {

		if (this->currentLevel < 30 && this->errorCounter < 20 && this->isOnlyJuling == false && this->IsBuyCheckBox == false) {
			this->mainStepIndex = MAIN_STEPS::MAIN_TASK;
			this->scriptIndex = 0;
			return 0;
		}
		

		if (this->errorCounter < 20){
			main->table->setItem(index - 1, 2, new QTableWidgetItem(QString::fromLocal8Bit("结束")));
			main->table->setItem(index - 1, 0, new QTableWidgetItem("000009"));

			QHash<int, int>::iterator iter = main->rowAccountMap.find(index);
			int thisAccountIndex = iter.value();

			if (thisAccountIndex < main->totalAccountNum && main->accountIndex < main->totalAccountNum) {
				int tempIndex = this->accountIndex;
				int theAccountIndex = main->getTheAccountIndex();
				main->rowAccountMap.insert(index, theAccountIndex);
				main->idsMap.remove(tempIndex);
			} 
		}
		else {
			main->table->setItem(index - 1, 2, new QTableWidgetItem(QString::fromLocal8Bit("结束")));
			main->table->setItem(index - 1, 0, new QTableWidgetItem("000009"));
		}

		
	}

	if (currentTask == "QXBJ") {

		if (this->currentLevel < 25) {
			this->scriptIndex++;
			return 0;
		}

		while (findHuiheIcon() == 1 && getIsEnded() == false) {
			main->table->setItem(index - 1, 2, new QTableWidgetItem(QString::fromLocal8Bit("勤修回合")));
			Sleep(3000);
		}

		clickQinxiuBtn();
		clickJinruzhandouBtn();
		this->clickLingquBangwuBtn();
		main->table->setItem(index - 1, 2, new QTableWidgetItem(QString::fromLocal8Bit("勤修不倦")));
		if (clickHuodongBtn() == 1) {
			if (canjiaQinxiuRenwu() == 0) {
				this->huodongSkipCounter++;
			}
			else {

				this->huodongSkipCounter = 0;
			}
			if (huodongSkipCounter >= 3) {
				this->scriptIndex++;
				huodongSkipCounter = 0;
				return 0;
			}
			clickCloseBtn();
		}
		else {
			clickCloseBtn();
		}
		return 0;
	}

	if (currentTask == "ZYCM") {

		while (findHuiheIcon() == 1 && getIsEnded() == false) {
			main->table->setItem(index - 1, 2, new QTableWidgetItem(QString::fromLocal8Bit("斩妖回合")));
			Sleep(3000);
		}

		zhanyaoCounter++;
		if (zhanyaoCounter > 50) {
			this->scriptIndex++;
			this->clickDuihuaCloseBtn(1);
			zhanyaoCounter = 0;
			return 0;
		}

		main->table->setItem(index - 1, 2, new QTableWidgetItem(QString::fromLocal8Bit("斩妖除魔")));
		
		int zuduiRet = 0;
		if (isInDuiwu() == 1) {
			zuduiRet = 1;
		}

		int isZhanyaoClickNeeded = 0;
		if (zuduiRet == 0) {
			isZhanyaoClickNeeded = 1;
		}
		if (clickHuodongBtn() == 1) {
			if (canjiaZhanyaoRenwu(isZhanyaoClickNeeded) == 0) {
				this->huodongSkipCounter++;
				clickCloseBtn();
			}
			else {

				this->huodongSkipCounter = 0;
			}
			if (huodongSkipCounter >= 3) {
				this->scriptIndex++;
				this->tuichuDuiwu();
				huodongSkipCounter = 0;
				return 0;
			}
			
			if (isZhanyaoClickNeeded == 1) {
				Sleep(10000);
				int tempCounter = 0;
				while (this->clickKuaijiezuduiBtn(0) == 0 && getIsEnded() == false) {
					tempCounter++;
					if (tempCounter > 10) {
						break;
					}
					Sleep(3000);
				}

				if (this->clickKuaijiezuduiBtn(1) == 1) {
					Sleep(1000);
					clickZidongpipeiBtn();
					Sleep(2000);
					clickCloseBtn();
					Sleep(1000);
				}
			}
			

			clickCloseBtn();
		}
		else {
			clickCloseBtn();
		}

		
		

		if (clickZuduiBtn() == 1) {
			if (findTuiduiBtn(0) == 1) {
				Sleep(1000);
				clickCloseBtn();
				Sleep(10000);

				//如果一直没有打怪，退队
				int tempCounter = 0;
				while (findHuiheIcon() == 0 && getIsEnded() == false) {
					tempCounter++;
					if (tempCounter > 10) {
						break;
					}
					Sleep(2000);
				}

				if (findHuiheIcon() == 0) {
					tuichuDuiwu();
				}

				//如果在打怪
				while (findHuiheIcon() == 1 && getIsEnded() == false) {
					Sleep(20000);
				}
			}
			else if (findShenqingliebiao(0) == 1) {
				//此乃队长
				/*int tempCounter = 0;
				while (clickTongyiruduiBtn() == 1 && getIsEnded() == false) {
					tempCounter++;
					if (tempCounter > 5) {
						break;
					}
				}

				clickCloseBtn();*/
				PskCommonHelper::CommonMoveTo(this->myFire,185, 125);
				PskCommonHelper::CommonLClick(this->myFire);
				Sleep(1000);
				findJiesanBtn(1);
			}
			else {
				findJiesanBtn(1);
			}
		}
		return 0;
	}
	return 0;
}

int MainScriptThread::getDailyAward() {
	PskCommonHelper::CommonMoveTo(this->myFire, 330, 400);
	PskCommonHelper::CommonLClick(this->myFire);
	Sleep(1000);
	PskCommonHelper::CommonMoveTo(this->myFire, 400, 400);
	PskCommonHelper::CommonLClick(this->myFire);
	Sleep(1000);
	PskCommonHelper::CommonMoveTo(this->myFire, 480, 400);
	PskCommonHelper::CommonLClick(this->myFire);
	Sleep(1000);
	PskCommonHelper::CommonMoveTo(this->myFire, 555, 400);
	PskCommonHelper::CommonLClick(this->myFire);
	Sleep(1000);
	PskCommonHelper::CommonMoveTo(this->myFire, 630, 400);
	PskCommonHelper::CommonLClick(this->myFire);
	Sleep(1000);

	return 0;
}

int MainScriptThread::tuichuDuiwu() {
	int ret = 0;
	if (clickZuduiBtn() == 0) {
		clickCloseBtn();
	}
	else {
		if (findTuiduiBtn(1) == 1) {
			ret = 1;
		}
		clickCloseBtn();
	}

	return ret;
}

int MainScriptThread::duliangTask() {
	
	if (clickZuduiBtn() == 0) {
		clickCloseBtn();
	}
	else {
		if (clickRichangBtn() == 1) {

		}
		clickCloseBtn();
	}

	return 0;
}

int MainScriptThread::isInDuiwu() {
	int ret = 0;
	if (clickZuduiBtn() == 0) {
		clickCloseBtn();
	}
	else {
		if (findTuiduiBtn(0) == 1) {
			ret = 1;
		}
		clickGuiduiBtn();
		clickCloseBtn();
	}


	return ret;
}

int MainScriptThread::MainTaskSubScript() {
	MainSingleton* main = MainSingleton::getInstance();
	main->table->setItem(index - 1, 2, new QTableWidgetItem(QString::fromLocal8Bit("主线任务")));
	clickCloseBtn();
	Sleep(1000);
	if (clickTaskBtn() == 1) {
		if (findLevelNotEnough(0) == 1) {
			this->mainStepIndex = MAIN_STEPS::GENERAL_TASK;
			clickCloseBtn();
			return 0;
		}
		if (findZhuxianTaskTitle(0) == 1) {
			clickQianwangBtn();
			clickGoumaiBtn();

			if (clickCloseBtn() == 1) {
				Sleep(2000);
				if (clickCloseBtn() == 1) {
					this->errorCounter++;
					if (this->errorCounter > 20) {
						this->mainStepIndex = MAIN_STEPS::GENERAL_TASK;
						this->scriptIndex = this->scriptList.size();
					}
				}
				else {
					this->errorCounter = 0;
				}
			}
			else {
				this->errorCounter = 0;
			}
		}
		
	}
	else if (clickDuihuaIcon() == 1) {
		qDebug() << "duihua";
	}


	if (this->currentLevel > 30) {
		this->mainStepIndex = MAIN_STEPS::GENERAL_TASK;
		this->scriptIndex = 0;
		return 0;
	}

	this->clickJinruzhandouBtn();
	
	if (doLibaoTask() == 1) {
		PskCommonHelper::CommonMoveTo(this->myFire, 605, 200);
		PskCommonHelper::CommonLClick(this->myFire);
		Sleep(2000);
	}

	

	if (doKaishiTask() == 1) {
		PskCommonHelper::CommonMoveTo(this->myFire, 730, 180);
		PskCommonHelper::CommonLClick(this->myFire);
		Sleep(2000);
	}

	

	if (doChongwuTask() == 1) {
		PskCommonHelper::CommonMoveTo(this->myFire, 605, 70);
		PskCommonHelper::CommonLClick(this->myFire);
		Sleep(2000);
		PskCommonHelper::CommonMoveTo(this->myFire, 605, 440);
		PskCommonHelper::CommonLClick(this->myFire);
		Sleep(2000);
	}

	if (doFashuTask() == 1) {
		movePigIcon();
		Sleep(2000);
		PskCommonHelper::CommonMoveTo(this->myFire, 780, 285);
		PskCommonHelper::CommonLClick(this->myFire);
		Sleep(2000);
		PskCommonHelper::CommonMoveTo(this->myFire, 705, 365);
		PskCommonHelper::CommonLClick(this->myFire);
		Sleep(2000);
		PskCommonHelper::CommonMoveTo(this->myFire, 645, 365);
		PskCommonHelper::CommonLClick(this->myFire);
		Sleep(2000);
		PskCommonHelper::CommonMoveTo(this->myFire, 250, 215);
		PskCommonHelper::CommonLClick(this->myFire);
		Sleep(2000);

	}

	while (findHuiheIcon() == 1 && getIsEnded() == false) {
		main->table->setItem(index - 1, 2, new QTableWidgetItem(QString::fromLocal8Bit("回合中")));
		Sleep(3000);
	}

	clickSkipBtn();
	clickChuanshangBtn();
	clickGoumaiBtn();
	clickGuanruBtn();
	return 0;
}

int MainScriptThread::EnterGameSubScript() {
	MainSingleton* main = MainSingleton::getInstance();
	main->table->setItem(index - 1, 2, new QTableWidgetItem(QString::fromLocal8Bit("登陆游戏")));

	int tempCounter = 0;
	this->errorCounter++;
	if (errorCounter > 20) {
		this->mainStepIndex = MAIN_STEPS::GENERAL_TASK;
		this->scriptIndex = this->scriptList.size();
		
		return 0;
	}

	if (this->clickTaskBtn() == 1) {
		this->mainStepIndex = MAIN_STEPS::GENERAL_TASK;
		return 0;
	}

	if (this->clickZuduiBtn() == 1) {
		this->mainStepIndex = MAIN_STEPS::GENERAL_TASK;
		return 0;
	}

	if (this->clickCloseBtn() == 1) {
		this->mainStepIndex = MAIN_STEPS::GENERAL_TASK;
		return 0;
	}

	while (findAndEnterGame(0) == 0 && clickOtherGameIcon(0) == 0) {
		Sleep(2000);
		tempCounter++;
		if (tempCounter > 20) {
			tempCounter = 0;
			break;
		}
	}

	if (findAndEnterGame(1) == 0) {
		return 0;
	}

	Sleep(2000);
	while (clickZhidaoBtn() == 0 && clickOtherGameIcon(0) == 0) {
		Sleep(2000);
		tempCounter++;
		if (tempCounter > 5) {
			tempCounter = 0;
			break;
		}
	}

	while (clickOtherGameIcon(0) == 0 && getIsEnded() == false) {
		Sleep(2000);
		tempCounter++;
		if (tempCounter > 10) {
			tempCounter = 0;
			break;
		}
	}

	clickOtherGameIcon(1);

	while (skipPhoneNumBind(0) == 0 && getIsEnded() == false) {
		Sleep(2000);
		tempCounter++;
		if (tempCounter > 20) {
			tempCounter = 0;
			break;
		}
	}

	if (skipPhoneNumBind(1) == 0) {
		Sleep(3000);
		while (selectLoginMethod(1) == 0 && getIsEnded() == false) {
			Sleep(2000);
			tempCounter++;
			if (tempCounter > 20) {
				tempCounter = 0;
				break;
			}
		}

		//不能用UI判定登陆界面
		while (findZhanghaoDengluUI() == 0 && getIsEnded() == false) {
			Sleep(2000);
			tempCounter++;
			if (tempCounter > 20) {
				tempCounter = 0;
				break;
			}
		}
		Sleep(2000);
		loginForFeizhu();

		while (findZhanghaoDengluUI() == 1 && getIsEnded() == false) {
			Sleep(2000);
			PskCommonHelper::CommonMoveTo(this->myFire, 405, 350);
			PskCommonHelper::CommonLClick(this->myFire);
			Sleep(2000);

			tempCounter++;
			if (tempCounter > 20) {
				tempCounter = 0;
				break;
			}
		}

		Sleep(2000);
		while (skipPhoneNumBind(1) == 0 && getIsEnded() == false) {
			Sleep(2000);
			tempCounter++;
			if (tempCounter > 20) {
				tempCounter = 0;
				break;
			}
		}
		Sleep(2000);
		while (clickEnterGameBtn(0) == 0 && getIsEnded() == false) {
			Sleep(2000);
			tempCounter++;
			if (tempCounter > 30) {
				tempCounter = 0;
				break;
			}
		}

		if (clickServerBtn(1) == 1) {
			PskCommonHelper::CommonMoveTo(this->myFire, 195, 175);
			PskCommonHelper::CommonLClick(this->myFire);
			Sleep(1000);

			if (this->zone == 1) {
				PskCommonHelper::CommonMoveTo(this->myFire, 365, 155);
				PskCommonHelper::CommonLClick(this->myFire);
			}
			if (this->zone == 0) {
				PskCommonHelper::CommonMoveTo(this->myFire, 560, 155);
				PskCommonHelper::CommonLClick(this->myFire);
			}

			Sleep(1000);
		}

		while (clickEnterGameBtn(1) == 0 && getIsEnded() == false) {
			Sleep(2000);
			tempCounter++;
			if (tempCounter > 30) {
				tempCounter = 0;
				break;
			}
		}

		Sleep(2000);

		if (clickGonggaoCloseBtn() == 1) {
			clickEnterGameBtn(1);
		}

		while (clickKaishiBtn(1) == 0 && getIsEnded() == false) {
			Sleep(2000);
			tempCounter++;
			if (tempCounter > 10) {
				tempCounter = 0;
				break;
			}
		}

		while (clickJueseQuedingBtn(1) == 1 && getIsEnded() == false) {
			Sleep(2000);
			tempCounter++;
			if (tempCounter > 20) {
				tempCounter = 0;
				break;
			}
		}

		if (clickJueseQuedingBtn(1) == 1) {
			this->mainStepIndex = MAIN_STEPS::GENERAL_TASK;
			this->scriptIndex = this->scriptList.size();
			this->errorCounter = 22;
		}

		
	}
	else {
		if (1 == 1) {
			Sleep(2000);
			loginOut();

			while (clickOtherGameIcon(0) == 0 && getIsEnded() == false) {
				Sleep(2000);
				tempCounter++;
				if (tempCounter > 20) {
					tempCounter = 0;
					break;
				}
			}

			if (clickOtherGameIcon(1) == 1) {
				Sleep(3000);
				while (selectLoginMethod(1) == 0 && getIsEnded() == false) {
					Sleep(2000);
					tempCounter++;
					if (tempCounter > 20) {
						tempCounter = 0;
						break;
					}
				}

				//不能用UI判定登陆界面
				while (findZhanghaoDengluUI() == 0 && getIsEnded() == false) {
					Sleep(2000);
					tempCounter++;
					if (tempCounter > 20) {
						tempCounter = 0;
						break;
					}
				}
				Sleep(2000);
				loginForFeizhu();

				while (findZhanghaoDengluUI() == 1 && getIsEnded() == false) {
					Sleep(2000);
					PskCommonHelper::CommonMoveTo(this->myFire, 405, 350);
					PskCommonHelper::CommonLClick(this->myFire);
					Sleep(2000);

					tempCounter++;
					if (tempCounter > 20) {
						tempCounter = 0;
						break;
					}
				}

				while (skipPhoneNumBind(1) == 0 && getIsEnded() == false) {
					Sleep(2000);
					tempCounter++;
					if (tempCounter > 20) {
						tempCounter = 0;
						break;
					}
				}
				Sleep(2000);
				while (clickEnterGameBtn(0) == 0 && getIsEnded() == false) {
					Sleep(2000);
					tempCounter++;
					if (tempCounter > 30) {
						tempCounter = 0;
						break;
					}
				}
				if (clickServerBtn(1) == 1) {
					PskCommonHelper::CommonMoveTo(this->myFire, 195, 175);
					PskCommonHelper::CommonLClick(this->myFire);
					Sleep(1000);
					if (this->zone == 1) {
						PskCommonHelper::CommonMoveTo(this->myFire, 365, 155);
						PskCommonHelper::CommonLClick(this->myFire);
					}
					if (this->zone == 0) {
						PskCommonHelper::CommonMoveTo(this->myFire, 560, 155);
						PskCommonHelper::CommonLClick(this->myFire);
					}
				}

				while (clickEnterGameBtn(1) == 0 && getIsEnded() == false) {
					Sleep(2000);
					tempCounter++;
					if (tempCounter > 30) {
						tempCounter = 0;
						break;
					}
				}

				Sleep(2000);
				if (clickGonggaoCloseBtn() == 1) {
					clickEnterGameBtn(1);
				}

				Sleep(2000);
				while (clickKaishiBtn(1) == 0 && getIsEnded() == false) {
					Sleep(2000);
					tempCounter++;
					if (tempCounter > 10) {
						tempCounter = 0;
						break;
					}
				}

				while (clickJueseQuedingBtn(1) == 1 && getIsEnded() == false) {
					Sleep(2000);
					tempCounter++;
					if (tempCounter > 10) {
						tempCounter = 0;
						break;
					}
				}

				if (clickJueseQuedingBtn(1) == 1) {
					this->mainStepIndex = MAIN_STEPS::GENERAL_TASK;
					this->scriptIndex = this->scriptList.size();
					this->errorCounter = 22;
				}
			}
		}
	}
	

	return 0;
}

int MainScriptThread::RegisterSubScript() {
	MainSingleton* main = MainSingleton::getInstance();
	main->table->setItem(index - 1, 2, new QTableWidgetItem(QString::fromLocal8Bit("注册机")));

	int tempCounter = 0;
	if (this->getThreadAccount(this->accountIndex) == 0) {
		return 0;
	}
	

	
	while (clickOtherGameIcon(0) == 0 && getIsEnded() == false) {
		Sleep(2000);
		tempCounter++;
		if (tempCounter > 20) {
			tempCounter = 0;
			break;
		}
	}

	if (clickOtherGameIcon(1) == 1) {
		Sleep(3000);
		while (selectLoginMethod(1) == 0 && getIsEnded() == false) {
			Sleep(2000);
			tempCounter++;
			if (tempCounter > 5) {
				tempCounter = 0;
				break;
			}
		}

		//不能用UI判定登陆界面
		while (findZhanghaoDengluUI() == 0 && getIsEnded() == false) {
			Sleep(2000);
			tempCounter++;
			if (tempCounter > 5) {
				tempCounter = 0;
				break;
			}
		}

		while (clickZhuceBtn() == 0 == 0 && getIsEnded() == false) {
			Sleep(2000);
			tempCounter++;
			if (tempCounter > 5) {
				tempCounter = 0;
				break;
			}
		}

		loginForFeizhu();

		while (skipPhoneNumBind(0) == 0) {
			Sleep(2000);
			tempCounter++;
			if (tempCounter > 10) {
				tempCounter = 0;
				break;
			}
		}

		if (skipPhoneNumBind(1) == 1) {
			
			Sleep(2000);
			saveSingleAccuntSub(this->accountIndex);

			this->accountIndex += main->windowCounterBox->text().toInt();


			Sleep(2000);
		}

		
		loginOut();
	}
	else {
		if (skipPhoneNumBind(1) == 1) {
			Sleep(2000);
			loginOut();

			while (clickOtherGameIcon(0) == 0 && getIsEnded() == false) {
				Sleep(2000);
				tempCounter++;
				if (tempCounter > 10) {
					tempCounter = 0;
					break;
				}
			}

			if (clickOtherGameIcon(1) == 1) {
				Sleep(3000);
				while (selectLoginMethod(1) == 0 && getIsEnded() == false) {
					Sleep(2000);
					tempCounter++;
					if (tempCounter > 20) {
						tempCounter = 0;
						break;
					}
				}

				//不能用UI判定登陆界面
				while (findZhanghaoDengluUI() == 0 && getIsEnded() == false) {
					Sleep(2000);
					tempCounter++;
					if (tempCounter > 5) {
						tempCounter = 0;
						break;
					}
				}
				while (clickZhuceBtn() == 0 == 0 && getIsEnded() == false) {
					Sleep(2000);
					tempCounter++;
					if (tempCounter > 5) {
						tempCounter = 0;
						break;
					}
				}

				loginForFeizhu();

				while (skipPhoneNumBind(0) == 0) {
					Sleep(2000);
					tempCounter++;
					if (tempCounter > 10) {
						tempCounter = 0;
						break;
					}
				}

				if (skipPhoneNumBind(1) == 1) {
					
					Sleep(2000);
					saveSingleAccuntSub(this->accountIndex);

					this->accountIndex += main->windowCounterBox->text().toInt();


					Sleep(2000);
				}


				loginOut();
			}
		}
	}


	return 0;
}

int MainScriptThread::saveSingleAccuntSub(int index) {
	MainSingleton* theMain = MainSingleton::getInstance();
	QTableWidgetItem* item = theMain->accountTable->item(index - 1, 0);
	int id = 0;
	/*if (item != NULL) {
		id = item->text().toInt();
	}

	if (id == 0) {
		id = index;
	}*/
	id = theMain->getRegisterID();

	qDebug() << "id = " << id;

	item = theMain->accountTable->item(index - 1, 1);
	if (item == NULL) {
		return 0;
	}
	QString account = item->text();
	qDebug() << "account = " << account;

	item = theMain->accountTable->item(index - 1, 2);
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

void MainScriptThread::getConfig(QString config) {
	QJsonParseError jsonError;
	QByteArray byteArray = config.toLatin1();
	qDebug() << "config = " << config;

	QJsonDocument document = QJsonDocument::fromJson(byteArray, &jsonError);

	if (!document.isNull() && (jsonError.error == QJsonParseError::NoError)) {
		if (document.isObject()) {
			QJsonObject object = document.object();  // 转化为对象

			if (object.contains("folder")) {
				QJsonValue value = object.value("folder");
				if (value.isString()) {
					QString strName = value.toString();
					qDebug() << "daqu : " << strName;
					this->folder = strName;
				}
			}

			if (object.contains("isZhuxian")) {
				QJsonValue value = object.value("isZhuxian");
				if (value.isString()) {
					QString strName = value.toString();
					qDebug() << "isZhuxian : " << strName;
					if (value == "0") {
						isZhuxian = false;
					}
					else {
						isZhuxian = true;
					}
				}
			}

			//isOnlyJuling
			if (object.contains("isOnlyJuling")) {
				QJsonValue value = object.value("isOnlyJuling");
				if (value.isString()) {
					QString strName = value.toString();
					qDebug() << "isOnlyJuling : " << strName;
					if (value == "0") {
						isOnlyJuling = false;
					}
					else {
						isOnlyJuling = true;
					}
				}
			}
			//
			if (object.contains("IsBuyCheckBox")) {
				QJsonValue value = object.value("IsBuyCheckBox");
				if (value.isString()) {
					QString strName = value.toString();
					qDebug() << "IsBuyCheckBox : " << strName;
					if (value == "0") {
						IsBuyCheckBox = false;
					}
					else {
						IsBuyCheckBox = true;
					}
				}
			}

			if (object.contains("zone")) {
				QJsonValue value = object.value("zone");
				if (value.isString()) {
					QString strName = value.toString();
					qDebug() << "zone : " << strName;
					this->zone = strName.toInt();
				}
			}
			//
			if (object.contains("item_name_parameter")) {
				QJsonValue value = object.value("item_name_parameter");
				if (value.isString()) {
					QString strName = value.toString();
					qDebug() << "item_name_parameter : " << strName;
					this->item_name_parameter = strName.toInt();
				}
			}

			if (object.contains("item_ye_parameter")) {
				QJsonValue value = object.value("item_ye_parameter");
				if (value.isString()) {
					QString strName = value.toString();
					qDebug() << "item_ye_parameter : " << strName;
					this->item_ye_parameter = strName.toInt();
				}
			}
			//
			if (object.contains("item_num_parameter")) {
				QJsonValue value = object.value("item_num_parameter");
				if (value.isString()) {
					QString strName = value.toString();
					qDebug() << "item_num_parameter : " << strName;
					this->item_num_parameter = strName.toInt();
				}
			}

			if (object.contains("item_name_parameter")) {
				QJsonValue value = object.value("item_name_parameter");
				if (value.isString()) {
					QString strName = value.toString();
					qDebug() << "item_name_parameter : " << strName;
					this->item_name_parameter = strName.toInt();
				}
			}
			//isGen
			if (object.contains("isGen")) {
				QJsonValue value = object.value("isGen");
				if (value.isString()) {
					QString strName = value.toString();
					qDebug() << "isGen : " << strName;
					if (value == "0") {
						isGen = false;
					}
					else {
						isGen = true;
					}
				}
			}

			//time_limit
			if (object.contains("time_limit")) {
				QJsonValue value = object.value("time_limit");
				if (value.isString()) {
					QString strName = value.toString();
					qDebug() << "time_limit : " << strName;
					time_limit = strName.toInt();
				}
			}

			if (object.contains("main_time_limit")) {
				QJsonValue value = object.value("main_time_limit");
				if (value.isString()) {
					QString strName = value.toString();
					qDebug() << "main_time_limit : " << strName;
					main_time_limit = strName.toInt();
				}
			}

			if (object.contains("scriptArray")) {
				QJsonValue value = object.value("scriptArray");
				if (value.isArray()) {  // Version 的 value 是数组
					QJsonArray array = value.toArray();
					int nSize = array.size();
					for (int i = 0; i < nSize; ++i) {
						QJsonValue value = array.at(i);
						if (value.isString()) {
							QString scriptStr = QString::fromLocal8Bit(value.toString().toLocal8Bit().data());
							qDebug() << "scriptArray : " << scriptStr;
						}
					}
					this->scriptList = array;
				}
			}
		}


	}
}

int MainScriptThread::getThreadAccount(int accountIndex) {
	MainSingleton* main = MainSingleton::getInstance();
	QTableWidgetItem* accountItem = main->accountTable->item(accountIndex - 1, 1);
	QTableWidgetItem* passwordItem = main->accountTable->item(accountIndex - 1, 2);
	if (accountItem == NULL || passwordItem == NULL) {
		return 0;
	}

	this->account = accountItem->text();
	this->password = passwordItem->text();
	qDebug() << "account = " << account << ", passowrd = " << password;

	main->table->setItem(index - 1, 9, new QTableWidgetItem(this->account));

	return 1;
}

int MainScriptThread::forADBInput(int index, QString path, string text) {
	QString command = path + "//dnconsole.exe adb --index " + QString::number(index, 10) + " --command \"shell input text \""
		+ QString::fromStdString(text) + "\"";
	qDebug() << "Command = " << command;
	WinExec(command.toStdString().c_str(), SW_NORMAL);
	return 0;
}

int MainScriptThread::loginForFeizhu() {
	
	PskCommonHelper::CommonMoveTo(this->myFire, 325, 260);
	PskCommonHelper::CommonLClick(this->myFire);
	Sleep(2000);
	forADBInput(this->index, this->folder, this->account.toStdString());
	Sleep(2000);
	PskCommonHelper::CommonMoveTo(this->myFire, 325, 305);
	PskCommonHelper::CommonLClick(this->myFire);
	Sleep(2000);
	forADBInput(this->index, this->folder, this->password.toStdString());
	Sleep(2000);
	PskCommonHelper::CommonMoveTo(this->myFire, 405, 350);
	PskCommonHelper::CommonLClick(this->myFire);
	Sleep(2000);

	return 0;
}

int MainScriptThread::clickTaskBtn() {
	std::vector<std::string> result;
	long x, y, l;
	string str = PskCommonHelper::CommonFindPicE(this->myFire, 620, 100, 750, 180, "TaskBtn.bmp|TaskBtn2.bmp", "000000", 0.9, 0);
	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "TaskBtnX=" << result[1].c_str();
	qDebug() << "TaskBtnY=" << result[2].c_str();

	if (x != -1) {
		PskCommonHelper::CommonMoveTo(this->myFire, x + 5, y + 5);
		PskCommonHelper::CommonLClick(this->myFire);
		Sleep(2000);

		if (findRenwuWnd() == 0) {
			this->errorCounter++;
			if (this->errorCounter > 20) {
				this->mainStepIndex = MAIN_STEPS::GENERAL_TASK;
				this->scriptIndex = this->scriptList.size();
			}
		}
		/*else {
			if (clickCloseBtn() == 1) {
				Sleep(2000);
				if (clickCloseBtn() == 1) {
					this->errorCounter++;
					if (this->errorCounter > 20) {
						this->mainStepIndex = MAIN_STEPS::GENERAL_TASK;
						this->scriptIndex = this->scriptList.size();
					}
				}
				else {
					errorCounter = 0;

					return 1;
				}
			}
			
		}*/

		return 1;
	}
	else {
		PskCommonHelper::CommonMoveTo(this->myFire, 680, 135);
		PskCommonHelper::CommonLClick(this->myFire);
		Sleep(1000);
		if (findRenwuWnd() == 0) {
			this->errorCounter++;
			if (this->errorCounter > 20) {
				this->mainStepIndex = MAIN_STEPS::GENERAL_TASK;
				this->scriptIndex = this->scriptList.size();
			}
		}
		/*else {
			if (clickCloseBtn() == 1) {
				Sleep(2000);
				if (clickCloseBtn() == 1) {
					this->errorCounter++;
					if (this->errorCounter > 20) {
						this->mainStepIndex = MAIN_STEPS::GENERAL_TASK;
						this->scriptIndex = this->scriptList.size();
					}
				}
				else {
					errorCounter = 0;

					return 1;
				}
			}

		}*/
	}
	
	return 0;
}

int MainScriptThread::jiaruBangpai() {
	clickCloseBtn();

	std::vector<std::string> result;
	long x, y, l;
	string str = PskCommonHelper::CommonFindPicE(this->myFire, 620, 400, 750, 500, "BangpaiBtn.bmp", "000000", 0.9, 0);
	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "BangpaiBtnX=" << result[1].c_str();
	qDebug() << "BangpaiBtnY=" << result[2].c_str();

	if (x != -1) {
		PskCommonHelper::CommonMoveTo(this->myFire, 665, 460);
		PskCommonHelper::CommonLClick(this->myFire);
		Sleep(2000);
		if (clickShenqingBtn() == 0) {
			isBanghui = true;
		}
		Sleep(1000);
		clickCloseBtn();
		return 1;
	}
	return 0;
}

int MainScriptThread::clickShenqingBtn() {
	std::vector<std::string> result;
	long x, y, l;
	string str = PskCommonHelper::CommonFindPicE(this->myFire, 500, 400, 700, 500, "YijianShenqingBtn.bmp", "000000", 0.9, 0);
	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "YijianShenqingBtnX=" << result[1].c_str();
	qDebug() << "YijianShenqingBtnY=" << result[2].c_str();

	if (x != -1) {
		PskCommonHelper::CommonMoveTo(this->myFire, x + 5, y + 2);
		PskCommonHelper::CommonLClick(this->myFire);
		Sleep(1000);

		return 1;
	}
	return 0;
}

int MainScriptThread::clickZhidaoBtn() {
	std::vector<std::string> result;
	long x, y, l;
	string str = PskCommonHelper::CommonFindPicE(this->myFire, 300, 300, 420, 400, "ZhidaoBtn.bmp|ZhidaoBtn2.bmp", "000000", 0.9, 0);
	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "ZhidaoBtnX=" << result[1].c_str();
	qDebug() << "ZhidaoBtnY=" << result[2].c_str();

	if (x != -1) {
		PskCommonHelper::CommonMoveTo(this->myFire, x + 5, y + 5);
		PskCommonHelper::CommonLClick(this->myFire);
		Sleep(1000);

		return 1;
	}
	return 0;
}

int MainScriptThread::getCurrentLevel() {
	if (this->findTaskBtn() == 0) {
		this->clickCloseBtn();
	}
	
	PskCommonHelper::CommonMoveTo(this->myFire, 770, 80);
	PskCommonHelper::CommonLClick(this->myFire);
	Sleep(2000);
	getCurrentLevelSubScript();

	

	if (this->currentLevel > 15) {
		richangBuchong();
	}
	
	return 0;
}

int MainScriptThread::updateSkills() {
	if (this->isSkillUpdated == true || this->currentLevel < 25 || this->IsBuyCheckBox) {

		return 0;
	}

	if (this->findTaskBtn() == 0) {
		this->clickCloseBtn();
	}

	PskCommonHelper::CommonMoveTo(this->myFire, 770, 80);
	PskCommonHelper::CommonLClick(this->myFire);
	Sleep(2000);
	PskCommonHelper::CommonMoveTo(this->myFire, 700, 355);
	PskCommonHelper::CommonLClick(this->myFire);
	Sleep(2000);

	if (this->clickShengji10Btn(0) == 1) {
		PskCommonHelper::CommonMoveTo(this->myFire, 185, 120);
		PskCommonHelper::CommonLClick(this->myFire);
		Sleep(1000);
		this->clickShengji10Btn(1);
		Sleep(1500);
		PskCommonHelper::CommonMoveTo(this->myFire, 290, 120);
		PskCommonHelper::CommonLClick(this->myFire);
		Sleep(1000);
		this->clickShengji10Btn(1);
		Sleep(1500);
		PskCommonHelper::CommonMoveTo(this->myFire, 395, 120);
		PskCommonHelper::CommonLClick(this->myFire);
		Sleep(1000);
		this->clickShengji10Btn(1);
		Sleep(1500);
		PskCommonHelper::CommonMoveTo(this->myFire, 505, 120);
		PskCommonHelper::CommonLClick(this->myFire);
		Sleep(1000);
		this->clickShengji10Btn(1);
		Sleep(1500);

		this->isSkillUpdated = true;
	}

	return 0;
}


int MainScriptThread::getCurrentLevelSubScript()
{
	PskCommonHelper::CommonSetDict(this->myFire, 0, "dwb_lvl.txt");

	string leverString = PskCommonHelper::CommonOcr(this->myFire, 350, 110, 400, 150, "12ce03-101C04|10cc02-0F1E02|12c401-112601", 0.8);

	qDebug() << "getCurrentLevel=" << leverString.c_str();
	MainSingleton* theMain = MainSingleton::getInstance();

	long level = atol(leverString.c_str());

	if (level > currentLevel && level < 200) {
		currentLevel = level;
		QTableWidget* table = theMain->table;
		table->setItem(index - 1, 8, new QTableWidgetItem(QString::fromLocal8Bit(leverString.c_str())));
	}

	return currentLevel;
}

int MainScriptThread::chickBaoguoBtn() {
	std::vector<std::string> result;
	long x, y, l;
	string str = PskCommonHelper::CommonFindPicE(this->myFire, 720, 320, 810, 450, "BaoguoBtn.bmp", "000000", 0.9, 0);
	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "BaoguoBtnX=" << result[1].c_str();
	qDebug() << "BaoguoBtnY=" << result[2].c_str();

	if (x != -1) {
		PskCommonHelper::CommonMoveTo(this->myFire, x + 5, y + 5);
		PskCommonHelper::CommonLClick(this->myFire);
		Sleep(1000);

		return 1;
	}
	return 0;
}

int MainScriptThread::findBaoguoWnd() {
	std::vector<std::string> result;
	long x, y, l;
	string str = PskCommonHelper::CommonFindPicE(this->myFire, 200, 20, 300, 120, "BaoguoWnd.bmp", "000000", 0.9, 0);
	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "BaoguoWndX=" << result[1].c_str();
	qDebug() << "BaoguoWndY=" << result[2].c_str();

	if (x != -1) {
		
		Sleep(1000);

		return 1;
	}
	return 0;
}

int MainScriptThread::getCurrentMoney() {
	if (this->IsBuyCheckBox) {
		return 0;
	}

	int ret = 0;
	if (this->currentMoney == 0) {
		if (chickBaoguoBtn() == 1) {
			Sleep(1000);
			ret = 1;
		}
		else {
			PskCommonHelper::CommonMoveTo(this->myFire, 770, 400);
			PskCommonHelper::CommonLClick(this->myFire);
			ret = 1;
		}

	}

	if (ret == 1) {
		Sleep(1000);
		if (findBaoguoWnd() == 1) {
			getCurrentMoneySubScript();
		}
	}

	return 0;
}



int MainScriptThread::getCurrentMoneySubScript()
{
	PskCommonHelper::CommonSetDict(this->myFire, 0, "dwb_money.txt");

	string moneyStr = PskCommonHelper::CommonOcr(this->myFire, 180, 430, 250, 450, "cdaa85-242827|e2c29c-1B1E1E", 0.8);

	qDebug() << "getCurrentMoneySubScript=" << moneyStr.c_str();
	MainSingleton* theMain = MainSingleton::getInstance();

	this->currentMoney = atol(moneyStr.c_str());

	if (this->currentMoney < 100000) {
		moneyStr = currentMoney;
		QTableWidget* table = theMain->table;
		table->setItem(index - 1, 4, new QTableWidgetItem(QString::number(currentMoney)));
		CommonUtil::upateDWBGold(index, this->accountIndex, currentMoney);
	}
	

	return currentLevel;
}

int MainScriptThread::findTaskBtn() {
	std::vector<std::string> result;
	long x, y, l;
	string str = PskCommonHelper::CommonFindPicE(this->myFire, 620, 100, 750, 180, "TaskBtn.bmp", "000000", 0.9, 0);
	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "TaskBtnX=" << result[1].c_str();
	qDebug() << "TaskBtnY=" << result[2].c_str();

	if (x != -1) {
		
		Sleep(1000);

		return 1;
	}
	return 0;
}

int MainScriptThread::clickShengji10Btn(int flag) {
	std::vector<std::string> result;
	long x, y, l;
	string str = PskCommonHelper::CommonFindPicE(this->myFire, 550, 400, 750, 500, "UpdateSkillBtn.bmp", "000000", 0.9, 0);
	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "UpdateSkillBtnX=" << result[1].c_str();
	qDebug() << "UpdateSkillBtnY=" << result[2].c_str();

	if (x != -1) {
		if (flag == 1) {
			PskCommonHelper::CommonMoveTo(this->myFire, x + 5, y + 5);
			PskCommonHelper::CommonLClick(this->myFire);
		}
		Sleep(1000);

		return 1;
	}
	return 0;
}

int MainScriptThread::clickChuanshangBtn() {
	std::vector<std::string> result;
	long x, y, l;
	string str = PskCommonHelper::CommonFindPicE(this->myFire, 650, 350, 750, 450, "ChuanshangBtn.bmp", "000000", 0.9, 0);
	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "ChuanshangBtnX=" << result[1].c_str();
	qDebug() << "ChuanshangBtnY=" << result[2].c_str();

	if (x != -1) {
		PskCommonHelper::CommonMoveTo(this->myFire, x + 5, y + 5);
		PskCommonHelper::CommonLClick(this->myFire);
		Sleep(1000);

		return 1;
	}
	return 0;
}

int MainScriptThread::clickSubCloseBtn(bool flag) {
	std::vector<std::string> result;
	long x, y, l;
	string str = PskCommonHelper::CommonFindPicE(this->myFire, 700, 250, 780, 350, "SubCloseBtn.bmp|SubCloseBtn2.bmp", "000000", 0.9, 0);
	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "SubCloseBtnX=" << result[1].c_str();
	qDebug() << "SubCloseBtnY=" << result[2].c_str();

	if (x != -1) {
		if (flag) {
			PskCommonHelper::CommonMoveTo(this->myFire, x + 2, y + 2);
			PskCommonHelper::CommonLClick(this->myFire);
		}
		else {
			PskCommonHelper::CommonMoveTo(this->myFire, 695, 415);
			PskCommonHelper::CommonLClick(this->myFire);
		}
		
		Sleep(1000);

		return 1;
	}
	return 0;
}

int MainScriptThread::clickShiyongBtn() {
	std::vector<std::string> result;
	long x, y, l;
	string str = PskCommonHelper::CommonFindPicE(this->myFire, 620, 350, 750, 450, "ShiyongBtn.bmp", "000000", 0.9, 0);
	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "ShiyongBtnX=" << result[1].c_str();
	qDebug() << "ShiyongBtnY=" << result[2].c_str();

	if (x != -1) {
		PskCommonHelper::CommonMoveTo(this->myFire, x + 5, y + 5);
		PskCommonHelper::CommonLClick(this->myFire);
		Sleep(1000);

		return 1;
	}
	return 0;
}

int MainScriptThread::clickDuihuaIcon() {
	std::vector<std::string> result;
	long x, y, l;
	string str = PskCommonHelper::CommonFindPicE(this->myFire, 310, 330, 420, 420, "DuihuaIcon.bmp", "000000", 0.9, 0);
	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "DuihuaIconX=" << result[1].c_str();
	qDebug() << "DuihuaIconY=" << result[2].c_str();

	if (x != -1) {
		PskCommonHelper::CommonMoveTo(this->myFire, x + 5, y + 5);
		PskCommonHelper::CommonLClick(this->myFire);
		Sleep(1000);

		return 1;
	}
	return 0;
}

int MainScriptThread::clickCenterQuedingBtn() {
	std::vector<std::string> result;
	long x, y, l;
	string str = PskCommonHelper::CommonFindPicE(this->myFire, 420, 200, 520, 300, "CenterQuedingBtn.bmp|CenterQuedingBtn2.bmp", "000000", 0.9, 0);
	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "CenterQuedingBtnX=" << result[1].c_str();
	qDebug() << "CenterQuedingBtnY=" << result[2].c_str();

	if (x != -1) {
		PskCommonHelper::CommonMoveTo(this->myFire, x + 5, y + 2);
		PskCommonHelper::CommonLClick(this->myFire);
		Sleep(1000);

		return 1;
	}
	return 0;
}


int MainScriptThread::clickFangzhiBtn() {
	std::vector<std::string> result;
	long x, y, l;
	string str = PskCommonHelper::CommonFindPicE(this->myFire, 650, 350, 750, 450, "FangzhiBtn.bmp", "000000", 0.9, 0);
	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "FangzhiBtnX=" << result[1].c_str();
	qDebug() << "FangzhiBtnY=" << result[2].c_str();

	if (x != -1) {
		PskCommonHelper::CommonMoveTo(this->myFire, x + 5, y + 5);
		PskCommonHelper::CommonLClick(this->myFire);
		Sleep(1000);

		return 1;
	}
	return 0;
}

int MainScriptThread::clickGuanruBtn() {
	std::vector<std::string> result;
	long x, y, l;
	string str = PskCommonHelper::CommonFindPicE(this->myFire, 650, 350, 750, 450, "GuanruBtn.bmp", "000000", 0.9, 0);
	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "GuanruBtnX=" << result[1].c_str();
	qDebug() << "GuanruBtnY=" << result[2].c_str();

	if (x != -1) {
		PskCommonHelper::CommonMoveTo(this->myFire, x + 5, y + 5);
		PskCommonHelper::CommonLClick(this->myFire);
		Sleep(1000);

		return 1;
	}
	return 0;
}

int MainScriptThread::clickSkipBtn() {
	std::vector<std::string> result;
	long x, y, l;
	string str = PskCommonHelper::CommonFindPicE(this->myFire, 650, 10, 800, 180, "SkipBtn.bmp", "000000", 0.9, 0);
	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "SkipBtnX=" << result[1].c_str();
	qDebug() << "SkipBtnY=" << result[2].c_str();

	if (x != -1) {
		PskCommonHelper::CommonMoveTo(this->myFire, x + 5, y + 5);
		PskCommonHelper::CommonLClick(this->myFire);
		Sleep(1000);

		return 1;
	}
	return 0;
}

int MainScriptThread::clickGoumaiBtn() {
	std::vector<std::string> result;
	long x, y, l;
	string str = PskCommonHelper::CommonFindPicE(this->myFire, 520, 400, 625, 460, "GoumaiBtn.bmp", "000000", 0.9, 0);
	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "GoumaiBtnX=" << result[1].c_str();
	qDebug() << "GoumaiBtnY=" << result[2].c_str();

	if (x != -1) {
		PskCommonHelper::CommonMoveTo(this->myFire, x + 5, y + 5);
		PskCommonHelper::CommonLClick(this->myFire);
		Sleep(1000);

		return 1;
	}
	return 0;
}

int MainScriptThread::findShuxingJiadian() {
	std::vector<std::string> result;
	long x, y, l;
	string str = PskCommonHelper::CommonFindPicE(this->myFire, 320, 100, 450, 200, "Shuxingjiadian.bmp", "000000", 0.9, 0);
	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "ShuxingjiadianX=" << result[1].c_str();
	qDebug() << "ShuxingjiadianY=" << result[2].c_str();

	if (x != -1) {
		/*PskCommonHelper::CommonMoveTo(this->myFire, x + 5, y + 5);
		PskCommonHelper::CommonLClick(this->myFire);*/
		Sleep(1000);

		return 1;
	}
	return 0;
}

int MainScriptThread::clickCloseBtn() {
	std::vector<std::string> result;
	long x, y, l;
	string str = PskCommonHelper::CommonFindPicE(this->myFire, 620, 30, 750, 180, "CloseBtn.bmp", "000000", 0.9, 0);
	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "CloseBtnX=" << result[1].c_str();
	qDebug() << "CloseBtnY=" << result[2].c_str();

	if (x != -1) {
		PskCommonHelper::CommonMoveTo(this->myFire, x + 5, y + 5);
		PskCommonHelper::CommonLClick(this->myFire);
		Sleep(1000);

		return 1;
	}
	return 0;
}

//JueseQuedingBtn.bmp

int MainScriptThread::clickJueseQuedingBtn(int flag) {
	std::vector<std::string> result;
	long x, y, l;
	string str = PskCommonHelper::CommonFindPicE(this->myFire, 320, 250, 480, 360, "JueseQuedingBtn.bmp", "000000", 0.9, 0);
	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "JueseQuedingBtnX=" << result[1].c_str();
	qDebug() << "JueseQuedingBtnY=" << result[2].c_str();

	if (x != -1) {

		if (flag == 1) {
			PskCommonHelper::CommonMoveTo(this->myFire, 530, 245);
			PskCommonHelper::CommonLClick(this->myFire);
			Sleep(1000);
			PskCommonHelper::CommonMoveTo(this->myFire, 405, 310);
			PskCommonHelper::CommonLClick(this->myFire);
			Sleep(1000);
			PskCommonHelper::CommonMoveTo(this->myFire, 720, 435);
			PskCommonHelper::CommonLClick(this->myFire);
			Sleep(1000);
		}
		Sleep(1000);

		return 1;
	}
	return 0;
}

int MainScriptThread::clickKaishiBtn(int flag) {
	std::vector<std::string> result;
	long x, y, l;
	string str = PskCommonHelper::CommonFindPicE(this->myFire, 670, 400, 780, 500, "KaishiBtn.bmp|KaishiBtn2.bmp", "000000", 0.9, 0);
	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "KaishiBtnX=" << result[1].c_str();
	qDebug() << "KaishiBtnY=" << result[2].c_str();

	if (x != -1) {
		

		//int character = CommonUtil::generateRandomNumberEx(5);
		//switch (character)
		//{
		//case 0: {
		//	PskCommonHelper::CommonMoveTo(this->myFire, 61, 145);
		//	PskCommonHelper::CommonLClick(this->myFire);
		//}break;
		//case 1: {
		//	PskCommonHelper::CommonMoveTo(this->myFire, 75, 195);
		//	PskCommonHelper::CommonLClick(this->myFire);
		//}break;
		//case 2: {
		//	/*PskCommonHelper::CommonMoveTo(this->myFire, 75, 195);
		//	PskCommonHelper::CommonLClick(this->myFire);*/
		//}break;
		//case 3: {
		//	PskCommonHelper::CommonMoveTo(this->myFire, 75, 315);
		//	PskCommonHelper::CommonLClick(this->myFire);
		//}break;
		//case 4: {
		//	PskCommonHelper::CommonMoveTo(this->myFire, 65, 370);
		//	PskCommonHelper::CommonLClick(this->myFire);
		//}break;
		//default:
		//	break;
		//}

		Sleep(5000);
		if (flag == 1) {
			PskCommonHelper::CommonMoveTo(this->myFire, x + 5, y + 5);
			PskCommonHelper::CommonLClick(this->myFire);
			Sleep(1000);
			PskCommonHelper::CommonMoveTo(this->myFire, 530, 245);
			PskCommonHelper::CommonLClick(this->myFire);
			Sleep(1000);
			PskCommonHelper::CommonMoveTo(this->myFire, 405, 310);
			PskCommonHelper::CommonLClick(this->myFire);
			Sleep(1000);
			PskCommonHelper::CommonMoveTo(this->myFire, x + 5, y + 5);
			PskCommonHelper::CommonLClick(this->myFire);
			Sleep(1000);
		}
		Sleep(1000);

		return 1;
	}
	return 0;
}

int MainScriptThread::findHuodongWnd() {
	std::vector<std::string> result;
	long x, y, l;
	string str = PskCommonHelper::CommonFindPicE(this->myFire, 220, 30, 300, 130, "HuodongWnd.bmp", "000000", 0.9, 0);
	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "HuodongWndX=" << result[1].c_str();
	qDebug() << "HuodongWndY=" << result[2].c_str();

	if (x != -1) {
		/*PskCommonHelper::CommonMoveTo(this->myFire, x + 5, y + 5);
		PskCommonHelper::CommonLClick(this->myFire);*/
		Sleep(1000);

		return 1;
	}
	return 0;
}

int MainScriptThread::findFuliWnd() {
	std::vector<std::string> result;
	long x, y, l;
	string str = PskCommonHelper::CommonFindPicE(this->myFire, 220, 30, 300, 130, "RenwuWnd.bmp", "000000", 0.9, 0);
	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "RenwuWndX=" << result[1].c_str();
	qDebug() << "RenwuWndY=" << result[2].c_str();

	if (x != -1) {
		/*PskCommonHelper::CommonMoveTo(this->myFire, x + 5, y + 5);
		PskCommonHelper::CommonLClick(this->myFire);*/
		Sleep(1000);

		return 1;
	}
	return 0;
}

int MainScriptThread::findRenwuWnd() {
	std::vector<std::string> result;
	long x, y, l;
	string str = PskCommonHelper::CommonFindPicE(this->myFire, 220, 30, 300, 130, "FuliWnd.bmp", "000000", 0.9, 0);
	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "FuliWndX=" << result[1].c_str();
	qDebug() << "FuliWndY=" << result[2].c_str();

	if (x != -1) {
		Sleep(1000);

		return 1;
	}
	return 0;
}

int MainScriptThread::clickDengjilibaoBtn() {
	std::vector<std::string> result;
	long x, y, l;
	string str = PskCommonHelper::CommonFindPicE(this->myFire, 550, 160, 650, 250, "LingDengjiBtn.bmp", "000000", 0.9, 0);
	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "LingDengjiBtnX=" << result[1].c_str();
	qDebug() << "LingDengjiBtnY=" << result[2].c_str();

	if (x != -1) {
		PskCommonHelper::CommonMoveTo(this->myFire, x + 5, y + 5);
		PskCommonHelper::CommonLClick(this->myFire);
		Sleep(1000);

		return 1;
	}
	return 0;
}

int MainScriptThread::clickFuliBtn() {
	std::vector<std::string> result;
	long x, y, l;
	string str = PskCommonHelper::CommonFindPicE(this->myFire, 250, 60, 450, 200, "FuliBtn", "000000", 0.9, 0);
	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "FuliBtnX=" << result[1].c_str();
	qDebug() << "FuliBtnY=" << result[2].c_str();

	if (x != -1) {
		PskCommonHelper::CommonMoveTo(this->myFire, x + 5, y + 5);
		PskCommonHelper::CommonLClick(this->myFire);
		Sleep(1000);

		return 1;
	}

	str = PskCommonHelper::CommonFindPicE(this->myFire, 620, 100, 750, 180, "TaskBtn.bmp|TaskBtn2.bmp", "000000", 0.9, 0);
	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "TaskBtnX=" << result[1].c_str();
	qDebug() << "TaskBtnY=" << result[2].c_str();

	if (x != -1) {
		PskCommonHelper::CommonMoveTo(this->myFire, 300, 120);
		PskCommonHelper::CommonLClick(this->myFire);
		Sleep(1000);

		return 1;
	}
	return 0;
}

int MainScriptThread::getMyFuli() {
	if (isFuliGot == true || this->currentLevel < 19) {
		return 0;
	}

	if (clickFuliBtn() == 0) {
		clickCloseBtn();
		return 0;
	}

	if (this->findFuliWnd() == 1) {
		//签到
		PskCommonHelper::CommonMoveTo(this->myFire, 225, 140);
		PskCommonHelper::CommonLClick(this->myFire);
		Sleep(1000);
		qiandaoSubScript();
		//在线奖励
		Sleep(1000);
		PskCommonHelper::CommonMoveTo(this->myFire, 225, 180);
		PskCommonHelper::CommonLClick(this->myFire);
		Sleep(1000);
		PskCommonHelper::CommonMoveTo(this->myFire, 490, 430);
		PskCommonHelper::CommonLClick(this->myFire);
		Sleep(1000);
		//等级礼包
		PskCommonHelper::CommonMoveTo(this->myFire, 225, 220);
		PskCommonHelper::CommonLClick(this->myFire);
		Sleep(1000);
		clickDengjilibaoBtn();
		//七日登陆
		PskCommonHelper::CommonMoveTo(this->myFire, 225, 265);
		PskCommonHelper::CommonLClick(this->myFire);
		Sleep(1000);
		PskCommonHelper::CommonMoveTo(this->myFire, 600, 415);
		PskCommonHelper::CommonLClick(this->myFire);
		Sleep(1000);

		this->isFuliGot = true;
	}

	return 0;
}

int MainScriptThread::qiandaoSubScript() {
	int pX = 355, pY = 168;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 5; j++) {
			PskCommonHelper::CommonMoveTo(this->myFire, pX + j * 70, pY  + i * 70);
			PskCommonHelper::CommonLClick(this->myFire);
			Sleep(300);
		}
	}

	return 1;
}


int MainScriptThread::timerChecker()
{
	DWORD onlineTime = timeGetTime() - this->startTime;

	long timeMin = onlineTime / 1000 / 60;

	MainSingleton* theMain = MainSingleton::getInstance();
	QTableWidget* table = theMain->table;

	table->setItem(index - 1, 7, new QTableWidgetItem(QString::number(timeMin)));
	//table->setItem(index - 1, 1, new QTableWidgetItem(QString::fromLocal8Bit("000000")));

	if (this->currentLevel > 20 && timeMin >= this->main_time_limit) {
		if (this->mainStepIndex == MAIN_STEPS::MAIN_TASK) {
			this->mainStepIndex = MAIN_STEPS::GENERAL_TASK;
		}
	}

	if (timeMin > time_limit) {
		if (this->mainStepIndex == MAIN_STEPS::GENERAL_TASK) {
			this->scriptIndex = this->scriptList.size();
		}

	}
	return 0;
}


int MainScriptThread::clickJulingBtn() {
	std::vector<std::string> result;
	long x, y, l;
	string str = PskCommonHelper::CommonFindPicE(this->myFire, 300, 30, 400, 130, "JulingBtn.bmp|JulingBtn2.bmp", "000000", 0.9, 0);
	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "JulingBtnX=" << result[1].c_str();
	qDebug() << "JulingBtnY=" << result[2].c_str();

	if (x != -1) {
		PskCommonHelper::CommonMoveTo(this->myFire, x + 5, y + 5);
		PskCommonHelper::CommonLClick(this->myFire);
		Sleep(1000);

		return 1;
	}

	str = PskCommonHelper::CommonFindPicE(this->myFire, 620, 100, 750, 180, "TaskBtn.bmp|TaskBtn2.bmp", "000000", 0.9, 0);
	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "TaskBtnX=" << result[1].c_str();
	qDebug() << "TaskBtnY=" << result[2].c_str();

	if (x != -1) {
		PskCommonHelper::CommonMoveTo(this->myFire, 355, 70);
		PskCommonHelper::CommonLClick(this->myFire);
		Sleep(1000);

		return 1;
	}
	return 0;
}

int MainScriptThread::shangchengGoumai() {
	MainSingleton* theMain = MainSingleton::getInstance();

	if (clickShangchengBtn(1) == 1) {
		Sleep(1000);
		PskCommonHelper::CommonMoveTo(this->myFire, 705, 215);
		PskCommonHelper::CommonLClick(this->myFire);
		Sleep(1000);
		if (findShanghuiWnd() == 1) {
			int gold = this->getSavedGold();

			/*PskCommonHelper::CommonMoveTo(this->myFire, 460, 125);
			PskCommonHelper::CommonLClick(this->myFire);
			Sleep(1000);

			PskCommonHelper::CommonMoveTo(this->myFire, 355, 180);
			PskCommonHelper::CommonLClick(this->myFire);
			Sleep(1000);

			QString text = QString::fromLocal8Bit("乌金枪");
			forADBInput(this->index, QString::fromStdString(theMain->path), text.toStdString());
			Sleep(1000);

			PskCommonHelper::CommonMoveTo(this->myFire, 545, 180);
			PskCommonHelper::CommonLClick(this->myFire);
			Sleep(1000);
			PskCommonHelper::CommonLClick(this->myFire);
			Sleep(1000);*/
			if (this->item_name_parameter < 9) {
				PskCommonHelper::CommonMoveTo(this->myFire, 205, 220);
				PskCommonHelper::CommonLClick(this->myFire);
				Sleep(1000);
			}


			switch (this->item_name_parameter)
			{
			case SHANGCHENG_ITEMS::QIANG: {
				PskCommonHelper::CommonMoveTo(this->myFire, 395, 210);
				PskCommonHelper::CommonLClick(this->myFire);
			} break;
			case SHANGCHENG_ITEMS::ZHANG: {
				PskCommonHelper::CommonMoveTo(this->myFire, 575, 210);
				PskCommonHelper::CommonLClick(this->myFire);
			} break;
			case SHANGCHENG_ITEMS::JIAN: {
				PskCommonHelper::CommonMoveTo(this->myFire, 375, 275);
				PskCommonHelper::CommonLClick(this->myFire);
			} break;
			case SHANGCHENG_ITEMS::SHAN: {
				PskCommonHelper::CommonMoveTo(this->myFire, 575, 275);
				PskCommonHelper::CommonLClick(this->myFire);
			} break;
			case SHANGCHENG_ITEMS::DAO: {
				PskCommonHelper::CommonMoveTo(this->myFire, 375, 350);
				PskCommonHelper::CommonLClick(this->myFire);
			} break;
			case SHANGCHENG_ITEMS::MAOZI: {
				PskCommonHelper::CommonMoveTo(this->myFire, 575, 350);
				PskCommonHelper::CommonLClick(this->myFire);
			} break;
			case SHANGCHENG_ITEMS::YIFU: {
				PskCommonHelper::CommonMoveTo(this->myFire, 375, 400);
				PskCommonHelper::CommonLClick(this->myFire);
			} break;
			case SHANGCHENG_ITEMS::YAODAI: {
				PskCommonHelper::CommonMoveTo(this->myFire, 575, 400);
				PskCommonHelper::CommonLClick(this->myFire);
			} break;
			default:
				break;
			}
			Sleep(1000);

			for (int i = 0; i < this->item_ye_parameter - 1; i++) {
				PskCommonHelper::CommonMoveTo(this->myFire, 410, 440);
				PskCommonHelper::CommonLClick(this->myFire);
				Sleep(800);
			}

			int theIndex = item_num_parameter - 1;
			int xNum = theIndex % 2;
			int yNum = theIndex % 2;
			int pX = 395, pY = 205;

			while (this->findDuihuanJinziWnd() == 0 && getIsEnded() == false) {
				PskCommonHelper::CommonMoveTo(this->myFire, pX + xNum * 190, pY + yNum * 60);
				PskCommonHelper::CommonLClick(this->myFire);
				Sleep(1000);
				PskCommonHelper::CommonMoveTo(this->myFire, 625, 440);
				PskCommonHelper::CommonLClick(this->myFire);
				Sleep(1000);
			}
			
			this->scriptIndex++;
		}
	}

	return 0;
}

int MainScriptThread::getSavedGold() {
	MainSingleton* theMain = MainSingleton::getInstance();
	QTableWidgetItem* item = theMain->accountTable->item(this->accountIndex - 1, 3);
	if (item == NULL) {
		return 0;
	}

	int num = item->text().toInt();

	return 0;
}

int MainScriptThread::findShanghuiWnd() {
	std::vector<std::string> result;
	long x, y, l;
	string str = PskCommonHelper::CommonFindPicE(this->myFire, 200, 30, 315, 120, "ShanghuiWnd.bmp", "000000", 0.9, 0);
	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "ShanghuiWndX=" << result[1].c_str();
	qDebug() << "ShanghuiWndY=" << result[2].c_str();

	if (x != -1) {

		Sleep(1000);

		return 1;
	}

	return 0;
}

int MainScriptThread::findDuihuanJinziWnd() {
	std::vector<std::string> result;
	long x, y, l;
	string str = PskCommonHelper::CommonFindPicE(this->myFire, 320, 80, 450, 180, "DuihuanJinziWnd.bmp", "000000", 0.9, 0);
	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "DuihuanJinziWndX=" << result[1].c_str();
	qDebug() << "DuihuanJinziWndY=" << result[2].c_str();

	if (x != -1) {

		Sleep(1000);

		return 1;
	}

	return 0;
}

int MainScriptThread::clickShangchengBtn(int flag) {
	std::vector<std::string> result;
	long x, y, l;
	string str = PskCommonHelper::CommonFindPicE(this->myFire, 0, 100, 80, 220, "ShangchengBtn.bmp", "000000", 0.9, 0);
	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "ShangchengBtnX=" << result[1].c_str();
	qDebug() << "ShangchengBtnY=" << result[2].c_str();

	if (x != -1) {
		if (flag == 1) {
			PskCommonHelper::CommonMoveTo(this->myFire, x + 5, y + 5);
			PskCommonHelper::CommonLClick(this->myFire);
		}
	
		Sleep(1000);

		return 1;
	}

	str = PskCommonHelper::CommonFindPicE(this->myFire, 620, 100, 750, 180, "TaskBtn.bmp|TaskBtn2.bmp", "000000", 0.9, 0);
	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "TaskBtnX=" << result[1].c_str();
	qDebug() << "TaskBtnY=" << result[2].c_str();

	if (x != -1) {
		if (flag == 1) {
			PskCommonHelper::CommonMoveTo(this->myFire, 30, 150);
			PskCommonHelper::CommonLClick(this->myFire);
		}
		
		Sleep(1000);

		return 1;
	}
	return 0;
}

int MainScriptThread::forJuling() {
	getCurrentMoney();

	if (this->currentLevel < 25 || this->IsBuyCheckBox) {
		return 0;
	}

	int ret = 0;
	if (this->lastJulingTime == 0) {
		ret = 1;
	}
	else {
		long timePassed = (timeGetTime() - lastJulingTime) / 1000 / 60;
		if (timePassed > 60) {
			ret = 1;
		}
	}

	if (ret == 0) {
		return 0;
	}

	if (this->clickJulingBtn() == 1) {
		Sleep(1000);
		if (findJulingWnd() == 1) {

			/*if (findJiaogaoJilv() == 1) {
				PskCommonHelper::CommonMoveTo(this->myFire, 200, 180);
				PskCommonHelper::CommonLClick(this->myFire);
				Sleep(1000);
				PskCommonHelper::CommonMoveTo(this->myFire, 620, 435);
				PskCommonHelper::CommonLClick(this->myFire);
				Sleep(1000);
				lastJulingTime = timeGetTime();
				if (this->isOnlyJuling) {
					this->mainStepIndex = MAIN_STEPS::GENERAL_TASK;
					this->scriptIndex = this->scriptList.size();
					return 0;
				}
			}*/


			if (findJulingLingjiangBtn() == 0) {
				PskCommonHelper::CommonMoveTo(this->myFire, 200, 180);
				PskCommonHelper::CommonLClick(this->myFire);
				Sleep(1000);
				PskCommonHelper::CommonMoveTo(this->myFire, 620, 435);
				PskCommonHelper::CommonLClick(this->myFire);
				Sleep(1000);
				lastJulingTime = timeGetTime();

				if (this->isOnlyJuling) {
					this->mainStepIndex = MAIN_STEPS::GENERAL_TASK;
					this->scriptIndex = this->scriptList.size();
					return 0;
				}
			}

			if (findJiaogaoJilv() == 1) {
				PskCommonHelper::CommonMoveTo(this->myFire, 200, 180);
				PskCommonHelper::CommonLClick(this->myFire);
				Sleep(1000);
				PskCommonHelper::CommonMoveTo(this->myFire, 620, 435);
				PskCommonHelper::CommonLClick(this->myFire);
				Sleep(1000);
				lastJulingTime = timeGetTime();

				if (this->isOnlyJuling) {
					this->mainStepIndex = MAIN_STEPS::GENERAL_TASK;
					this->scriptIndex = this->scriptList.size();
					Sleep(1000);
				}
			}
			else {
				if (this->isOnlyJuling) {
					this->mainStepIndex = MAIN_STEPS::GENERAL_TASK;
					this->scriptIndex = this->scriptList.size();
					Sleep(1000);
				}
			}

			if (clickKaishijulingBtn() == 1) {
				Sleep(1000);
				lastJulingTime = timeGetTime();

				if (this->isOnlyJuling) {
					this->mainStepIndex = MAIN_STEPS::GENERAL_TASK;
					this->scriptIndex = this->scriptList.size();
					return 0;
				}
			}
			
		}
	}
	else {
		clickCloseBtn();
		Sleep(1000);
		if (this->clickJulingBtn() == 1) {
			Sleep(1000);
			if (findJulingWnd() == 1) {


				if (findJulingLingjiangBtn() == 0) {
					PskCommonHelper::CommonMoveTo(this->myFire, 200, 180);
					PskCommonHelper::CommonLClick(this->myFire);
					Sleep(1000);
					PskCommonHelper::CommonMoveTo(this->myFire, 620, 435);
					PskCommonHelper::CommonLClick(this->myFire);
					Sleep(1000);
					lastJulingTime = timeGetTime();

					if (this->isOnlyJuling) {
						this->mainStepIndex = MAIN_STEPS::GENERAL_TASK;
						this->scriptIndex = this->scriptList.size();
						return 0;
					}
				}

				if (findJiaogaoJilv() == 1) {
					PskCommonHelper::CommonMoveTo(this->myFire, 200, 180);
					PskCommonHelper::CommonLClick(this->myFire);
					Sleep(1000);
					PskCommonHelper::CommonMoveTo(this->myFire, 620, 435);
					PskCommonHelper::CommonLClick(this->myFire);
					Sleep(1000);
					lastJulingTime = timeGetTime();

					if (this->isOnlyJuling) {
						this->mainStepIndex = MAIN_STEPS::GENERAL_TASK;
						this->scriptIndex = this->scriptList.size();
						Sleep(1000);
					}
				}
				else {
					if (this->isOnlyJuling) {
						this->mainStepIndex = MAIN_STEPS::GENERAL_TASK;
						this->scriptIndex = this->scriptList.size();
						Sleep(1000);
					}
				}

				if (clickKaishijulingBtn() == 1) {
					Sleep(1000);
					lastJulingTime = timeGetTime();

					if (this->isOnlyJuling) {
						this->mainStepIndex = MAIN_STEPS::GENERAL_TASK;
						this->scriptIndex = this->scriptList.size();
						return 0;
					}
				}
			}
		}
	}
	return 0;
}

int MainScriptThread::findJulingWnd() {
	std::vector<std::string> result;
	long x, y, l;
	string str = PskCommonHelper::CommonFindPicE(this->myFire, 195, 30, 350, 130, "JulingWnd.bmp", "000000", 0.9, 0);
	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "JulingWndX=" << result[1].c_str();
	qDebug() << "JulingWndY=" << result[2].c_str();

	if (x != -1) {
		/*PskCommonHelper::CommonMoveTo(this->myFire, x + 5, y + 5);
		PskCommonHelper::CommonLClick(this->myFire);*/
		Sleep(1000);

		return 1;
	}
	return 0;
}

int MainScriptThread::clickTongyiruduiBtn() {
	std::vector<std::string> result;
	long x, y, l;
	string str = PskCommonHelper::CommonFindPicE(this->myFire, 260, 200, 670, 400, "TongyiruduiBtn.bmp", "000000", 0.9, 0);
	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "TongyiruduiBtnX=" << result[1].c_str();
	qDebug() << "TongyiruduiBtnY=" << result[2].c_str();

	if (x != -1) {
		PskCommonHelper::CommonMoveTo(this->myFire, x + 5, y + 2);
		PskCommonHelper::CommonLClick(this->myFire);
		Sleep(1000);

		return 1;
	}
	return 0;
}

int MainScriptThread::clickZuduiBtn() {
	std::vector<std::string> result;
	long x, y, l;
	string str = PskCommonHelper::CommonFindPicE(this->myFire, 700, 100, 810, 180, "ZuduiBtn1.bmp|ZuduiBtn2.bmp|ZuduiBtn3.bmp", "000000", 0.9, 0);
	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "ZuduiBtn1X=" << result[1].c_str();
	qDebug() << "ZuduiBtn1Y=" << result[2].c_str();

	if (x != -1) {
		PskCommonHelper::CommonMoveTo(this->myFire, x + 5, y + 5);
		PskCommonHelper::CommonLClick(this->myFire);
		Sleep(1000);
		return 1;
	}
	return 0;
}

int MainScriptThread::clickRichangBtn() {
	std::vector<std::string> result;
	long x, y, l;
	string str = PskCommonHelper::CommonFindPicE(this->myFire, 130, 120, 260, 300, "RichangBtn.bmp", "000000", 0.9, 0);
	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "RichangBtnX=" << result[1].c_str();
	qDebug() << "RichangBtnY=" << result[2].c_str();

	if (x != -1) {
		PskCommonHelper::CommonMoveTo(this->myFire, x + 5, y + 5);
		PskCommonHelper::CommonLClick(this->myFire);
		Sleep(1000);
		return 1;
	}
	return 0;
}

int MainScriptThread::clickGuiduiBtn() {
	std::vector<std::string> result;
	long x, y, l;
	string str = PskCommonHelper::CommonFindPicE(this->myFire, 560, 40, 650, 480, "HuiguiDuiwuBtn.bmp", "000000", 0.9, 0);
	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "HuiguiDuiwuBtnX=" << result[1].c_str();
	qDebug() << "HuiguiDuiwuBtnY=" << result[2].c_str();

	if (x != -1) {
		PskCommonHelper::CommonMoveTo(this->myFire, x + 5, y + 2);
		PskCommonHelper::CommonLClick(this->myFire);
		Sleep(1000);
		PskCommonHelper::CommonLClick(this->myFire);
		Sleep(1000);
		return 1;
	}
	return 0;
}

int MainScriptThread::findTuiduiBtn(int flag) {
	std::vector<std::string> result;
	long x, y, l;
	string str = PskCommonHelper::CommonFindPicE(this->myFire, 130, 400, 220, 480, "TuiduiBtn.bmp|TuiduiBtn2.bmp", "000000", 0.9, 0);
	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "TuiduiBtnX=" << result[1].c_str();
	qDebug() << "TuiduiBtnY=" << result[2].c_str();

	if (x != -1) {
		if (flag == 1) {
			PskCommonHelper::CommonMoveTo(this->myFire, x + 5, y + 5);
			PskCommonHelper::CommonLClick(this->myFire);
			Sleep(1000);
			PskCommonHelper::CommonMoveTo(this->myFire, 465, 245);
			PskCommonHelper::CommonLClick(this->myFire);
			Sleep(1000);
		}
		
		Sleep(1000);

		return 1;
	}
	return 0;
}

int MainScriptThread::findJiesanBtn(int flag) {
	std::vector<std::string> result;
	long x, y, l;
	string str = PskCommonHelper::CommonFindPicE(this->myFire, 130, 400, 220, 480, "JiesanBtn.bmp", "000000", 0.9, 0);
	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "JiesanBtnX=" << result[1].c_str();
	qDebug() << "JiesanBtnY=" << result[2].c_str();

	if (x != -1) {
		if (flag == 1) {
			PskCommonHelper::CommonMoveTo(this->myFire, x + 5, y + 5);
			PskCommonHelper::CommonLClick(this->myFire);
			Sleep(1000);
			PskCommonHelper::CommonMoveTo(this->myFire, 465, 245);
			PskCommonHelper::CommonLClick(this->myFire);
			Sleep(1000);
		}

		Sleep(1000);

		return 1;
	}
	return 0;
}

int MainScriptThread::findShenqingliebiao(int flag) {
	std::vector<std::string> result;
	long x, y, l;
	string str = PskCommonHelper::CommonFindPicE(this->myFire, 450, 100, 530, 180, "Shenqingliebiao.bmp", "000000", 0.9, 0);
	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "ShenqingliebiaoX=" << result[1].c_str();
	qDebug() << "ShenqingliebiaoY=" << result[2].c_str();

	if (x != -1) {
		if (flag == 1) {
			PskCommonHelper::CommonMoveTo(this->myFire, x + 5, y + 5);
			PskCommonHelper::CommonLClick(this->myFire);
			Sleep(1000);
			PskCommonHelper::CommonMoveTo(this->myFire, x + 5, y + 5);
			PskCommonHelper::CommonLClick(this->myFire);
			Sleep(1000);
		}

		Sleep(1000);

		return 1;
	}
	return 0;
}

int MainScriptThread::clickKuaijiezuduiBtn(bool flag) {
	std::vector<std::string> result;
	long x, y, l;
	string str = PskCommonHelper::CommonFindPicE(this->myFire, 620, 275, 750, 325, "KuaijiezuduiBtn.bmp", "000000", 0.9, 0);
	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "KuaijiezuduiBtnX=" << result[1].c_str();
	qDebug() << "KuaijiezuduiBtnY=" << result[2].c_str();

	if (x != -1) {
		if (flag == 1) {
			PskCommonHelper::CommonMoveTo(this->myFire, x + 5, y + 2);
			PskCommonHelper::CommonLClick(this->myFire);
		}
		
		Sleep(1000);

		return 1;
	}
	return 0;
}

int MainScriptThread::clickZidongpipeiBtn() {
	std::vector<std::string> result;
	long x, y, l;
	string str = PskCommonHelper::CommonFindPicE(this->myFire, 550, 400, 650, 460, "ZidongpipeiBtn.bmp", "000000", 0.9, 0);
	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "ZidongpipeiBtnX=" << result[1].c_str();
	qDebug() << "ZidongpipeiBtnY=" << result[2].c_str();

	if (x != -1) {
		PskCommonHelper::CommonMoveTo(this->myFire, x + 5, y + 2);
		PskCommonHelper::CommonLClick(this->myFire);
		Sleep(1000);

		return 1;
	}
	return 0;
}

int MainScriptThread::clickHuodongBtn() {
	std::vector<std::string> result;
	long x, y, l;
	string str = PskCommonHelper::CommonFindPicE(this->myFire, 200, 30, 300, 120, "HuodongBtn.bmp|HuodongBtn2.bmp|HuodongBtn3.bmp|HuodongBtn4.bmp", "000000", 0.9, 0);
	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "HuodongBtnX=" << result[1].c_str();
	qDebug() << "HuodongBtnY=" << result[2].c_str();

	if (x != -1) {
		PskCommonHelper::CommonMoveTo(this->myFire, x + 5, y + 5);
		PskCommonHelper::CommonLClick(this->myFire);
		Sleep(2000);

		if (findWanchenglv() == 1) {
			getDailyAward();
			this->scriptIndex = this->scriptList.size();
		}

		if (findHuodongWnd() == 0) {
			this->errorCounter++;
			if (this->errorCounter > 20) {
				this->scriptIndex = this->scriptList.size();
			}
		}
		else {
			errorCounter = 0;
		}

		return 1;
	}
	else {

		PskCommonHelper::CommonMoveTo(this->myFire, 250,60);
		PskCommonHelper::CommonLClick(this->myFire);

		Sleep(1000);

		if (findHuodongWnd() == 0) {
			this->errorCounter++;
			if (this->errorCounter > 20) {
				this->scriptIndex = this->scriptList.size();
			}
		}
		else {
			errorCounter = 0;
			return 1;
		}

		clickCloseBtn();
	}

	str = PskCommonHelper::CommonFindPicE(this->myFire, 620, 100, 750, 180, "TaskBtn.bmp|TaskBtn2.bmp", "000000", 0.9, 0);
	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "TaskBtnX=" << result[1].c_str();
	qDebug() << "TaskBtnY=" << result[2].c_str();

	if (x != -1) {
		PskCommonHelper::CommonMoveTo(this->myFire, 250, 60);
		PskCommonHelper::CommonLClick(this->myFire);
		Sleep(2000);

		if (findWanchenglv() == 1) {
			this->scriptIndex = this->scriptList.size();
		}

		if (findHuodongWnd() == 0) {
			this->errorCounter++;
			if (this->errorCounter > 20) {
				this->scriptIndex = this->scriptList.size();
			}
		}
		else {
			errorCounter = 0;
		}

		return 1;
	}
	else {
		clickCloseBtn();
	}

	str = PskCommonHelper::CommonFindPicE(this->myFire, 700, 100, 810, 180, "ZuduiBtn1.bmp|ZuduiBtn2.bmp|ZuduiBtn3.bmp", "000000", 0.9, 0);
	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "ZuduiBtn1X=" << result[1].c_str();
	qDebug() << "ZuduiBtn1Y=" << result[2].c_str();

	if (x != -1) {
		PskCommonHelper::CommonMoveTo(this->myFire, 250, 60);
		PskCommonHelper::CommonLClick(this->myFire);
		Sleep(1000);

		if (findWanchenglv() == 1) {
			this->scriptIndex = this->scriptList.size();
		}

		if (findHuodongWnd() == 0) {
			this->errorCounter++;
			if (this->errorCounter > 20) {
				this->scriptIndex = this->scriptList.size();
			}
		}
		else {
			errorCounter = 0;
		}
		return 1;
	}

	return 0;
}

int MainScriptThread::canjiaShimenHuodong() {
	std::vector<std::string> result;
	long x, y, l;
	string str = PskCommonHelper::CommonFindPicE(this->myFire, 300, 100, 650, 350, "ShimenTaskTitle.bmp|ShimenTaskTitle2.bmp|ShimenTaskTitle3.bmp", "000000", 0.9, 0);
	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "ShimenTaskTitleX=" << result[1].c_str();
	qDebug() << "ShimenTaskTitleY=" << result[2].c_str();

	if (x != -1) {
		if (findCompleted(x, y) == 1) {
			this->scriptIndex++;
			return 0;
		}

		PskCommonHelper::CommonMoveTo(this->myFire, x + 100, y + 10);
		PskCommonHelper::CommonLClick(this->myFire);

		Sleep(1000);

		return 1;
	}

	str = PskCommonHelper::CommonFindPicE(this->myFire, 250, 100, 650, 350, "ShimenIcon.bmp|ShimenIcon2.bmp", "000000", 0.9, 0);
	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "ShimenTaskTitleX=" << result[1].c_str();
	qDebug() << "ShimenTaskTitleY=" << result[2].c_str();

	if (x != -1) {
		if (findCompleted(x, y) == 1) {
			this->scriptIndex++;
			return 0;
		}

		PskCommonHelper::CommonMoveTo(this->myFire, x + 130, y + 2);
		PskCommonHelper::CommonLClick(this->myFire);

		Sleep(1000);

		return 1;
	}
	return 0;
}

int MainScriptThread::canjiaJishiyuHuodong() {
	std::vector<std::string> result;
	long x, y, l;
	string str = PskCommonHelper::CommonFindPicE(this->myFire, 300, 100, 650, 350, "JishiyuTitle.bmp|JishiyuTitle2.bmp", "000000", 0.9, 0);
	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "JishiyuTitleX=" << result[1].c_str();
	qDebug() << "JishiyuTitleY=" << result[2].c_str();

	if (x != -1) {
		if (findCompleted(x, y) == 1) {
			this->scriptIndex++;
			return 0;
		}

		PskCommonHelper::CommonMoveTo(this->myFire, x + 100, y + 10);
		PskCommonHelper::CommonLClick(this->myFire);

		Sleep(1000);

		return 1;
	}
	return 0;
}

int MainScriptThread::canjiaZhaixinglouHuodong() {
	std::vector<std::string> result;
	long x, y, l;
	string str = PskCommonHelper::CommonFindPicE(this->myFire, 300, 100, 650, 350, "ZhaixinglouTitle.bmp", "000000", 0.9, 0);
	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "ZhaixinglouTitleY=" << result[1].c_str();
	qDebug() << "ZhaixinglouTitleX=" << result[2].c_str();

	if (x != -1) {
		if (findCompleted(x, y) == 1) {
			this->scriptIndex++;
			return 0;
		}

		PskCommonHelper::CommonMoveTo(this->myFire, x + 100, y + 10);
		PskCommonHelper::CommonLClick(this->myFire);

		Sleep(1000);

		return 1;
	}
	return 0;
}

int MainScriptThread::canjiaFabaoHuodong() {
	std::vector<std::string> result;
	long x, y, l;
	string str = PskCommonHelper::CommonFindPicE(this->myFire, 300, 100, 650, 350, "FabaotiaozhanTitle.bmp|FabaotiaozhanTitle2.bmp", "000000", 0.9, 0);
	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "FabaotiaozhanTitleX=" << result[1].c_str();
	qDebug() << "FabaotiaozhanTitleY=" << result[2].c_str();

	if (x != -1) {
		if (findCompleted(x, y) == 1) {
			this->scriptIndex++;
			return 0;
		}

		PskCommonHelper::CommonMoveTo(this->myFire, x + 100, y + 10);
		PskCommonHelper::CommonLClick(this->myFire);

		Sleep(1000);

		return 1;
	}
	return 0;
}

int MainScriptThread::canjiaBangxiuHuodong() {
	std::vector<std::string> result;
	long x, y, l;
	string str = PskCommonHelper::CommonFindPicE(this->myFire, 300, 100, 650, 350, "BangpaiXiulianTitle.bmp|BangpaiXiulianTitle2.bmp", "000000", 0.9, 0);
	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "BangpaiXiulianTitleX=" << result[1].c_str();
	qDebug() << "BangpaiXiulianTitleY=" << result[2].c_str();

	if (x != -1) {
		if (findCompleted(x, y) == 1) {
			this->scriptIndex++;
			return 0;
		}

		PskCommonHelper::CommonMoveTo(this->myFire, x + 100, y + 10);
		PskCommonHelper::CommonLClick(this->myFire);

		Sleep(1000);

		return 1;
	}
	return 0;
}

int MainScriptThread::xunxianwendao(int flag) {
	if (canjiaXunxianHuodong(flag) == 0) {
		PskCommonHelper::CommonMoveTo(this->myFire, 370, 330);
		Sleep(1000);
		PskCommonHelper::CommonLeftDown(this->myFire);
		Sleep(1000);
		PskCommonHelper::CommonMoveTo(this->myFire, 370, 120);
		Sleep(1000);
		PskCommonHelper::CommonLeftUp(this->myFire);
		Sleep(1000);
		PskCommonHelper::CommonMoveTo(this->myFire, 370, 330);
		Sleep(1000);
		PskCommonHelper::CommonLeftDown(this->myFire);
		Sleep(1000);
		PskCommonHelper::CommonMoveTo(this->myFire, 370, 120);
		Sleep(1000);
		PskCommonHelper::CommonLeftUp(this->myFire);
		Sleep(3000);
		if (canjiaXunxianHuodong(flag) == 1) {
			return 1;
		}
	}

	return 0;
}

int MainScriptThread::canjiaXunxianHuodong(int flag) {
	std::vector<std::string> result;
	long x, y, l;
	string str = PskCommonHelper::CommonFindPicE(this->myFire, 300, 100, 650, 350, "XunxianTitle.bmp", "000000", 0.8, 0);
	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "XunxianTitleX=" << result[1].c_str();
	qDebug() << "XunxianTitleY=" << result[2].c_str();

	if (x != -1) {
		if (findCompleted(x, y) == 1) {
			this->scriptIndex++;
			return 0;
		}

		if (flag == 1) {
			PskCommonHelper::CommonMoveTo(this->myFire, x + 100, y + 10);
			PskCommonHelper::CommonLClick(this->myFire);
		}
		

		Sleep(1000);

		return 1;
	}
   
	str = PskCommonHelper::CommonFindPicE(this->myFire, 250, 100, 650, 350, "XunxianIcon.bmp", "000000", 0.8, 0);
	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "XunxianIconX=" << result[1].c_str();
	qDebug() << "XunxianIconY=" << result[2].c_str();

	if (x != -1) {
		if (findCompleted(x, y) == 1) {
			this->scriptIndex++;
			return 0;
		}

		if (flag == 1) {
			PskCommonHelper::CommonMoveTo(this->myFire, x + 100, y + 2);
			PskCommonHelper::CommonLClick(this->myFire);
		}


		Sleep(1000);

		return 1;
	}
	return 0;
}

int MainScriptThread::canjiaDuliangHuodong(int flag) {
	std::vector<std::string> result;
	long x, y, l;
	string str = PskCommonHelper::CommonFindPicE(this->myFire, 300, 100, 650, 350, "DuliangTitle.bmp|DuliangTitle2.bmp", "000000", 0.8, 0);
	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "DuliangTitleX=" << result[1].c_str();
	qDebug() << "DuliangTitleY=" << result[2].c_str();

	if (x != -1) {
		if (findCompleted(x, y) == 1) {
			this->scriptIndex++;
			return 0;
		}

		if (flag == 1) {
			PskCommonHelper::CommonMoveTo(this->myFire, x + 100, y + 10);
			PskCommonHelper::CommonLClick(this->myFire);
		}


		Sleep(1000);

		return 1;
	}

	str = PskCommonHelper::CommonFindPicE(this->myFire, 250, 100, 650, 350, "DuliangIcon.bmp", "000000", 0.8, 0);
	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "DuliangTitleX=" << result[1].c_str();
	qDebug() << "DuliangTitleY=" << result[2].c_str();

	if (x != -1) {
		if (findCompleted(x, y) == 1) {
			this->scriptIndex++;
			return 0;
		}

		if (flag == 1) {
			PskCommonHelper::CommonMoveTo(this->myFire, x + 130, y + 2);
			PskCommonHelper::CommonLClick(this->myFire);
		}


		Sleep(1000);

		return 1;
	}
	return 0;
}


int MainScriptThread::canjiaBangpaiRenwu() {
	std::vector<std::string> result;
	long x, y, l;
	string str = PskCommonHelper::CommonFindPicE(this->myFire, 300, 100, 620, 350, "BangpaiRenwuTitle.bmp|BangpaiRenwuTitle2.bmp|BangpaiRenwuTitle3.bmp|BangpaiRenwuTitle4.bmp", "000000", 0.9, 0);
	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "BangpaiRenwuTitleX=" << result[1].c_str();
	qDebug() << "BangpaiRenwuTitleY=" << result[2].c_str();

	if (x != -1) {
		if (findCompleted(x, y) == 1) {
			this->scriptIndex++;
			return 0;
		}

		PskCommonHelper::CommonMoveTo(this->myFire, x + 100, y + 10);
		PskCommonHelper::CommonLClick(this->myFire);

		Sleep(1000);

		return 1;
	}

	str = PskCommonHelper::CommonFindPicE(this->myFire, 250, 100, 620, 350, "BangpaiTaskIcon.bmp|BangpaiTaskIcon2.bmp", "000000", 0.9, 0);
	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "BangpaiTaskIconX=" << result[1].c_str();
	qDebug() << "BangpaiTaskIconY=" << result[2].c_str();

	if (x != -1) {
		if (findCompleted(x, y) == 1) {
			this->scriptIndex++;
			return 0;
		}

		PskCommonHelper::CommonMoveTo(this->myFire, x + 130, y + 2);
		PskCommonHelper::CommonLClick(this->myFire);

		Sleep(1000);

		return 1;
	}
	return 0;
}

int MainScriptThread::canjiaQinxiuRenwu() {
	std::vector<std::string> result;
	long x, y, l;
	string str = PskCommonHelper::CommonFindPicE(this->myFire, 300, 100, 620, 350, "QinxiuTitle.bmp|QinxiuTitle2.bmp|QinxiuTitle3.bmp|QinxiuTitle4.bmp", "000000", 0.8, 0);
	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "QinxiuTitleX=" << result[1].c_str();
	qDebug() << "QinxiuTitleY=" << result[2].c_str();

	if (x != -1) {
		if (findCompleted(x, y) == 1) {
			this->scriptIndex++;
			return 0;
		}

		PskCommonHelper::CommonMoveTo(this->myFire, x + 100, y + 10);
		PskCommonHelper::CommonLClick(this->myFire);

		Sleep(1000);

		return 1;
	}
	return 0;
}

int MainScriptThread::canjiaZhanyaoRenwu(int flag) {
	std::vector<std::string> result;
	long x, y, l;
	string str = PskCommonHelper::CommonFindPicE(this->myFire, 300, 100, 620, 350, "ZhanyaoTitle.bmp|ZhanyaoTitle2.bmp", "000000", 0.8, 0);
	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "ZhanyaoTitleX=" << result[1].c_str();
	qDebug() << "ZhanyaoTitleY=" << result[2].c_str();

	if (x != -1) {
		if (findCompleted(x, y) == 1) {
			this->scriptIndex++;
			return 0;
		}

		if (findCompleted2020(x, y) == 1) {
			clickCloseBtn();
			Sleep(2000);
			this->scriptIndex++;
			this->tuichuDuiwu();
			return 0;
		}

		if (flag == 1) {
			PskCommonHelper::CommonMoveTo(this->myFire, x + 100, y + 10);
			PskCommonHelper::CommonLClick(this->myFire);
		}

		Sleep(1000);

		return 1;
	}
	return 0;
}


int MainScriptThread::findCompleted(long pX, long pY) {
	std::vector<std::string> result;
	long x, y, l;
	string str = PskCommonHelper::CommonFindPicE(this->myFire, pX + 60, pY - 30, pX + 150 , pY + 20, "Completed.bmp|Completed2.bmp", "000000", 0.9, 0);
	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "CompletedX=" << result[1].c_str();
	qDebug() << "CompletedY=" << result[2].c_str();

	if (x != -1) {

		Sleep(1000);

		return 1;
	}
	return 0;
}

int MainScriptThread::findCompleted2020(long pX, long pY) {
	std::vector<std::string> result;
	long x, y, l;
	string str = PskCommonHelper::CommonFindPicE(this->myFire, pX + 60, pY, pX + 150, pY + 60, "Completed2020.bmp|Completed2020_2.bmp", "000000", 0.8, 0);
	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "Completed2020X=" << result[1].c_str();
	qDebug() << "Completed2020Y=" << result[2].c_str();

	if (x != -1) {

		Sleep(1000);

		return 1;
	}
	return 0;
}

int MainScriptThread::doSouhuTask() {
	std::vector<std::string> result;
	long x, y, l;
	string str = PskCommonHelper::CommonFindPicE(this->myFire, 560, 300, 650, 400, "ShouhuTask.bmp", "000000", 0.9, 0);
	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "ShouhuTaskX=" << result[1].c_str();
	qDebug() << "ShouhuTaskY=" << result[2].c_str();

	if (x != -1) {
	
		Sleep(1000);

		return 1;
	}
	return 0;
}

int MainScriptThread::doChuandaiTask() {
	std::vector<std::string> result;
	long x, y, l;
	string str = PskCommonHelper::CommonFindPicE(this->myFire, 480, 300, 560, 380, "ChuandaiTask.bmp", "000000", 0.9, 0);
	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "ChuandaiTaskX=" << result[1].c_str();
	qDebug() << "ChuandaiTaskY=" << result[2].c_str();

	if (x != -1) {

		Sleep(1000);

		return 1;
	}
	return 0;
}

int MainScriptThread::doRenwushuxingTask() {
	std::vector<std::string> result;
	long x, y, l;
	string str = PskCommonHelper::CommonFindPicE(this->myFire, 600, 150, 700, 350, "RenwushuxingTask.bmp", "000000", 0.9, 0);
	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "RenwushuxingTaskX=" << result[1].c_str();
	qDebug() << "RenwushuxingTaskY=" << result[2].c_str();

	if (x != -1) {

		Sleep(1000);

		return 1;
	}
	return 0;
}

int MainScriptThread::doGudingduiTask() {
	std::vector<std::string> result;
	long x, y, l;
	string str = PskCommonHelper::CommonFindPicE(this->myFire, 400, 300, 500, 400, "Gudingdui.bmp", "000000", 0.9, 0);
	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "GudingduiX=" << result[1].c_str();
	qDebug() << "GudingduiY=" << result[2].c_str();

	if (x != -1) {

		Sleep(1000);

		return 1;
	}
	return 0;
}

int MainScriptThread::doKaishiTask() {
	std::vector<std::string> result;
	long x, y, l;
	string str = PskCommonHelper::CommonFindPicE(this->myFire, 500, 120, 580, 220, "KaishiTask.bmp", "000000", 0.9, 0);
	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "KaishiTaskX=" << result[1].c_str();
	qDebug() << "KaishiTaskY=" << result[2].c_str();

	if (x != -1) {

		Sleep(1000);

		return 1;
	}
	return 0;
}

int MainScriptThread::doChongwuTask() {
	std::vector<std::string> result;
	long x, y, l;
	string str = PskCommonHelper::CommonFindPicE(this->myFire, 450, 120, 580, 220, "ChongwuTask.bmp", "000000", 0.9, 0);
	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "ChongwuTaskX=" << result[1].c_str();
	qDebug() << "ChongwuTaskY=" << result[2].c_str();

	if (x != -1) {

		Sleep(1000);

		return 1;
	}
	return 0;
}

int MainScriptThread::doFashuTask() {
	std::vector<std::string> result;
	long x, y, l;
	string str = PskCommonHelper::CommonFindPicE(this->myFire, 620, 220, 720, 320, "FashuTask.bmp", "000000", 0.9, 0);
	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "FashuTaskX=" << result[1].c_str();
	qDebug() << "FashuTaskY=" << result[2].c_str();

	if (x != -1) {

		Sleep(1000);

		return 1;
	}
	return 0;
}

int MainScriptThread::doFuliTask() {
	std::vector<std::string> result;
	long x, y, l;
	string str = PskCommonHelper::CommonFindPicE(this->myFire, 550, 220, 650, 320, "FuliTask.bmp", "000000", 0.9, 0);
	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "FuliTaskX=" << result[1].c_str();
	qDebug() << "FuliTaskY=" << result[2].c_str();

	if (x != -1) {

		Sleep(1000);

		return 1;
	}
	return 0;
}

int MainScriptThread::doLibaoTask() {
	std::vector<std::string> result;
	long x, y, l;
	string str = PskCommonHelper::CommonFindPicE(this->myFire, 430, 120, 580, 220, "LibaoTask.bmp", "000000", 0.9, 0);
	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "LibaoTaskX=" << result[1].c_str();
	qDebug() << "LibaoTaskY=" << result[2].c_str();

	if (x != -1) {

		Sleep(1000);

		return 1;
	}
	return 0;
}

int MainScriptThread::doShengjicailiaoTask() {
	std::vector<std::string> result;
	long x, y, l;
	string str = PskCommonHelper::CommonFindPicE(this->myFire, 360, 120, 460, 220, "Shengjicailiao.bmp", "000000", 0.9, 0);
	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "ShengjicailiaoX=" << result[1].c_str();
	qDebug() << "ShengjicailiaoY=" << result[2].c_str();

	if (x != -1) {

		Sleep(1000);

		return 1;
	}
	return 0;
}

int MainScriptThread::doJulingTask() {
	std::vector<std::string> result;
	long x, y, l;
	string str = PskCommonHelper::CommonFindPicE(this->myFire, 180, 150, 260, 250, "JulingTask.bmp", "000000", 0.9, 0);
	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "JulingTaskX=" << result[1].c_str();
	qDebug() << "JulingTaskY=" << result[2].c_str();

	if (x != -1) {

		Sleep(1000);

		return 1;
	}
	return 0;
}

int MainScriptThread::doPaihangbangTask() {
	std::vector<std::string> result;
	long x, y, l;
	string str = PskCommonHelper::CommonFindPicE(this->myFire, 550, 300, 650, 365, "PaihangbangTask.bmp", "000000", 0.9, 0);
	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "PaihangbangTaskX=" << result[1].c_str();
	qDebug() << "PaihangbangTaskY=" << result[2].c_str();

	if (x != -1) {

		Sleep(1000);

		return 1;
	}
	return 0;
}

int MainScriptThread::doJiangliTask() {
	std::vector<std::string> result;
	long x, y, l;
	string str = PskCommonHelper::CommonFindPicE(this->myFire, 180, 200, 350, 300, "JiangliTask.bmp", "000000", 0.9, 0);
	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "JiangliTaskX=" << result[1].c_str();
	qDebug() << "JiangliTaskY=" << result[2].c_str();

	if (x != -1) {

		Sleep(1000);

		return 1;
	}
	return 0;
}

int MainScriptThread::doQianghuaTask() {
	std::vector<std::string> result;
	long x, y, l;
	string str = PskCommonHelper::CommonFindPicE(this->myFire, 380, 300, 460, 375, "QianghuaTask.bmp", "000000", 0.9, 0);
	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "QianghuaTaskX=" << result[1].c_str();
	qDebug() << "QianghuaTaskY=" << result[2].c_str();

	if (x != -1) {

		Sleep(1000);

		return 1;
	}
	return 0;
}

int MainScriptThread::doShangzhenTask() {
	std::vector<std::string> result;
	long x, y, l;
	string str = PskCommonHelper::CommonFindPicE(this->myFire, 450, 300, 560, 400, "ShangzhenTask.bmp", "000000", 0.9, 0);
	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "ShangzhenTaskX=" << result[1].c_str();
	qDebug() << "ShangzhenTaskY=" << result[2].c_str();

	if (x != -1) {

		Sleep(1000);

		return 1;
	}
	return 0;
}

int MainScriptThread::doBangpaiTask() {
	std::vector<std::string> result;
	long x, y, l;
	string str = PskCommonHelper::CommonFindPicE(this->myFire, 500, 300, 600, 400, "BangpaiTask.bmp", "000000", 0.9, 0);
	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "BangpaiTaskX=" << result[1].c_str();
	qDebug() << "BangpaiTaskY=" << result[2].c_str();

	if (x != -1) {

		Sleep(1000);

		return 1;
	}
	return 0;
}

int MainScriptThread::doZhangaiTask() {
	std::vector<std::string> result;
	long x, y, l;
	string str = PskCommonHelper::CommonFindPicE(this->myFire, 550, 120, 650, 200, "ZhangaiJinengTask.bmp", "000000", 0.9, 0);
	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "ZhangaiJinengTaskX=" << result[1].c_str();
	qDebug() << "ZhangaiJinengTaskY=" << result[2].c_str();

	if (x != -1) {

		Sleep(1000);

		return 1;
	}
	return 0;
}

int MainScriptThread::clickQianwangBtn() {
	std::vector<std::string> result;
	long x, y, l;
	string str = PskCommonHelper::CommonFindPicE(this->myFire, 560, 380, 680, 480, "QianwangBtn.bmp", "000000", 0.9, 0);
	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "QianwangBtnX=" << result[1].c_str();
	qDebug() << "QianwangBtnY=" << result[2].c_str();

	if (x != -1) {
		PskCommonHelper::CommonMoveTo(this->myFire, x + 5, y + 5);
		PskCommonHelper::CommonLClick(this->myFire);
		Sleep(1000);

		return 1;
	}
	return 0;
}

int MainScriptThread::clickLingquBangwuBtn() {
	std::vector<std::string> result;
	long x, y, l;
	string str = PskCommonHelper::CommonFindPicE(this->myFire, 620, 250, 735, 325, "LingquBangwuBtn.bmp", "000000", 0.9, 0);
	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "LingquBangwuBtnX=" << result[1].c_str();
	qDebug() << "LingquBangwuBtnY=" << result[2].c_str();

	if (x != -1) {
		PskCommonHelper::CommonMoveTo(this->myFire, x + 5, y + 2);
		PskCommonHelper::CommonLClick(this->myFire);
		Sleep(1000);

		return 1;
	}
	return 0;
}

int MainScriptThread::clickJishiyuBtn() {
	std::vector<std::string> result;
	long x, y, l;
	string str = PskCommonHelper::CommonFindPicE(this->myFire, 620, 280, 735, 325, "JishiyuBtn.bmp", "000000", 0.9, 0);
	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "JishiyuBtnX=" << result[1].c_str();
	qDebug() << "JishiyuBtnY=" << result[2].c_str();

	if (x != -1) {
		PskCommonHelper::CommonMoveTo(this->myFire, x + 5, y + 2);
		PskCommonHelper::CommonLClick(this->myFire);
		Sleep(1000);

		return 1;
	}
	return 0;
}

int MainScriptThread::clickZhaixinglouBtn() {
	std::vector<std::string> result;
	long x, y, l;
	string str = PskCommonHelper::CommonFindPicE(this->myFire, 650, 200, 735, 240, "ZhaixinglouBtn.bmp", "000000", 0.9, 0);
	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "ZhaixinglouBtnX=" << result[1].c_str();
	qDebug() << "ZhaixinglouBtnY=" << result[2].c_str();

	if (x != -1) {
		PskCommonHelper::CommonMoveTo(this->myFire, x + 5, y + 2);
		PskCommonHelper::CommonLClick(this->myFire);
		Sleep(1000);

		return 1;
	}
	return 0;
}

int MainScriptThread::clickZhaixingJingyanBtn() {
	std::vector<std::string> result;
	long x, y, l;
	string str = PskCommonHelper::CommonFindPicE(this->myFire, 650, 200, 735, 280, "ZhaixingJingyanBtn.bmp", "000000", 0.9, 0);
	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "ZhaixingJingyanBtnX=" << result[1].c_str();
	qDebug() << "ZhaixingJingyanBtnY=" << result[2].c_str();

	if (x != -1) {
		PskCommonHelper::CommonMoveTo(this->myFire, x + 5, y + 2);
		PskCommonHelper::CommonLClick(this->myFire);
		Sleep(1000);

		return 1;
	}
	return 0;
}

int MainScriptThread::clickZhaixingDaohangBtn() {
	std::vector<std::string> result;
	long x, y, l;
	string str = PskCommonHelper::CommonFindPicE(this->myFire, 650, 280, 735, 320, "ZhaixingDaohangBtn.bmp", "000000", 0.9, 0);
	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "ZhaixingDaohangBtnX=" << result[1].c_str();
	qDebug() << "ZhaixingDaohangBtnY=" << result[2].c_str();

	if (x != -1) {
		PskCommonHelper::CommonMoveTo(this->myFire, x + 5, y + 2);
		PskCommonHelper::CommonLClick(this->myFire);
		Sleep(1000);

		return 1;
	}
	return 0;
}

int MainScriptThread::clickShouhuTiaozhanBtn() {
	std::vector<std::string> result;
	long x, y, l;
	string str = PskCommonHelper::CommonFindPicE(this->myFire, 650, 200, 750, 280, "ShouhuTiaozhanBtn.bmp", "000000", 0.9, 0);
	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "ShouhuTiaozhanBtnX=" << result[1].c_str();
	qDebug() << "ShouhuTiaozhanBtnY=" << result[2].c_str();

	if (x != -1) {
		PskCommonHelper::CommonMoveTo(this->myFire, x + 5, y + 2);
		PskCommonHelper::CommonLClick(this->myFire);
		Sleep(1000);

		return 1;
	}
	return 0;
}

int MainScriptThread::clickBangxiuBtn() {
	std::vector<std::string> result;
	long x, y, l;
	string str = PskCommonHelper::CommonFindPicE(this->myFire, 650, 220, 750, 320, "BangpaiXiulianBtn.bmp", "000000", 0.9, 0);
	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "BangpaiXiulianBtnX=" << result[1].c_str();
	qDebug() << "BangpaiXiulianBtnY=" << result[2].c_str();

	if (x != -1) {
		PskCommonHelper::CommonMoveTo(this->myFire, x + 5, y + 2);
		PskCommonHelper::CommonLClick(this->myFire);
		Sleep(1000);

		return 1;
	}
	return 0;
}


int MainScriptThread::clickFabaoJinzhanBtn() {
	std::vector<std::string> result;
	long x, y, l;
	string str = PskCommonHelper::CommonFindPicE(this->myFire, 460, 320, 600, 400, "FabaoJinzhanBtn.bmp", "000000", 0.9, 0);
	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "FabaoJinzhanBtnX=" << result[1].c_str();
	qDebug() << "FabaoJinzhanBtnY=" << result[2].c_str();

	if (x != -1) {
		PskCommonHelper::CommonMoveTo(this->myFire, x + 5, y + 2);
		PskCommonHelper::CommonLClick(this->myFire);
		Sleep(1000);

		return 1;
	}
	return 0;
}

int MainScriptThread::findTiaozhanWnd() {
	std::vector<std::string> result;
	long x, y, l;
	string str = PskCommonHelper::CommonFindPicE(this->myFire, 220, 50, 350, 120, "TiaozhanWnd.bmp", "000000", 0.9, 0);
	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "TiaozhanWndX=" << result[1].c_str();
	qDebug() << "TiaozhanWndY=" << result[2].c_str();

	if (x != -1) {
		/*PskCommonHelper::CommonMoveTo(this->myFire, x + 5, y + 2);
		PskCommonHelper::CommonLClick(this->myFire);*/
		Sleep(1000);

		return 1;
	}
	return 0;
}

int MainScriptThread::clickFabaoTiaozhanBtn() {
	std::vector<std::string> result;
	long x, y, l;
	string str = PskCommonHelper::CommonFindPicE(this->myFire, 650, 280, 750, 320, "FabaoTiaozhanBtn.bmp", "000000", 0.9, 0);
	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "FabaoTiaozhanBtnX=" << result[1].c_str();
	qDebug() << "FabaoTiaozhanBtnY=" << result[2].c_str();

	if (x != -1) {
		PskCommonHelper::CommonMoveTo(this->myFire, x + 5, y + 2);
		PskCommonHelper::CommonLClick(this->myFire);
		Sleep(1000);

		return 1;
	}
	return 0;
}

int MainScriptThread::clickZhaixingSub() {
	std::vector<std::string> result;
	long x, y, l;
	string str = PskCommonHelper::CommonFindPicE(this->myFire, 620, 120, 735, 200, "ZhaixinglouSub.bmp", "000000", 0.9, 0);
	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "ZhaixinglouSubX=" << result[1].c_str();
	qDebug() << "ZhaixinglouSubY=" << result[2].c_str();

	if (x != -1) {
		PskCommonHelper::CommonMoveTo(this->myFire, x + 5, y + 2);
		PskCommonHelper::CommonLClick(this->myFire);
		Sleep(1000);

		return 1;
	}
	return 0;
}

int MainScriptThread::clickJishiyuSubBtn() {
	std::vector<std::string> result;
	long x, y, l;
	string str = PskCommonHelper::CommonFindPicE(this->myFire, 620, 200, 710, 330, "JishiyuSubBtn.bmp", "000000", 0.9, 0);
	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "JishiyuSubBtnX=" << result[1].c_str();
	qDebug() << "JishiyuSubBtnY=" << result[2].c_str();

	if (x != -1) {
		PskCommonHelper::CommonMoveTo(this->myFire, x + 5, y + 2);
		PskCommonHelper::CommonLClick(this->myFire);
		Sleep(1000);

		return 1;
	}
	return 0;
}

int MainScriptThread::loginOut() {
	std::vector<std::string> result;
	long x, y, l;
	string str = PskCommonHelper::CommonFindPicE(this->myFire, 10, 200, 120, 380, "PigIcon.bmp|PigIcon2.bmp", "000000", 0.9, 0);
	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "PigIconX=" << result[1].c_str();
	qDebug() << "PigIconY=" << result[2].c_str();

	if (x != -1) {
		PskCommonHelper::CommonMoveTo(this->myFire, x + 10, y + 10);
		PskCommonHelper::CommonLClick(this->myFire);
		Sleep(2000);
		clickZhuxiaoBtn();
		Sleep(2000);
		PskCommonHelper::CommonMoveTo(this->myFire, 295, 260);
		PskCommonHelper::CommonLClick(this->myFire);
		Sleep(2000);
		PskCommonHelper::CommonMoveTo(this->myFire, 150, 260);
		PskCommonHelper::CommonLClick(this->myFire);

		return 1;
	}
	return 0;
}

int MainScriptThread::clickZhuxiaoBtn() {
	std::vector<std::string> result;
	long x, y, l;
	string str = PskCommonHelper::CommonFindPicE(this->myFire, 250, 240, 460, 320, "ZhuxiaoBtn.bmp|ZhuxiaoBtn2.bmp", "000000", 0.9, 0);
	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "ZhuxiaoBtnX=" << result[1].c_str();
	qDebug() << "ZhuxiaoBtnY=" << result[2].c_str();

	if (x != -1) {
		PskCommonHelper::CommonMoveTo(this->myFire, x + 5, y + 5);
		PskCommonHelper::CommonLClick(this->myFire);
		Sleep(1000);


		return 1;
	}
	return 0;
}

bool MainScriptThread::getIsPaused()
{
	MainSingleton* theMain = MainSingleton::getInstance();
	QTableWidget* table = theMain->table;
	QTableWidgetItem* item = table->item(index - 1, 0);
	if (item == NULL) {
		return false;
	}

	QString tHWND = item->text();
	if (tHWND == "111111") {
		return true;
	}

	return false;
}

int MainScriptThread::movePigIcon() {
	std::vector<std::string> result;
	long x, y, l;
	string str = PskCommonHelper::CommonFindPicE(this->myFire, 10, 200, 120, 380, "PigIcon.bmp", "000000", 0.9, 0);
	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "PigIconX=" << result[1].c_str();
	qDebug() << "PigIconY=" << result[2].c_str();

	if (x != -1) {
		PskCommonHelper::CommonMoveTo(this->myFire, x + 10, y + 10);
		Sleep(1000);
		PskCommonHelper::CommonLeftDown(this->myFire);
		Sleep(5000);
		PskCommonHelper::CommonMoveTo(this->myFire,0, 0);
		Sleep(1000);
		PskCommonHelper::CommonLClick(this->myFire);
		Sleep(1000);
		PskCommonHelper::CommonLeftUp(this->myFire);
		PskCommonHelper::CommonLeftUp(this->myFire);
		PskCommonHelper::CommonLeftUp(this->myFire);
		Sleep(1000);
		PskCommonHelper::CommonLClick(this->myFire);
		Sleep(1000);

		return 1;
	}

	str = PskCommonHelper::CommonFindPicE(this->myFire, 650, 200, 800, 380, "PigIcon.bmp", "000000", 0.9, 0);
	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "PigIconX=" << result[1].c_str();
	qDebug() << "PigIconY=" << result[2].c_str();

	if (x != -1) {
		PskCommonHelper::CommonMoveTo(this->myFire, x + 10, y + 10);
		Sleep(1000);
		PskCommonHelper::CommonLeftDown(this->myFire);
		Sleep(1000);
		PskCommonHelper::CommonMoveTo(this->myFire, 0, 0);
		Sleep(1000);
		PskCommonHelper::CommonLeftUp(this->myFire);
		PskCommonHelper::CommonLeftUp(this->myFire);
		PskCommonHelper::CommonLeftUp(this->myFire);
		Sleep(1000);

		return 1;
	}
	return 0;
}

int MainScriptThread::clickJinruzhandouBtn() {
	std::vector<std::string> result;
	long x, y, l;
	string str = PskCommonHelper::CommonFindPicE(this->myFire, 650, 250, 750, 350, "JinruzhandouBtn.bmp", "000000", 0.9, 0);
	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "JinruzhandouBtnX=" << result[1].c_str();
	qDebug() << "JinruzhandouBtnY=" << result[2].c_str();

	if (x != -1) {
		PskCommonHelper::CommonMoveTo(this->myFire, x + 5, y + 5);
		PskCommonHelper::CommonLClick(this->myFire);
		Sleep(1000);

		return 1;
	}
	return 0;
}

int MainScriptThread::richangBuchong() {
	if (findBuchongZero() == 1) {

		int random = CommonUtil::generateRandomNumberEx(2);
		if (clickBuchongBtn() == 1) {
			PskCommonHelper::CommonMoveTo(this->myFire, 535, 225);
			PskCommonHelper::CommonLClick(this->myFire);
			Sleep(1000);
			clickCenterQuedingBtn();
			Sleep(1000);
		}

		if (clickBuchongBtn() == 1) {
			PskCommonHelper::CommonMoveTo(this->myFire, 535, 345);
			PskCommonHelper::CommonLClick(this->myFire);
			Sleep(1000);
			clickCenterQuedingBtn();
			Sleep(1000);
		}

		if (random == 1) {
			if (clickBuchongBtn() == 1) {
				PskCommonHelper::CommonMoveTo(this->myFire, 535, 285);
				PskCommonHelper::CommonLClick(this->myFire);
				Sleep(1000);
				clickCenterQuedingBtn();
				Sleep(1000);
			}

			if (clickBuchongBtn() == 1) {
				PskCommonHelper::CommonMoveTo(this->myFire, 535, 405);
				PskCommonHelper::CommonLClick(this->myFire);
				Sleep(1000);
				clickCenterQuedingBtn();
				Sleep(1000);
			}
		}
	}

	return 0;
}

int MainScriptThread::findBuchongZero() {
	std::vector<std::string> result;
	long x, y, l;
	string str = PskCommonHelper::CommonFindPicE(this->myFire, 440, 360, 680, 460, "Buchong1.bmp", "000000", 0.9, 0);
	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "Buchong1X=" << result[1].c_str();
	qDebug() << "Buchong1Y=" << result[2].c_str();

	if (x != -1) {
		/*PskCommonHelper::CommonMoveTo(this->myFire, x + 5, y + 5);
		PskCommonHelper::CommonLClick(this->myFire);*/
		Sleep(1000);

		return 1;
	}
	return 0;
}

int MainScriptThread::clickBuchongBtn() {
	std::vector<std::string> result;
	long x, y, l;
	string str = PskCommonHelper::CommonFindPicE(this->myFire, 420, 400, 520, 480, "BuchongBtn.bmp", "000000", 0.9, 0);
	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "BuchongBtnX=" << result[1].c_str();
	qDebug() << "BuchongBtnY=" << result[2].c_str();

	if (x != -1) {
		PskCommonHelper::CommonMoveTo(this->myFire, x + 5, y + 2);
		PskCommonHelper::CommonLClick(this->myFire);
		Sleep(1000);

		return 1;
	}
	return 0;
}


int MainScriptThread::clickQinxiuBtn() {
	std::vector<std::string> result;
	long x, y, l;
	string str = PskCommonHelper::CommonFindPicE(this->myFire, 650, 250, 750, 350, "QinxiuBtn.bmp", "000000", 0.9, 0);
	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "QinxiuBtnX=" << result[1].c_str();
	qDebug() << "QinxiuBtnY=" << result[2].c_str();

	if (x != -1) {
		PskCommonHelper::CommonMoveTo(this->myFire, x + 5, y + 2);
		PskCommonHelper::CommonLClick(this->myFire);
		Sleep(1000);

		return 1;
	}
	return 0;
}

int MainScriptThread::findZhinengZudui() {
	std::vector<std::string> result;
	long x, y, l;
	string str = PskCommonHelper::CommonFindPicE(this->myFire, 350, 150, 500, 250, "ZhinengZudui.bmp", "000000", 0.9, 0);
	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "ZhinengZuduiX=" << result[1].c_str();
	qDebug() << "ZhinengZuduiY=" << result[2].c_str();

	if (x != -1) {
		PskCommonHelper::CommonMoveTo(this->myFire, 460, 245);
		PskCommonHelper::CommonLClick(this->myFire);
		Sleep(1000);

		return 1;
	}
	return 0;
}

int MainScriptThread::findZhuxianTaskTitle(int isClick) {
	std::vector<std::string> result;
	long x, y, l;
	string str = PskCommonHelper::CommonFindPicE(this->myFire, 120, 120, 250, 220, "ZhuxianTaskTitle.bmp", "000000", 0.9, 0);
	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "ZhuxianTaskTitleX=" << result[1].c_str();
	qDebug() << "ZhuxianTaskTitleY=" << result[2].c_str();

	if (x != -1) {
		if (isClick == 1) {
			PskCommonHelper::CommonMoveTo(this->myFire, x + 5, y + 2);
			PskCommonHelper::CommonLClick(this->myFire);
		}
	
		Sleep(1000);

		return 1;
	}
	return 0;
}

int MainScriptThread::findLevelNotEnough(int isClick) {
	std::vector<std::string> result;
	long x, y, l;
	string str = PskCommonHelper::CommonFindPicE(this->myFire, 300, 100, 360, 180, "Shengzhi.bmp", "000000", 0.9, 0);
	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "ShengzhiX=" << result[1].c_str();
	qDebug() << "ShengzhiY=" << result[2].c_str();

	if (x != -1) {
		if (isClick == 1) {
			PskCommonHelper::CommonMoveTo(this->myFire, x + 5, y + 2);
			PskCommonHelper::CommonLClick(this->myFire);
		}

		Sleep(1000);

		return 1;
	}
	return 0;
}

int MainScriptThread::skipPhoneNumBind(int flag) {
	std::vector<std::string> result;
	long x, y, l;
	string str = PskCommonHelper::CommonFindPicE(this->myFire, 400, 150, 500, 250, "BangdingshoujiTitle.bmp", "000000", 0.9, 0);
	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "BangdingshoujiTitleX=" << result[1].c_str();
	qDebug() << "BangdingshoujiTitleY=" << result[2].c_str();

	if (x != -1) {
		if (flag == 1) {
			PskCommonHelper::CommonMoveTo(this->myFire, 550, 395);
			PskCommonHelper::CommonLClick(this->myFire);
		}
		
		Sleep(1000);

		return 1;
	}

	/*string str = PskCommonHelper::CommonFindPicE(this->myFire, 560, 450, 700, 500, "ZanbuBangding.bmp|ZanbuBangding2.bmp", "000000", 0.9, 0);
	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "ZanbuBangdingX=" << result[1].c_str();
	qDebug() << "ZanbuBangdingY=" << result[2].c_str();

	if (x != -1) {
		PskCommonHelper::CommonMoveTo(this->myFire, x + 5, y + 5);
		PskCommonHelper::CommonLClick(this->myFire);
		Sleep(1000);

		return 1;
	}*/
	return 0;
}

int MainScriptThread::clickEnterGameBtn(int flag) {
	std::vector<std::string> result;
	long x, y, l;
	string str = PskCommonHelper::CommonFindPicE(this->myFire, 330, 300, 450, 450, "EnterGameBtn.bmp", "000000", 0.9, 0);
	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "EnterGameBtnY=" << result[1].c_str();
	qDebug() << "EnterGameBtnX=" << result[2].c_str();

	if (x != -1) {
		if (flag == 1) {
			PskCommonHelper::CommonMoveTo(this->myFire, x + 5, y + 5);
			PskCommonHelper::CommonLClick(this->myFire);
			Sleep(1000);
			this->mainStepIndex = MAIN_STEPS::MAIN_TASK;
			Sleep(20000);
		}
		Sleep(1000);
		return 1;
	}
	return 0;
}

int MainScriptThread::clickDuihuaCloseBtn(int flag) {
	std::vector<std::string> result;
	long x, y, l;
	string str = PskCommonHelper::CommonFindPicE(this->myFire, 620, 200, 780, 375, "DuihuaCloseBtn.bmp", "000000", 0.9, 0);
	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "DuihuaCloseBtnY=" << result[1].c_str();
	qDebug() << "DuihuaCloseBtnX=" << result[2].c_str();

	if (x != -1) {
		if (flag == 1) {
			PskCommonHelper::CommonMoveTo(this->myFire, x + 5, y + 2);
			PskCommonHelper::CommonLClick(this->myFire);
			Sleep(1000);
		
		}
		
		return 1;
	}
	return 0;
}

int MainScriptThread::clickServerBtn(int flag) {
	std::vector<std::string> result;
	long x, y, l;
	string str = PskCommonHelper::CommonFindPicE(this->myFire, 400, 300, 550, 450, "DianjiXuanfuBtn.bmp", "000000", 0.9, 0);
	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "DianjiXuanfuBtnX=" << result[1].c_str();
	qDebug() << "DianjiXuanfuBtnY=" << result[2].c_str();

	if (x != -1) {
		if (flag == 1) {
			PskCommonHelper::CommonMoveTo(this->myFire, x + 5, y + 5);
			PskCommonHelper::CommonLClick(this->myFire);
			
		}
		Sleep(1000);
		return 1;
	}
	return 0;
}

int MainScriptThread::findAndEnterGame(int flag) {
	std::vector<std::string> result;
	long x, y, l;
	string str = PskCommonHelper::CommonFindPicE(this->myFire, 0, 0, 800, 350, "DWB_Icon.bmp|DWB_Icon2.bmp", "000000", 0.9, 0);
	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "DWB_IconX=" << result[1].c_str();
	qDebug() << "DWB_IconY=" << result[2].c_str();

	if (x != -1) {
		if (flag == 1) {
			PskCommonHelper::CommonMoveTo(this->myFire, x + 20, y + 20);
			PskCommonHelper::CommonLClick(this->myFire);
		}
		
		Sleep(1000);

		return 1;
	}
	return 0;
}

int MainScriptThread::findLoginUI() {
	std::vector<std::string> result;
	long x, y, l;
	string str = PskCommonHelper::CommonFindPicE(this->myFire, 150, 230, 250, 350, "PhoneUI.bmp", "000000", 0.9, 0);
	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "PhoneUIX=" << result[1].c_str();
	qDebug() << "PhoneUIY=" << result[2].c_str();

	if (x != -1) {
		
		Sleep(1000);

		return 1;
	}
	return 0;
}

int MainScriptThread::findZhanghaoDengluUI() {
	std::vector<std::string> result;
	long x, y, l;
	//ZhanghaoDengluTitle.bmp
	string str = PskCommonHelper::CommonFindPicE(this->myFire, 400, 150, 520, 250, "ZhanghaoDengluTitle.bmp", "000000", 0.9, 0);
	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "ZhanghaoDengluTitleX=" << result[1].c_str();
	qDebug() << "ZhanghaoDengluTitleY=" << result[2].c_str();

	if (x != -1) {
		Sleep(1000);

		return 1;
	}

	/*string str = PskCommonHelper::CommonFindPicE(this->myFire, 400, 120, 520, 200, "ZhanghaoDengluUI.bmp", "000000", 0.9, 0);
	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "ZhanghaoDengluUIX=" << result[1].c_str();
	qDebug() << "ZhanghaoDengluUIY=" << result[2].c_str();

	if (x != -1) {

		Sleep(1000);

		return 1;
	}*/
	return 0;
}

int MainScriptThread::clickGonggaoCloseBtn() {
	std::vector<std::string> result;
	long x, y, l;
	//ZhanghaoDengluTitle.bmp
	string str = PskCommonHelper::CommonFindPicE(this->myFire, 350, 400, 480, 480, "GonggaoCloseBtn.bmp", "000000", 0.9, 0);
	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "GonggaoCloseBtnX=" << result[1].c_str();
	qDebug() << "GonggaoCloseBtnY=" << result[2].c_str();

	if (x != -1) {
		PskCommonHelper::CommonMoveTo(this->myFire, x + 5, y + 5);
		PskCommonHelper::CommonLClick(this->myFire);
		Sleep(1000);
		
		return 1;
	}

	return 0;
}

int MainScriptThread::findJulingTimer() {
	std::vector<std::string> result;
	long x, y, l;
	//ZhanghaoDengluTitle.bmp
	string str = PskCommonHelper::CommonFindPicE(this->myFire, 550, 300, 650, 360, "JulingTimer.bmp", "000000", 0.9, 0);
	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "JulingTimerX=" << result[1].c_str();
	qDebug() << "JulingTimerY=" << result[2].c_str();

	if (x != -1) {
		Sleep(1000);

		return 1;
	}

	return 0;
}

int MainScriptThread::findJulingLingjiangBtn() {
	std::vector<std::string> result;
	long x, y, l;
	//ZhanghaoDengluTitle.bmp
	string str = PskCommonHelper::CommonFindPicE(this->myFire, 550, 400, 680, 480, "JulingLingjiangBtn.bmp", "000000", 0.9, 0);
	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "JulingLingjiangBtnX=" << result[1].c_str();
	qDebug() << "JulingLingjiangBtnY=" << result[2].c_str();

	if (x != -1) {
		Sleep(1000);

		return 1;
	}

	return 0;
}

int MainScriptThread::clickKaishijulingBtn() {
	std::vector<std::string> result;
	long x, y, l;
	//ZhanghaoDengluTitle.bmp
	string str = PskCommonHelper::CommonFindPicE(this->myFire, 550, 400, 680, 480, "KaishiJulingBtn.bmp", "000000", 0.9, 0);
	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "KaishiJulingBtnX=" << result[1].c_str();
	qDebug() << "KaishiJulingBtnY=" << result[2].c_str();

	if (x != -1) {
		PskCommonHelper::CommonMoveTo(this->myFire, x + 5, y + 5);
		PskCommonHelper::CommonLClick(this->myFire);
		Sleep(1000);

		return 1;
	}

	return 0;
}

int MainScriptThread::findJiaogaoJilv() {
	std::vector<std::string> result;
	long x, y, l;
	//ZhanghaoDengluTitle.bmp
	string str = PskCommonHelper::CommonFindPicE(this->myFire, 500, 300, 650, 360, "Jigaojilv.bmp", "000000", 0.9, 0);
	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "JiaogaojilvX=" << result[1].c_str();
	qDebug() << "JiaogaojilvY=" << result[2].c_str();

	if (x != -1) {
		Sleep(1000);

		return 1;
	}

	return 0;
}

int MainScriptThread::clickZhuceBtn() {
	std::vector<std::string> result;
	long x, y, l;
	string str = PskCommonHelper::CommonFindPicE(this->myFire, 520, 375, 610, 420, "ZhuceBtn2.bmp", "000000", 0.9, 0);
	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "ZhuceBtnX=" << result[1].c_str();
	qDebug() << "ZhuceBtnY=" << result[2].c_str();

	if (x != -1) {
		PskCommonHelper::CommonMoveTo(this->myFire, x + 5, y + 5);
		PskCommonHelper::CommonLClick(this->myFire);
		Sleep(1000);

		return 1;
	}

	/*string str = PskCommonHelper::CommonFindPicE(this->myFire, 580, 420, 720, 520, "ZhuceBtn.bmp", "000000", 0.9, 0);
	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "ZhuceBtnX=" << result[1].c_str();
	qDebug() << "ZhuceBtnY=" << result[2].c_str();

	if (x != -1) {
		PskCommonHelper::CommonMoveTo(this->myFire, x + 5, y + 5);
		PskCommonHelper::CommonLClick(this->myFire);
		Sleep(1000);

		return 1;
	}*/
	return 0;
}

int MainScriptThread::clickOtherGameIcon(int flag) {
	std::vector<std::string> result;
	long x, y, l;
	string str = PskCommonHelper::CommonFindPicE(this->myFire, 500, 250, 700, 400, "OtherGameIcon.bmp|OtherGameIcon2.bmp", "000000", 0.9, 0);
	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "OtherGameIconX=" << result[1].c_str();
	qDebug() << "OtherGameIconY=" << result[2].c_str();

	if (x != -1) {
		if (flag == 1) {
			PskCommonHelper::CommonMoveTo(this->myFire, x + 5, y + 5);
			PskCommonHelper::CommonLClick(this->myFire);
		}
		
		Sleep(1000);

		return 1;
	}
	return 0;
}

int MainScriptThread::clickFeizhuIcon() {
	std::vector<std::string> result;
	long x, y, l;
	string str = PskCommonHelper::CommonFindPicE(this->myFire, 100, 350, 200, 450, "FeizhuIcon.bmp|FeizhuIcon2.bmp", "000000", 0.9, 0);
	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "FeizhuIconX=" << result[1].c_str();
	qDebug() << "FeizhuIconY=" << result[2].c_str();

	if (x != -1) {
		PskCommonHelper::CommonMoveTo(this->myFire, 200, 330);
		PskCommonHelper::CommonLClick(this->myFire);
		Sleep(1000);

		return 1;
	}
	return 0;
}

int MainScriptThread::selectLoginMethod(int flag) {
	std::vector<std::string> result;
	long x, y, l;
	//string str = PskCommonHelper::CommonFindPicE(this->myFire, 250, 100, 380, 220, "Fei.bmp|Fei2.bmp", "000000", 0.9, 0);
	//qDebug() << str.c_str();

	//result = CommonUtil::split(str, "|");

	//l = result.size();
	//if (l < 3) {
	//	return 0;
	//}

	//x = atol(result[1].c_str());
	//y = atol(result[2].c_str());

	//qDebug() << "FeiX=" << result[1].c_str();
	//qDebug() << "FeiY=" << result[2].c_str();

	//if (x != -1) {
	//	if (flag == 1) {
	//		PskCommonHelper::CommonMoveTo(this->myFire, 200, 330);
	//		PskCommonHelper::CommonLClick(this->myFire);
	//	}
	//	
	//	Sleep(1000);

	//	return 1;
	//}

	string str = PskCommonHelper::CommonFindPicE(this->myFire, 200, 300, 280, 350, "FeizhuLogin.bmp", "000000", 0.9, 0);
	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "FeizhuLoginX=" << result[1].c_str();
	qDebug() << "FeizhuLoginY=" << result[2].c_str();

	if (x != -1) {
		if (flag == 1) {
			PskCommonHelper::CommonMoveTo(this->myFire, 265, 295);
			PskCommonHelper::CommonLClick(this->myFire);
		}

		Sleep(1000);

		return 1;
	}

	str = PskCommonHelper::CommonFindPicE(this->myFire, 400, 150, 500, 250, "XuanzeDenglu.bmp", "000000", 0.9, 0);
	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "XuanzeDengluX=" << result[1].c_str();
	qDebug() << "XuanzeDengluY=" << result[2].c_str();

	if (x != -1) {
		if (flag == 1) {
			PskCommonHelper::CommonMoveTo(this->myFire, 265, 295);
			PskCommonHelper::CommonLClick(this->myFire);
		}

		Sleep(1000);

		return 1;
	}
	return 0;
}

int MainScriptThread::findHuiheIcon() {
	std::vector<std::string> result;
	long x, y, l;
	string str = PskCommonHelper::CommonFindPicE(this->myFire, 45, 0, 100, 100, "HuiheIcon.bmp", "000000", 0.9, 0);
	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "HuiheIconX=" << result[1].c_str();
	qDebug() << "HuiheIconY=" << result[2].c_str();

	if (x != -1) {
		this->huiheCounter++;
		Sleep(1000);
		if (huiheCounter > 300) {
			this->errorCounter = 22;
			this->scriptIndex = this->scriptList.size();
			return 0;
		}

		return 1;
	}
	else {
		this->huiheCounter = 0;
	}
	return 0;
}

int MainScriptThread::findWanchenglv() {
	std::vector<std::string> result;
	long x, y, l;
	string str = PskCommonHelper::CommonFindPicE(this->myFire, 625, 400, 650, 480, "WanchengLv.bmp", "000000", 0.9, 0);
	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "WanchengLvX=" << result[1].c_str();
	qDebug() << "WanchengLvY=" << result[2].c_str();

	if (x != -1) {

		Sleep(1000);

		return 1;
	}
	return 0;
}

int MainScriptThread::bindMyWnd(long hwnd) {
	char buf[1000];
	GetCurrentDirectoryA(1000, buf);  //得到当前工作路径
	string path;
	path.assign(buf);
	path.append("\\resources");

	PskCommonHelper::CommonSetPath(this->myFire, path.c_str());

	string xx = PskCommonHelper::CommonGetMachineCode(this->myFire);
	qDebug() << "machineCode=" << xx.c_str();

	int bindRet = PskCommonHelper::CommonBindWndEx(this->myFire, hwnd, "dx.graphic.opengl", "windows3", "normal", "", 103);

	return bindRet;
}

int MainScriptThread::getThreadFire()
{
	this->myFire = DMSoft::getInstance()->newDMObject();
	int result;

	result = PskCommonHelper::CommonReg(myFire, "pskfire20928db6b002f54b0b0f1d5dcc665316", "ambition");
	myFire->PskSetShowErrorMsg(0);
	if (result != 1) {
		qDebug() << "reg error";

	}
	else {
		qDebug() << "reg success!" << myFire->PskVer();
	}

	/*result = PskCommonHelper::CommonGuard(myFire, 1, "np");
	if (result != 1) {
		qDebug() << "DmGuard np error";
	}

	result = PskCommonHelper::CommonGuard(myFire, 1, "memory");
	if (result != 1) {
		qDebug() << "DmGuard memory error";
	}

	result = PskCommonHelper::CommonGuard(myFire, 1, "block");
	if (result != 1) {
		qDebug() << "DmGuard block error";
	}

	result = PskCommonHelper::CommonGuard(myFire, 1, "b2");
	if (result != 1) {
		qDebug() << "DmGuard b2 error ";
	}

	result = PskCommonHelper::CommonGuard(myFire, 1, "f1");
	if (result != 1) {
		qDebug() << "DmGuard f1 error";
	}*/

	return 0;
}