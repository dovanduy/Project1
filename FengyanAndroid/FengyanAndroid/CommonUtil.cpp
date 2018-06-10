#include "CommonUtil.h"
#define FBLOCK_MAX_BYTES 1024

CommonUtil::CommonUtil()
{

}

CommonUtil::~CommonUtil()
{

}


 string CommonUtil::toHexString(const unsigned char* input, const int datasize)

{
	string output;
	char ch[3];

	for (int i = 0; i < datasize; ++i)
	{
		sprintf_s(ch, 3, "%02x", input[i]);
		output += ch;
	}
	return output;
}
string CommonUtil::ToHexString(const unsigned char* input, const int datasize)
{
	char  output[33];
	for (int j = 0; j < datasize; j++)
	{
		unsigned char b = *(input + j);
		sprintf_s(output + j * 2, 3, "%02x", b);
	}
	return string(output);
}

string CommonUtil::getTimeStamp()
{
	time_t curtime = time(NULL);
	tm *ptm = localtime(&curtime);
	char buf[64];
	sprintf(buf, "%d/%02d/%02d %02d:%02d:%02d", ptm->tm_year + 1900, ptm->tm_mon + 1,
		ptm->tm_mday, ptm->tm_hour, ptm->tm_min, ptm->tm_sec);
	std::cout << buf << std::endl;
	return buf;
}

LPCWSTR CommonUtil::stringToLPCWSTR(std::string orig)
{
	/*size_t origsize = orig.length() + 1;
	size_t convertedChars = 0;
	wchar_t *wcstring = (wchar_t *)malloc(sizeof(wchar_t)*(orig.length() - 1));
	mbstowcs_s(&convertedChars, wcstring, origsize, orig.c_str(), _TRUNCATE);*/

	size_t size = orig.length();

	wchar_t *buffer = new wchar_t[size + 1];

	MultiByteToWideChar(CP_ACP, 0, orig.c_str(), size, buffer, size * sizeof(wchar_t));

	buffer[size] = 0;  // 确保以 '\0' 结尾 
	return buffer;
}

string CommonUtil::getTimeFrom1970()
{
	long long time_last;
	time_last = time(NULL);     //总秒数  
	struct timeb t1;
	ftime(&t1);

	char buf[64];

	sprintf(buf, "%lld", t1.time * 1000 + t1.millitm);
	return buf;
}

string CommonUtil::byteToHexStr(const unsigned char byte_arr[], int arr_len)
{
	string  hexstr;
	for (int i = 0; i<arr_len; i++)
	{
		char hex1;
		char hex2;
		int value = byte_arr[i];
		int v1 = value / 16;
		int v2 = value % 16;

		if (v1 >= 0 && v1 <= 9)
			hex1 = (char)(48 + v1);
		else
			hex1 = (char)(55 + v1);


		if (v2 >= 0 && v2 <= 9)
			hex2 = (char)(48 + v2);
		else
			hex2 = (char)(55 + v2);

		hexstr = hexstr + hex1 + hex2;
	}
	return hexstr;
}

LPCSTR  CommonUtil::G2U(string string)
{
	const char *gb2312 = string.c_str();
	int len = MultiByteToWideChar(CP_ACP, 0, gb2312, -1, NULL, 0);
	wchar_t* wstr = new wchar_t[len + 1];
	memset(wstr, 0, len + 1);
	MultiByteToWideChar(CP_ACP, 0, gb2312, -1, wstr, len);
	len = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, NULL, 0, NULL, NULL);
	char* str = new char[len + 1];
	memset(str, 0, len + 1);
	WideCharToMultiByte(CP_UTF8, 0, wstr, -1, str, len, NULL, NULL);
	if (wstr) delete[] wstr;
	return str; 
}

string&  CommonUtil::replace_all(string&   str, const   string&   old_value, const   string&   new_value)
{
	while (true) {
		string::size_type   pos(0);
		if ((pos = str.find(old_value)) != string::npos)
			str.replace(pos, old_value.length(), new_value);
		else   break;
	}
	return   str;
}

