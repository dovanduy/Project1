#pragma once  
//#include <windows.h>   
#include <iostream>  
#include <fstream> 
#include <sstream> 
#include <comdef.h>
#include <vector>
#include <time.h>
#include <sys/timeb.h>  
#include <QTime>

#pragma comment ( lib, "imm32.lib" )
#include <windows.h>
#include <imm.h>

#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QtCore/QDebug>
#include <QSettings>
#include <QDatetime>
#pragma comment(lib, "winmm.lib ")

using namespace std;

class CommonUtil
{
public:
	CommonUtil();
	~CommonUtil();

public:
	 /*LPCSTR U2G(string string)
	{
		const char *utf8 = string.c_str();
		int len = MultiByteToWideChar(CP_UTF8, 0, utf8, -1, NULL, 0);
		wchar_t* wstr = new wchar_t[len + 1];
		memset(wstr, 0, len + 1);
		MultiByteToWideChar(CP_UTF8, 0, utf8, -1, wstr, len);
		len = WideCharToMultiByte(CP_ACP, 0, wstr, -1, NULL, 0, NULL, NULL);
		char* str = new char[len + 1];
		memset(str, 0, len + 1);
		WideCharToMultiByte(CP_ACP, 0, wstr, -1, str, len, NULL, NULL);
		if (wstr) delete[] wstr;
		return str;
	}*/
	static LPCSTR U2G(string string);
	static LPCSTR G2U(string gb2312);
	static std::string BSTR2STR(_bstr_t bstr);
	static long STR2Long(const char* arg);
	static std::vector<std::string> split(std::string str, std::string pattern);
	static std::string Long2STR(long l);
	static std::string getLogString(int count,const char* args, ...);
	static string CommonUtil::byteToHexStr(const unsigned char byte_arr[], int arr_len);
	static string CommonUtil::toHexString(const unsigned char* input, const int datasize);
	static string CommonUtil::ToHexString(const unsigned char* input, const int datasize);
	static string combinString(string arg1, string arg2);
	static string getTimeStamp();
	static string CommonUtil::getTimeFrom1970();
	static LPCWSTR CommonUtil::stringToLPCWSTR(std::string orig);
	static string&   replace_all(string&   str, const   string&   old_value, const   string&   new_value);
	static void CommonUtil::readTxt(string strFileName, string& str);
	 //LPCSTR getCurrentPath()
	 //{
		// char buf[1000];
		// GetCurrentDirectory(1000, buf);  //得到当前工作路径

		// return buf;
	 //}

	static BOOL CALLBACK FindHwndFromPID(HWND hwnd, LPARAM lParam);
	static HWND CommonUtil::GetHwndFromPID(DWORD dwProcessId);
	static HWND CommonUtil::GetWindowHandleByPID(DWORD dwProcessID);
	static int CommonUtil::generateRandomNumber();
	static int CommonUtil::generateRandomNumberEx(int num);
	static int CommonUtil::Digit(int Number);
	static void CommonUtil::split(int Number, int count, int temprary);
	static char CommonUtil::GetKeyNum(int Finish_ID[]);
	static string CommonUtil::getIDNumber();
	static string CommonUtil::char2string1(char c);
	static string CommonUtil::char2string(char c);
	static QString CommonUtil::getRandomCNChar();
	static string CommonUtil::getRandomPhoneNumebr();

	static unsigned int CommonUtil::GetTimeStampByStr(const char* pDate);
	static unsigned int CommonUtil::getCurrentTimeInt();
	static string CommonUtil::getCurrentDateStr(int dayOffset);

	static void CommonUtil::upateGold(int windowIndex, int roleIndex, long gold);

	static int CommonUtil::calculateSingleWindow(int windowIndex);

	static BOOL CommonUtil::KillProcess(DWORD ProcessId);
	static string CommonUtil::ExeCmd(LPWSTR pszCmd);
	static LPSTR CommonUtil::string2LPSTR(string str);

	static void CommonUtil::setRandAlpabeticString(QString & randString);
	static void CommonUtil::setRandNumberString(QString & randString);
	static void CommonUtil::upateDWBGold(int windowIndex, int accountIndex, long gold);
};