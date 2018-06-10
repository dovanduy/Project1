#include "DMSoft.h"
CLSID clsid;   //COM对象类标示符

DMSoft::DMSoft()
{
	RegistryDll();
}


DMSoft::~DMSoft()
{
}

BOOL DMSoft::RegistryDll()
{
	char buf[1000];
	GetCurrentDirectoryA(1000, buf);  //得到当前工作路径
	string path;
	path.assign(buf);
	path.append("\\psk.dll");

	LRESULT(CALLBACK* lpDllEntryPoint)();
	HINSTANCE hLib = LoadLibraryA(path.c_str());
	if (hLib < (HINSTANCE)HINSTANCE_ERROR)
	{
		return FALSE;
	}
	(FARPROC&)lpDllEntryPoint = GetProcAddress(hLib, "DllRegisterServer");
	BOOL bRet = FALSE;
	if (lpDllEntryPoint != NULL)
	{
		HRESULT hr = (*lpDllEntryPoint)();
		bRet = SUCCEEDED(hr);
		if (FAILED(hr))
		{
			
		}
	}
	FreeLibrary(hLib);
	return bRet;
}

void DMSoft::initDMObject()
{
	//下面直接加载dll创建对象，避免进行注册文件
	typedef HRESULT(__stdcall * pfnGCO) (REFCLSID, REFIID, void**);
	pfnGCO fnGCO = NULL;
	HINSTANCE hdllInst = LoadLibraryA("dm.dll");
	fnGCO = (pfnGCO)GetProcAddress(hdllInst, "DllGetClassObject");
	if (fnGCO != 0)
	{
		IClassFactory* pcf = NULL;
		HRESULT hr = (fnGCO)(__uuidof(fire), IID_IClassFactory, (void**)&pcf);
		if (SUCCEEDED(hr) && (pcf != NULL))
		{
			hr = pcf->CreateInstance(NULL, __uuidof(fire), (void**)&fr);
			if ((SUCCEEDED(hr) && (fr != NULL)) == FALSE)
				return;
		}
		pcf->Release();

	}


	return;
}

Ifire* DMSoft::newDMObject()
{
	Ifire *DM = NULL;
	//下面直接加载dll创建对象，避免进行注册文件
	typedef HRESULT(__stdcall * pfnGCO) (REFCLSID, REFIID, void**);
	pfnGCO fnGCO = NULL;
	HINSTANCE hdllInst = LoadLibraryA("psk.dll");
	fnGCO = (pfnGCO)GetProcAddress(hdllInst, "DllGetClassObject");
	if (fnGCO != 0)
	{
		IClassFactory* pcf = NULL;
		HRESULT hr = (fnGCO)(__uuidof(fire), IID_IClassFactory, (void**)&pcf);
		if (SUCCEEDED(hr) && (pcf != NULL))
		{
			hr = pcf->CreateInstance(NULL, __uuidof(Ifire), (void**)&DM);
			if ((SUCCEEDED(hr) && (DM != NULL)) == FALSE)
			return DM;
		}
		pcf->Release();

	}

	return DM;
}


DMSoft* DMSoft::instance;
DMSoft* DMSoft::getInstance()
{
	if (instance == NULL) {
		instance = new DMSoft();
	}
	return instance;
}

Ifire* DMSoft::getDMObject()
{
	if (fr == NULL) {
		initDMObject();
	}
	return fr;
}

Ifire* DMSoft::getOtherDMObject()
{
	Ifire* newDM;
	WinExec("regsvr32 d3d12.dll /s", SW_HIDE);		//运行注册插件命令
												//	}
	if (SUCCEEDED(CoInitialize(NULL)))				//初始化COM库
	{
		//根据给定的程序标示符从注册表中找出对应的类标示符
		//这里的"dm.dmsoft"是dll在注册表里的键值，将类标示符赋给clsid 
		HRESULT hr = CLSIDFromProgID(OLESTR("psk.fire"), &clsid);
		//用指定的类标示符创建一个未初始化的COM对象
		//Idmsoft：创建的com对象的接口标示符
		//dm:用来接收指向com对象接口地址的指针变量
		//CLSCTX_INPROC_SERVER  创建同一进程中运行的组件
		HRESULT Hr = CoCreateInstance(clsid, NULL, CLSCTX_INPROC_SERVER,
			__uuidof(fire), (LPVOID*)&newDM);
		if (SUCCEEDED(Hr))
		{
			CoFreeUnusedLibraries();				//卸载不用的COM服务
		}
	}
	else
	{
		//AfxMessageBox("初始化COM组件失败！");
	}
	return newDM;
}


