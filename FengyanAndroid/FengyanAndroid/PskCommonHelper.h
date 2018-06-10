#pragma once
#include "CommonUtil.h"
#include "DMSoft.h"

class PskCommonHelper
{
public:
	PskCommonHelper();
	~PskCommonHelper();

	static int CommonReg(Ifire* fire, LPCSTR code, LPCSTR ver);
	static int CommonLClick(Ifire* fire);
	static int CommonMoveTo(Ifire* fire, long x, long y);
	static int CommonGuard(Ifire* fire, long en, LPCSTR type);
	static string CommonGetVer(Ifire* fire);
	static string CommonGetMachineCode(Ifire* fire);
	static int CommonSetPath(Ifire* fire, LPCSTR path);
	static int CommonBindWndEx(Ifire* fire, long hwnd, LPCSTR display, LPCSTR mouse, LPCSTR keypad, LPCSTR public_desc, long mode);
	static int CommonCapture(Ifire* fire, long x1, long y1, long x2, long y2, LPCSTR file);
	static string CommonFindPicE(Ifire* fire, long x1, long y1, long x2, long y2, LPCSTR pic_name, LPCSTR delta_color, double sim, long dir);
	static int CommonLeftDown(Ifire* fire);
	static int CommonLeftUp(Ifire* fire);
	static int CommonUnbindWindow(Ifire* fire);
	static int CommonRelease(Ifire* fire);

	static string CommonOcr(Ifire* fire, long x1,long y1,long x2,long y2,LPCSTR color,double sim);
	static int PskCommonHelper::CommonSetDict(Ifire* fire, long index, LPCSTR file);
};