LPCSTR CommonUtil::U2G(string string)
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
}

//只适用于数字转换
string CommonUtil::BSTR2STR(_bstr_t bstr)
{
	const char *buf = bstr;

	long l = atol(buf);


	char s[1024];
	string str;
	ltoa(l, s, 1024);//这是在windows下使用的函数
	str = s;

	return str;
}

string CommonUtil::Long2STR(long l)
{

	char s[10];
	string str;
	ltoa(l, s, 10);//这是在windows下使用的函数
	str = s;

	return str;
}

long CommonUtil::STR2Long(const char* arg)
{

	long l = atol(arg);

	return l;
}

std::vector<std::string> CommonUtil::split(std::string str, std::string pattern)
{
	std::string::size_type pos;
	std::vector<std::string> result;
	str += pattern;//扩展字符串以方便操作
	int size = str.size();

	for (int i = 0; i<size; i++)
	{
		pos = str.find(pattern, i);
		if (pos<size)
		{
			std::string s = str.substr(i, pos - i);
			result.push_back(s);
			i = pos + pattern.size() - 1;
		}
	}
	return result;
}

std::string CommonUtil::getLogString(int count,const char* args, ...){
	va_list ap;
	char temp[4096];
	string result;
	va_start(ap, args);
	for (int i = 1; i <= count; i++){
		result.append(args);
		//strcat_s(temp, args);
		args = va_arg(ap, const char *);
	}
		
		

	va_end(ap);
	return result;
}

std::string CommonUtil::combinString(string arg1, string arg2)
{
	string result;
	result.append(arg1);
	result.append(arg2);

	return G2U(result);
}

void CommonUtil::readTxt(string strFileName, string& str)
{

	char szBuf[FBLOCK_MAX_BYTES];
	memset(szBuf, 0, sizeof(char) * FBLOCK_MAX_BYTES);


	FILE *fp;
	errno_t err;
	//Openforread(willfailiffile"crt_fopen_s.c"doesnotexist)
	err = fopen_s(&fp, strFileName.c_str(), "r");
	if (fp != NULL)
	{
		// UTF-8 file should offset 3 byte from start position.
		fseek(fp, 0, 0);
		while (fread(szBuf, sizeof(char), 1, fp) ==1)
		{
			str += G2U(szBuf);
			memset(szBuf, 0, sizeof(char) * 1);
		}
	}

	fclose(fp);

	//char txt[100];
	////string msg;
	//ifstream infile;
	//infile.open(strFileName);

	//if (!infile.is_open())
	//{
	//	return;
	//}

	//while (!infile.eof())
	//{
	//	infile.getline(txt, 100);
	//	//msg = UTF8ToGB(txt);
	//	//cout << msg << endl;
	//	str += txt;
	//}

	//infile.close();
}

HWND  g_hwnd;
int  g_nFound;
BOOL CALLBACK CommonUtil::FindHwndFromPID(HWND hwnd, LPARAM lParam)
{
	DWORD   dwPID2Find = (DWORD)lParam;
	DWORD   dwPID = 0;

	if (GetWindowThreadProcessId(hwnd, &dwPID))
	{
		if (dwPID == dwPID2Find)
		{
			g_hwnd = hwnd;
			return  (FALSE);
		}
	}

	return  (TRUE);
}

int CommonUtil::generateRandomNumber()
{
	qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));
	/*for (int i = 0; i<4; i++)
	{
		int test = qrand() % 10;
		qDebug() << test;
	}*/
	return qrand() % 4;
}

int CommonUtil::generateRandomNumberEx(int num)
{
	qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));
	/*for (int i = 0; i<4; i++)
	{
	int test = qrand() % 10;
	qDebug() << test;
	}*/
	return qrand() % num;
}

