#pragma once
#import "psk.dll" no_namespace
#include <iostream>
//using namespace dm;
using namespace std;

class DMSoft
{
public:



	~DMSoft();


	static DMSoft* getInstance();
	Ifire* getDMObject();
	Ifire* getOtherDMObject();
	Ifire* DMSoft::newDMObject();
private:
	DMSoft();
	static DMSoft* instance;
	void initDMObject();
	BOOL DMSoft::RegistryDll();
	Ifire *fr = NULL;


};

