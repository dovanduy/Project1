#ifndef QFLICENSE_H_
#define QFLICENSE_H_
#pragma comment(lib,"WebZCM.lib")

// 初始化DLL
int __stdcall InitDll(const char* token/*in*/, const char* proid/*in*/);
int __stdcall InitDllW(const wchar_t* token/*in*/, const wchar_t* proid/*in*/);

// 注册码登录，并自动验证有效期
unsigned int __stdcall LoginRegCodeAuto(const char* regcode/*in*/);
unsigned int __stdcall LoginRegCodeAutoW(const wchar_t* regcode/*in*/);
// 注册码登录 需要自己写心跳检测
unsigned int __stdcall LoginRegCode(const char* regcode/*in*/);
unsigned int __stdcall LoginRegCodeW(const wchar_t* regcode/*in*/);
// 注册码登录，并自动验证有效期
unsigned int __stdcall LoginRegCodeEx(const char* regcode,const char* remark);
unsigned int __stdcall LoginRegCodeExW(const wchar_t* regcode,const wchar_t* remark);
// 注册码登录 需要自己写心跳检测
unsigned int __stdcall LoginRegCodeAutoEx(const char* regcode,const char* remark);
unsigned int __stdcall LoginRegCodeAutoExW(const wchar_t* regcode,const wchar_t* remark);

// 试用登录
unsigned int __stdcall TryLogin();
unsigned int __stdcall TryLoginW();
// 获取试用的剩余时间
unsigned int __stdcall GetTryTime();
unsigned int __stdcall GetTryTimeW();

// 获取注册码详情
unsigned int __stdcall CheckRegCode(char* result/*out*/, unsigned int nMax/*in*/);
unsigned int __stdcall CheckRegCodeW(wchar_t* result/*out*/, unsigned int nMax/*in*/);
// 获取注册码的剩余时间
unsigned int __stdcall GetRegCodeTime();
unsigned int __stdcall GetRegCodeTimeW();
// 解绑
unsigned int __stdcall Ubind(const char* regcode/*in*/, const char* pwd/*in*/);
unsigned int __stdcall UbindW(const wchar_t* regcode/*in*/, const wchar_t* pwd/*in*/);
// 设置注册码的备注信息
unsigned int __stdcall SetRegCodeRemark(const char* remark/*in*/);
unsigned int __stdcall SetRegCodeRemarkW(const wchar_t* remark/*in*/);
// 获取注册码的备注内容
unsigned int __stdcall GetRegCodeRemark(char* result/*out*/, unsigned int nMax/*in*/);
unsigned int __stdcall GetRegCodeRemarkW(wchar_t* result/*out*/, unsigned int nMax/*in*/);
// 更新文件
int __stdcall UpdateFile(const char* version/*in*/);
int __stdcall UpdateFileW(const wchar_t* version/*in*/);
// 更新文件 扩展模式
unsigned int __stdcall UpdateFileEx(const char* version/*in*/, bool autoRun);
unsigned int __stdcall UpdateFileExW(const wchar_t* version/*in*/, bool autoRun);
// 获取项目公告
unsigned int __stdcall GetPlacard(char* result/*out*/, unsigned int nMax/*in*/);
unsigned int __stdcall GetPlacardW(wchar_t* result/*out*/, unsigned int nMax/*in*/);
// 发送监控信息
unsigned int __stdcall SendMonitorMsg(const char* name/*in*/, const char* msg/*in*/);
unsigned int __stdcall SendMonitorMsgW(const wchar_t* name/*in*/, const wchar_t* msg/*in*/);
// 获取自定义数据
unsigned int __stdcall GetCustom(const char* key/*in*/, char* result/*out*/, unsigned int nMax/*in*/);
unsigned int __stdcall GetCustomW(const wchar_t* key/*in*/, wchar_t* result/*out*/, unsigned int nMax/*in*/);
// 获取到错误信息详情
unsigned int __stdcall GetLastErrorInfo(char* result/*out*/, unsigned int nMax/*in*/);
unsigned int __stdcall GetLastErrorInfoW(wchar_t* result/*out*/, unsigned int nMax/*in*/);
// 获取到错误信息ID
unsigned int __stdcall GetLastErrorInfoID();
unsigned int __stdcall GetLastErrorInfoIDW();
// 获取到DLL版本号
unsigned int __stdcall PluginVersion(char *result/*out*/, unsigned int nMax/*in*/);
unsigned int __stdcall PluginVersionW(wchar_t *result/*out*/, unsigned int nMax/*in*/);
// 获取到注册码登录的访问令牌
unsigned int __stdcall GetRegCodeKey(char *result/*out*/, unsigned int nMax/*in*/);
unsigned int __stdcall GetRegCodeKeyW(wchar_t *result/*out*/, unsigned int nMax/*in*/);