HWND CommonUtil::GetHwndFromPID(DWORD dwProcessId)
{
	g_hwnd = NULL;
	g_nFound = 0;

	EnumWindows(FindHwndFromPID, (LPARAM)dwProcessId);

	if (g_hwnd)  // we found one...
		return (g_hwnd);

	// nothing found :-(

	return (NULL);
}

HWND CommonUtil::GetWindowHandleByPID(DWORD dwProcessID)
{
	HWND h = GetTopWindow(0);
	while (h)
	{
		DWORD pid = 0;
		DWORD dwTheardId = GetWindowThreadProcessId(h, &pid);

		if (dwTheardId != 0)
		{
			if (pid == dwProcessID/*your process id*/)
			{
				// here h is the handle to the window
				return h;
			}
		}

		h = GetNextWindow(h, GW_HWNDNEXT);
	}

	return NULL;
}

void CommonUtil::setRandAlpabeticString(QString & randString) {
	srand((unsigned)time(NULL));
	int max = 6;
	QString tmp = QString("abcdefghijklmnopqrstuvwxyz");
	QString str = QString();
	QTime t;
	t = QTime::currentTime();
	qsrand(t.msec() + t.second() * 1000);
	for (int i = 0; i<max; i++) {
		int ir = rand() / (RAND_MAX / (tmp.length() - 1));
		str[i] = tmp.at(ir);
	}
	randString = str;
}

void CommonUtil::setRandNumberString(QString & randString) {
	srand((unsigned)time(NULL));
	int max = 3;
	QString tmp = QString("0123456789");
	QString str = QString();
	QTime t;
	t = QTime::currentTime();
	//int x = rand() / (RAND_MAX / (tmp.length() - 1));
	qsrand(t.msec() + t.second() * 1000);
	for (int i = 0; i<max; i++) {
		int ir = rand() / (RAND_MAX / (tmp.length() - 1));
		str[i] = tmp.at(ir);
	}
	randString = str;
}

int CommonUtil::Digit(int Number)
{
	int temprary = 1;
	int count = 0;
	while (1)
	{
		if (Number  <    temprary)
		{
			count++;
			goto outport;
		}
		else
		{
			temprary = temprary * 10;
			count++;
		}
	}
outport:
	count--;
	split(Number, count, temprary);
	return count;
}

int Finish_ID[20];
int l = 0;
void CommonUtil::split(int Number, int count, int temprary)
{
	
	int k = l;
	temprary = temprary / 10;
	for (l; l<k + count; l++)
	{
		if (temprary == 0) {
			return;
		}
		Finish_ID[l] = Number / temprary;

		
		Number = Number%temprary;
		temprary = temprary / 10;
	}
	return;
}

char CommonUtil::GetKeyNum(int Finish_ID[])
{
	char keyword;

	char Right_Val[20] = { '1','0','X','9','8','7','6','5','4','3','2' };

	int Cmp_ID[20] = { 7,9,10,5,8,4,2,1,6,3,7,9,10,5,8,4,2 };
	int Sum_ID = 0;
	int Temp_ID[20];//用来临时存储乘后数据  


	for (int i = 0; i<17; i++)
	{
		Temp_ID[i] = Cmp_ID[i] * Finish_ID[i];
	}

	for (int i = 0; i<17; i++)
	{
		Sum_ID = Sum_ID + Temp_ID[i];
	}

	Sum_ID = Sum_ID % 11;
	keyword = Right_Val[Sum_ID];
	return keyword;
}

string CommonUtil::getIDNumber() {
	srand((unsigned)time(NULL));
	l = 0;
	memset(Finish_ID, 0x0, 20 * sizeof(int));

	int Addr_ID;    //110000-659001  110000 + rand()%549001  

	int Year_ID;    //1900-1996     1900 + rand()%97  
	int Month_ID;   //01-12         1 + rand()%11  
	int Day_ID;     //01-28         1 + rand()%27  

	int Key_ID;     //100-999       100+rand()%899  

	int Cmp_ID;

	Addr_ID = (1 + rand() % 5) * 100000 + (1 + rand() % 2) * 10000; Digit(Addr_ID);
	Year_ID = 1900 + rand() % 97; Digit(Year_ID);
	Month_ID = 10 + rand() % 2; Digit(Month_ID);
	Day_ID = 10 + rand() % 17; Digit(Day_ID);
	Key_ID = 100 + rand() % 899; Digit(Key_ID);

	
	char keyword;
	keyword = GetKeyNum(Finish_ID);
	string temp = "";

	for (int i = 0; i<17; i++)
	{
		cout << Finish_ID[i];
		temp.append(char2string1(Finish_ID[i]));
	}

	temp.append(char2string(keyword));

	return temp;
}

