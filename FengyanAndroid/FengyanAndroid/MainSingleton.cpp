#include "MainSingleton.h"


QMutex mutex;
MainSingleton::MainSingleton()
{
	this->windowCount = 0;
	this->accountIndex = 0;
	this->totalAccountNum = 0;
	this->config = "";
	this->path = "";
	this->folder = "";
	this->genAccountNum = 0;
}


MainSingleton::~MainSingleton()
{
}

MainSingleton* MainSingleton::instance;
MainSingleton* MainSingleton::getInstance() {
	if (instance == NULL) {
		instance = new MainSingleton();
	}

	return instance;
}

void MainSingleton::setRegisterID(int registerID) {
	this->registerID = registerID;
}

void MainSingleton::setStartAccountID(int startAccountID) {
	this->accountIndex = startAccountID;
}

int MainSingleton::getTheAccountIndex() {
	mutex.lock();
	this->accountIndex++;
	while (this->idsMap.contains(this->accountIndex)) {
		this->accountIndex++;
	}

	mutex.unlock();
	return this->accountIndex;
}

int MainSingleton::getRegisterID() {
	int ret = 0;
	mutex.lock();
	ret = this->registerID;
	this->registerID++;
	mutex.unlock();
	return ret;
}

