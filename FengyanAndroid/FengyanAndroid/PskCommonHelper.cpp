#include "PskCommonHelper.h"



PskCommonHelper::PskCommonHelper()
{
}


PskCommonHelper::~PskCommonHelper()
{
}

int PskCommonHelper::CommonLClick(Ifire* fire) {

	fire->PskLClick();
	return 0;
}

int PskCommonHelper::CommonUnbindWindow(Ifire* fire) {

	return fire->PskUnBindWnd();
}

int PskCommonHelper::CommonRelease(Ifire* fire) {

	return fire->Release();
}


int PskCommonHelper::CommonLeftDown(Ifire* fire) {

	fire->PskLDown();
	return 0;
}

int PskCommonHelper::CommonLeftUp(Ifire* fire) {

	fire->PskLUp();
	return 0;
}

int PskCommonHelper::CommonMoveTo(Ifire* fire, long x, long y) {

	fire->PskMTo(x, y);
	return 0;
}

int PskCommonHelper::CommonReg(Ifire* fire, LPCSTR code, LPCSTR ver) {
	int ret = fire->PskReg(code, ver);
	return ret;
}

int PskCommonHelper::CommonGuard(Ifire* fire, long en, LPCSTR type)
{
	int ret = fire->PskGuard(en, type);
	return ret;
}

string PskCommonHelper::CommonGetVer(Ifire* fire) {
	string ver = fire->PskVer();
	return ver;
}

string PskCommonHelper::CommonOcr(Ifire* fire, long x1, long y1, long x2, long y2, LPCSTR color, double sim) {
	string ret = fire->PskOcr(x1, y1, x2, y2, color, sim);
	return ret;
}

int PskCommonHelper::CommonSetDict(Ifire* fire,long index, LPCSTR file) {
	int ret = fire->PskSetDict(index, file);
	return ret;
}

string PskCommonHelper::CommonGetMachineCode(Ifire* fire) {
	string code = fire->GetMachineCode();
	return code;
}

int PskCommonHelper::CommonSetPath(Ifire* fire, LPCSTR path) {
	fire->PskSetPath(path);
	return 0;
}

int PskCommonHelper::CommonBindWndEx(Ifire* fire, long hwnd, LPCSTR display, LPCSTR mouse, LPCSTR keypad, LPCSTR public_desc, long mode) {
	int ret = fire->PskBindWndEx(hwnd, display, mouse, keypad, public_desc, mode);
	return ret;
}

int PskCommonHelper::CommonCapture(Ifire* fire, long x1, long y1, long x2, long y2, LPCSTR file) {
	return fire->PskCapture(x1, y1, x2, y2, file);
}

string PskCommonHelper::CommonFindPicE(Ifire* fire, long x1, long y1, long x2, long y2, LPCSTR pic_name, LPCSTR delta_color, double sim, long dir) {
	string ret = "";
	ret = fire->PskFindPicE(x1, y1, x2, y2, pic_name, delta_color, sim, dir);

	return ret;
}