// 使用扩展模式进行试用登录
unsigned int __stdcall TryLoginEx(char *result/*out*/, unsigned int nMax/*in*/);
unsigned int __stdcall TryLoginExW(wchar_t *result/*out*/, unsigned int nMax/*in*/);

// 对注册码进行充值
unsigned int __stdcall Charge(const char *newcard/*in*/, const char *oldcard/*in*/);
unsigned int __stdcall ChargeW(const wchar_t *newcard/*in*/, const wchar_t *oldcard/*in*/);

// 注册码退出登录
unsigned int __stdcall RegCodeLogOut();

// 设置机器码获取的模式
void __stdcall SetMachineMode(unsigned int flag/*in*/);
// 设置客户端信息
unsigned int __stdcall SetClientInfo(const char* remark/*in*/);
unsigned int __stdcall SetClientInfoW(const wchar_t* remark/*in*/);

//注册码系统通用通讯接口
int __stdcall CommonInterface(const char *arg,char* result,unsigned int nMax);
int __stdcall CommonInterfaceW(const wchar_t *arg,wchar_t* result,unsigned int nMax);

//下面为算法部分
// MD5算法
unsigned int __stdcall MD5(const char *str/*in*/, char* result/*out*/, unsigned int nMax/*in*/);
unsigned int __stdcall MD5W(const wchar_t *str/*in*/, wchar_t* result/*out*/, unsigned int nMax/*in*/);
// 获取机器码
unsigned int __stdcall GetMachinecode(char* result/*out*/, unsigned int nMax/*in*/);
unsigned int __stdcall GetMachinecodeW(wchar_t* result/*out*/, unsigned int nMax/*in*/);

//为客户端设置其他机器码
int _stdcall SetMachinecode(const char *arg);
int _stdcall SetMachinecodeW(const wchar_t *arg);

//让注册码相关的客户端下线
unsigned int __stdcall ClientOffline(const char * regcode,const char * machinecode);
unsigned int __stdcall ClientOfflineW(const wchar_t *str,const wchar_t * machinecode);