string CommonUtil::char2string(char c) {
	string temp = "";
	stringstream stream;
	stream << c;
	temp = stream.str();

	string temp2;
	if (temp != "") {
		temp2 = temp.substr(1, 1);
	}
	else {
		temp2 = "";
	}

	int i = atol(temp.c_str());

	temp = Long2STR(i);
	/*if (i < 9) {
		temp = Long2STR(i);
	}
	else {
		temp = stream.str();
	}*/
	
	
	return temp;
}

string CommonUtil::char2string1(char c) {
	/*string temp = "";
	stringstream stream;
	stream << c;
	temp = stream.str();

	string temp2;
	if (temp != "") {
		temp2 = temp.substr(1, 1);
	}
	else {
		temp2 = "";
	}*/

	int i = int(c);

	string temp = Long2STR(i);
	/*if (i < 9) {
	temp = Long2STR(i);
	}
	else {
	temp = stream.str();
	}*/


	return temp;
}

QString CommonUtil::getRandomCNChar() {
	
	string temp = "";
	int a = 0;
	int b = 400;
	int random = (rand() % (b - a)) + a;

	QSettings configIniRead("config/ziku_config.ini", QSettings::IniFormat);
	configIniRead.setIniCodec("GB2312");
	QString path = "/ziku_config/";
	path.append(QString::number(random));
	QString zi = configIniRead.value(path).toString();

	qDebug() << zi;

	//const wchar_t * encodedName = reinterpret_cast<const wchar_t *>(zi.utf16());


	return zi;
}

string CommonUtil::getRandomPhoneNumebr() {
	srand((unsigned)time(NULL));
	string temp = "1";
	int a = 0;
	int b = 9;

	for (int i = 0; i < 10; i++) {
		int random = (rand() % (b - a)) + a;
		temp.append(Long2STR(random));
	}


	return temp;
}

string CommonUtil::getCurrentDateStr(int dayOffset) {
	/*string result = "";
	time_t t = time(0);
	char tmp[64];
	struct tm *local;
	local = localtime(&t);
	local->tm_mday = local->tm_mday + dayOffset;

	strftime(tmp, sizeof(tmp), "%Y-%m-%d", local);
	puts(tmp);
	result = tmp;
*/
	QDateTime time = QDateTime::currentDateTime();//获取系统现在的时间
	//time.addDays(dayOffset);
	QString str = time.addDays(dayOffset).toString("yyyy-MM-dd"); //设置显示格式


	return str.toStdString();
}

unsigned int CommonUtil::getCurrentTimeInt() {

	time_t curtime = time(NULL);
	tm *ptm = localtime(&curtime);
	return mktime(ptm);
}

