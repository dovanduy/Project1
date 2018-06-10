#pragma once

#include <QThread>
#include "PskCommonHelper.h"
#include <QDebug>
#include "MainSingleton.h"

class MainScriptThread : public QThread
{
	Q_OBJECT

public:
	MainScriptThread(QObject *parent);
	~MainScriptThread();

	MainScriptThread(long HWND, QString config, int index, int accountIndex);
private:
	enum MAIN_STEPS {WAIT_LOGIN, MAIN_TASK, GENERAL_TASK, REGISTER};
	enum SHANGCHENG_ITEMS {QIANG, ZHANG, JIAN, SHAN, DAO, MAOZI, YIFU, YAODAI, XIEZI};

	int mainStepIndex;
	int index;
	int scriptIndex;
	int accountIndex;
	int huodongSkipCounter;
	long lHWND;
	QString config;
	QString account, password;
	QString folder;
	QJsonArray scriptList;
	bool isBanghui;
	bool isSkillUpdated;

	long time_limit;
	long main_time_limit;
	DWORD startTime;
	DWORD lastJulingTime;

	int bangpaiCounter;
	int shimenCounter;
	int zhanyaoCounter;
	int xunxianCounter;
	int duliangCounter;
	int enterGameCounter;
	int currentMoney;

	bool isFuliGot;

	int errorCounter;

	int huiheCounter;

	long currentLevel;

	bool isZhuxian;
	bool isGen;
	bool isOnlyJuling;
	bool IsBuyCheckBox;
	int zone;
	int item_name_parameter;
	int item_ye_parameter;
	int item_num_parameter;

	void run();
	int MainScriptThread::getThreadFire();

	Ifire* myFire;
	int MainScriptThread::bindMyWnd(long lHWND);
	int MainScriptThread::loginGame();
	int MainScriptThread::clickOtherGameIcon(int flag);
	int MainScriptThread::findAndEnterGame(int flag);
	int MainScriptThread::clickFeizhuIcon();
	int MainScriptThread::getThreadAccount(int accountIndex);
	int MainScriptThread::findLoginUI();
	int MainScriptThread::findZhanghaoDengluUI();
	int MainScriptThread::loginOut();
	int MainScriptThread::clickZhuxiaoBtn();


	int MainScriptThread::loginForFeizhu();
	void MainScriptThread::getConfig(QString config);
	int MainScriptThread::forADBInput(int index, QString path, string text);
	int MainScriptThread::skipPhoneNumBind(int flag);
	int MainScriptThread::clickEnterGameBtn(int flag);
	int MainScriptThread::EnterGameSubScript();
	int MainScriptThread::MainTaskSubScript();
	int MainScriptThread::clickTaskBtn();
	int MainScriptThread::findZhuxianTaskTitle(int isClick);
	int MainScriptThread::clickQianwangBtn();
	int MainScriptThread::clickJinruzhandouBtn();
	int MainScriptThread::findHuiheIcon();
	int MainScriptThread::doSouhuTask();
	int MainScriptThread::clickCloseBtn();
	int MainScriptThread::findShuxingJiadian();
	int MainScriptThread::doRenwushuxingTask();
	int MainScriptThread::doJiangliTask();
	int MainScriptThread::movePigIcon();
	int MainScriptThread::doShangzhenTask();
	int MainScriptThread::clickSkipBtn();
	int MainScriptThread::clickChuanshangBtn();
	int MainScriptThread::doBangpaiTask();
	int MainScriptThread::clickGoumaiBtn();
	int MainScriptThread::clickGuanruBtn();
	int MainScriptThread::doZhangaiTask();
	int MainScriptThread::findLevelNotEnough(int isClick);
	int MainScriptThread::clickHuodongBtn();
	int MainScriptThread::GeneralTaskSubScript();
	int MainScriptThread::selectLoginMethod(int flag);
	int MainScriptThread::canjiaShimenHuodong();
	int MainScriptThread::doGudingduiTask();
	int MainScriptThread::doChuandaiTask();
	int MainScriptThread::clickShiyongBtn();
	int MainScriptThread::doPaihangbangTask();
	int MainScriptThread::findCompleted(long pX, long pY);
	int MainScriptThread::clickFangzhiBtn();
	int MainScriptThread::clickSubCloseBtn(bool flag);
	int MainScriptThread::doJulingTask();
	int MainScriptThread::doQianghuaTask();
	int MainScriptThread::clickQinxiuBtn();
	int MainScriptThread::doKaishiTask();
	int MainScriptThread::doLibaoTask();
	int MainScriptThread::doChongwuTask();
	int MainScriptThread::doFashuTask();

	bool MainScriptThread::getIsPaused();