// AES加密
unsigned int __stdcall AesEncrypt(const char *str/*in*/, const char *key/*in*/, char* result/*out*/, unsigned int nMax/*in*/);
unsigned int __stdcall AesEncryptW(const wchar_t *str/*in*/, const wchar_t *key/*in*/, wchar_t* result/*out*/, unsigned int nMax/*in*/);
// AES解密
unsigned int __stdcall AesDecrypt(const char *str/*in*/,const char *key/*in*/,char* result/*out*/,unsigned int nMax/*in*/);
unsigned int __stdcall AesDecryptW(const wchar_t *str/*in*/,const wchar_t *key/*in*/,wchar_t* result/*out*/,unsigned int nMax/*in*/);
// DES 加密
unsigned int __stdcall DesEncrypt(const char *str/*in*/,const char *key/*in*/,char* result/*out*/,unsigned int nMax/*in*/);
unsigned int __stdcall DesEncryptW(const wchar_t *str/*in*/,const wchar_t *key/*in*/,wchar_t* result/*out*/,unsigned int nMax/*in*/);
// DES 解密
unsigned int __stdcall DesDecrypt(const char *str/*in*/,const char *key/*in*/,char* result/*out*/,unsigned int nMax/*in*/);
unsigned int __stdcall DesDecryptW(const wchar_t *str/*in*/,const wchar_t *key/*in*/,wchar_t* result/*out*/,unsigned int nMax/*in*/);
// Blowfish 加密
unsigned int __stdcall BlowfishEncrypt(const char *str/*in*/,const char *key/*in*/,char* result/*out*/,unsigned int nMax/*in*/);
unsigned int __stdcall BlowfishEncryptW(const wchar_t *str/*in*/,const wchar_t *key/*in*/,wchar_t* result/*out*/,unsigned int nMax/*in*/);
// Blowfish 解密
unsigned int __stdcall BlowfishDecrypt(const char *str/*in*/,const char *key/*in*/,char* result/*out*/,unsigned int nMax/*in*/);
unsigned int __stdcall BlowfishDecryptW(const wchar_t *str/*in*/,const wchar_t *key/*in*/,wchar_t* result/*out*/,unsigned int nMax/*in*/);
// TEA 加密
unsigned int __stdcall TeaEncrypt(const char *str/*in*/,const char *key/*in*/,char* result/*out*/,unsigned int nMax/*in*/);
unsigned int __stdcall TeaEncryptW(const wchar_t *str/*in*/,const wchar_t *key/*in*/,wchar_t* result/*out*/,unsigned int nMax/*in*/);
// TEA 解密
unsigned int __stdcall TeaDecrypt(const char *str/*in*/,const char *key/*in*/,char* result/*out*/,unsigned int nMax/*in*/);
unsigned int __stdcall TeaDecryptW(const wchar_t *str/*in*/,const wchar_t *key/*in*/,wchar_t* result/*out*/,unsigned int nMax/*in*/);
// RC2 加密
unsigned int __stdcall Rc2Encrypt(const char *str/*in*/,const char *key/*in*/,char* result/*out*/,unsigned int nMax/*in*/);
unsigned int __stdcall Rc2EncryptW(const wchar_t *str/*in*/,const wchar_t *key/*in*/,wchar_t* result/*out*/,unsigned int nMax/*in*/);
// RC2 解密
unsigned int __stdcall Rc2Decrypt(const char *str/*in*/,const char *key/*in*/,char* result/*out*/,unsigned int nMax/*in*/);
unsigned int __stdcall Rc2DecryptW(const wchar_t *str/*in*/,const wchar_t *key/*in*/,wchar_t* result/*out*/,unsigned int nMax/*in*/);
// RC5 加密
unsigned int __stdcall Rc5Encrypt(const char *str/*in*/,const char *key/*in*/,char* result/*out*/,unsigned int nMax/*in*/);
unsigned int __stdcall Rc5EncryptW(const wchar_t *str/*in*/,const wchar_t *key/*in*/,wchar_t* result/*out*/,unsigned int nMax/*in*/);
// RC5 解密
unsigned int __stdcall Rc5Decrypt(const char *str/*in*/,const char *key/*in*/,char* result/*out*/,unsigned int nMax/*in*/);
unsigned int __stdcall Rc5DecryptW(const wchar_t *str/*in*/,const wchar_t *key/*in*/,wchar_t* result/*out*/,unsigned int nMax/*in*/);
// RC6 加密
unsigned int __stdcall Rc6Encrypt(const char *str/*in*/,const char *key/*in*/,char* result/*out*/,unsigned int nMax/*in*/);
unsigned int __stdcall Rc6EncryptW(const wchar_t *str/*in*/,const wchar_t *key/*in*/,wchar_t* result/*out*/,unsigned int nMax/*in*/);
// RC6 解密
unsigned int __stdcall Rc6Decrypt(const char *str/*in*/,const char *key/*in*/,char* result/*out*/,unsigned int nMax/*in*/);
unsigned int __stdcall Rc6DecryptW(const wchar_t *str/*in*/,const wchar_t *key/*in*/,wchar_t* result/*out*/,unsigned int nMax/*in*/);



#endif