unsigned int CommonUtil::GetTimeStampByStr(const char* pDate)
{
	const char* pStart = pDate;

	char szYear[5], szMonth[3], szDay[3], szHour[3], szMin[3], szSec[3];

	szYear[0] = *pDate++;
	szYear[1] = *pDate++;
	szYear[2] = *pDate++;
	szYear[3] = *pDate++;
	szYear[4] = 0x0;

	++pDate;

	szMonth[0] = *pDate++;
	szMonth[1] = *pDate++;
	szMonth[2] = 0x0;

	++pDate;

	szDay[0] = *pDate++;
	szDay[1] = *pDate++;
	szDay[2] = 0x0;

	++pDate;

	szHour[0] = *pDate++;
	szHour[1] = *pDate++;
	szHour[2] = 0x0;

	++pDate;

	szMin[0] = *pDate++;
	szMin[1] = *pDate++;
	szMin[2] = 0x0;

	++pDate;

	szSec[0] = *pDate++;
	szSec[1] = *pDate++;
	szSec[2] = 0x0;

	tm tmObj;

	tmObj.tm_year = atoi(szYear) - 1900;
	tmObj.tm_mon = atoi(szMonth) - 1;
	tmObj.tm_mday = atoi(szDay);
	tmObj.tm_hour = atoi(szHour);
	tmObj.tm_min = atoi(szMin);
	tmObj.tm_sec = atoi(szSec);
	tmObj.tm_isdst = -1;

	return mktime(&tmObj);
}

void CommonUtil::upateGold(int windowIndex, int roleIndex, long gold) {
	QString file = "logs/aaa";
	file.append(QString::number(windowIndex));
	file.append(".ini");

	QString single = "role";
	single.append(QString::number(roleIndex));
	QSettings settings(file, QSettings::IniFormat); // 当前目录的INI文件
													/* 区服设置 */
	settings.beginGroup("divided");
	settings.setValue(single, gold);
	settings.endGroup();
	return;
}

void CommonUtil::upateDWBGold(int windowIndex, int accountIndex, long gold) {
	QString file = "logs/aaa.ini";
	/*file.append(QString::number(windowIndex));
	file.append(".ini");*/


	QSettings settings(file, QSettings::IniFormat); // 当前目录的INI文件
													/* 区服设置 */
	settings.beginGroup("gold_sum");
	settings.setValue(QString::number(accountIndex), gold);
	settings.endGroup();
	return;
}

int CommonUtil::calculateSingleWindow(int windowIndex) {
	QString file = "logs/aaa";
	file.append(QString::number(windowIndex));
	file.append(".ini");

	QSettings configIniRead(file, QSettings::IniFormat);

	int totalGold = 0;

	for (int i = 0; i < 10; i++) {
		QString single = "/divided/role";
		single.append(QString::number(i+1));

		int singleGold = configIniRead.value(single).toInt();
		totalGold += singleGold;
	}

	QSettings settings(file, QSettings::IniFormat); // 当前目录的INI文件
													/* 区服设置 */
	settings.beginGroup("total");
	settings.setValue("all", totalGold);
	settings.endGroup();

	return totalGold;
}


BOOL CommonUtil::KillProcess(DWORD ProcessId)
{
	HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, ProcessId);
	if (hProcess == NULL)
		return FALSE;
	if (!TerminateProcess(hProcess, 0))
		return FALSE;
	return TRUE;
}

string CommonUtil::ExeCmd(LPWSTR pszCmd)
{
	//创建匿名管道
	SECURITY_ATTRIBUTES sa = { sizeof(SECURITY_ATTRIBUTES), NULL, TRUE };
	HANDLE hRead, hWrite;
	if (!CreatePipe(&hRead, &hWrite, &sa, 0))
	{
		return "";
	}

	//设置命令行进程启动信息(以隐藏方式启动命令并定位其输出到hWrite)
	STARTUPINFO si = { sizeof(STARTUPINFO) };
	GetStartupInfo(&si);
	si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;
	si.wShowWindow = SW_HIDE;
	si.hStdError = hWrite;
	si.hStdOutput = hWrite;

	//启动命令行
	PROCESS_INFORMATION pi;
	if (!CreateProcess(NULL, pszCmd, NULL, NULL, TRUE, NULL, NULL, NULL, &si, &pi))
	{
		return "";
	}

	//立即关闭hWrite
	CloseHandle(hWrite);

	//读取命令行返回值
	std::string strRet;
	char buff[1024] = { 0 };
	DWORD dwRead = 0;
	while (ReadFile(hRead, buff, 1024, &dwRead, NULL))
	{
		strRet.append(buff, dwRead);
	}
	CloseHandle(hRead);

	return strRet;
}