	int MainScriptThread::canjiaZhanyaoRenwu(int flag);
	int MainScriptThread::canjiaBangpaiRenwu();
	int MainScriptThread::canjiaQinxiuRenwu();

	bool MainScriptThread::getIsEnded();
	int MainScriptThread::clickLingquBangwuBtn();
	int MainScriptThread::clickKuaijiezuduiBtn(bool flag);
	int MainScriptThread::clickZidongpipeiBtn();
	int MainScriptThread::clickZuduiBtn();
	int MainScriptThread::findTuiduiBtn(int flag);
	int MainScriptThread::findShenqingliebiao(int flag);
	int MainScriptThread::clickTongyiruduiBtn();
	int MainScriptThread::tuichuDuiwu();
	int MainScriptThread::isInDuiwu();
	int MainScriptThread::clickGuiduiBtn();
	int MainScriptThread::findJiesanBtn(int flag);
	int MainScriptThread::findCompleted2020(long pX, long pY);
	int MainScriptThread::canjiaJishiyuHuodong();
	int MainScriptThread::clickJishiyuBtn();
	int MainScriptThread::clickJishiyuSubBtn();
	int MainScriptThread::canjiaZhaixinglouHuodong();
	int MainScriptThread::clickZhaixinglouBtn();

	int MainScriptThread::clickZhaixingJingyanBtn();
	int MainScriptThread::clickZhaixingDaohangBtn();
	int MainScriptThread::clickZhaixingSub();
	int MainScriptThread::canjiaFabaoHuodong();
	int MainScriptThread::clickShouhuTiaozhanBtn();
	int MainScriptThread::clickFabaoTiaozhanBtn();
	int MainScriptThread::canjiaBangxiuHuodong();

	int MainScriptThread::findTiaozhanWnd();
	int MainScriptThread::clickFabaoJinzhanBtn();
	int MainScriptThread::clickBangxiuBtn();
	int MainScriptThread::canjiaXunxianHuodong(int flag);
	int MainScriptThread::xunxianwendao(int flag);

	int MainScriptThread::findTaskBtn();
	int MainScriptThread::getCurrentLevel();
	int MainScriptThread::getCurrentLevelSubScript();

	int MainScriptThread::canjiaDuliangHuodong(int flag);

	int MainScriptThread::clickServerBtn(int flag);
	int MainScriptThread::clickZhidaoBtn();
	int MainScriptThread::jiaruBangpai();
	int MainScriptThread::clickShenqingBtn();

	int MainScriptThread::duliangTask();
	int MainScriptThread::clickRichangBtn();
	int MainScriptThread::findWanchenglv();

	int MainScriptThread::getDailyAward();
	int MainScriptThread::findZhinengZudui();
	int MainScriptThread::clickJulingBtn();
	int MainScriptThread::doFuliTask();

	int MainScriptThread::findJulingWnd();
	int MainScriptThread::forJuling();
	int MainScriptThread::clickCenterQuedingBtn();

	int MainScriptThread::findBuchongZero();
	int MainScriptThread::richangBuchong();
	int MainScriptThread::clickBuchongBtn();
	int MainScriptThread::timerChecker();

	int MainScriptThread::findHuodongWnd();
	int MainScriptThread::findRenwuWnd();

	int MainScriptThread::RegisterSubScript();
	int MainScriptThread::clickZhuceBtn();

	int MainScriptThread::saveSingleAccuntSub(int index);
	int MainScriptThread::clickKaishiBtn(int flag);
	int MainScriptThread::clickJueseQuedingBtn(int flag);

	int MainScriptThread::clickDuihuaIcon();
	int MainScriptThread::clickDuihuaCloseBtn(int flag);

	int MainScriptThread::findJulingTimer();
	int MainScriptThread::findJiaogaoJilv();
	int MainScriptThread::clickGonggaoCloseBtn();
	int MainScriptThread::findJulingLingjiangBtn();

	int MainScriptThread::findFuliWnd();
	int MainScriptThread::getMyFuli();

	int MainScriptThread::qiandaoSubScript();
	int MainScriptThread::clickDengjilibaoBtn();
	int MainScriptThread::clickFuliBtn();
	int MainScriptThread::getCurrentMoneySubScript();
	int MainScriptThread::getCurrentMoney();
	int MainScriptThread::chickBaoguoBtn();

	int MainScriptThread::findBaoguoWnd();
	int MainScriptThread::clickKaishijulingBtn();
	int MainScriptThread::updateSkills();
	int MainScriptThread::clickShengji10Btn(int flag);

	int MainScriptThread::clickShangchengBtn(int flag);
	int MainScriptThread::shangchengGoumai();
	int MainScriptThread::findShanghuiWnd();
	int MainScriptThread::getSavedGold();
	int MainScriptThread::findDuihuanJinziWnd();
	int MainScriptThread::doShengjicailiaoTask();
};
