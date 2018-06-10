#include "FengyanAndroid.h"

FengyanAndroid::FengyanAndroid(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	QObject::connect(ui.enterBtn, SIGNAL(clicked()), this, SLOT(enterBtnClicked()));

	QObject::connect(ui.unBindBtn, SIGNAL(clicked()), this, SLOT(unBindBtnClicked()));
	QObject::connect(ui.chongzhiBtn, SIGNAL(clicked()), this, SLOT(chongzhiBtnClicked()));

	QSettings configIniRead("config/code.ini", QSettings::IniFormat);
	QString value = configIniRead.value("/code_value/value").toString();
	int mode = configIniRead.value("/code_value/mode").toInt();

	ui.lineEdit->setText(value);
}

int FengyanAndroid::tokenVerify() {
	LPCSTR g_csBbyToken = "e1fca05a1aa8186d1407ce653e51a0f9";

	LPCSTR g_csProjName = "dwb";
	
	if (InitDll(g_csBbyToken, g_csProjName) == 0)
	{
		TCHAR buffer[1024] = { 0 };
		GetLastErrorInfoW(buffer, 1024);
		QMessageBox::information(NULL, "Error", QString::fromLocal8Bit("Token错误！"), QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
		return 0;
	}
	else {
		return 1;
	}


	return 0;
}

void FengyanAndroid::unBindBtnClicked() {

	qDebug() << "unBindBtnClicked";

	if (tokenVerify() == 0) {
		this->close();
		return;
	}
	QString value = ui.lineEdit->text();
	wstring g_csRegCode = value.toStdWString();
	LPCWSTR code = g_csRegCode.c_str();
	LPCWSTR pwd = L"";
	// 无密码解绑

	if (UbindW(code, pwd))
	{
		QMessageBox::information(NULL, "Success", QString::fromLocal8Bit("解绑成功！"), QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
	}
	else
	{
		TCHAR buffer[1024] = { 0 };
		GetLastErrorInfoW(buffer, 1024);
		QString msg = QString::fromWCharArray(buffer);
		/*::AfxMessageBox(_T("登录失败,原因：") + CString(buffer));*/
		QMessageBox::information(NULL, QString::fromLocal8Bit("解绑失败，原因是："), msg, QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
		return;
	}

}

void FengyanAndroid::chongzhiBtnClicked() {

	qDebug() << "chongzhiBtnClicked";

	if (tokenVerify() == 0) {
		this->close();
		return;
	}
	QString value = ui.lineEdit->text();
	wstring g_csRegCode = value.toStdWString();
	LPCWSTR code = g_csRegCode.c_str();
	LPCWSTR pwd = L"";
	// 无密码解绑
	QString newValue = ui.chongzhiLine->text();
	wstring newRegCode = newValue.toStdWString();
	LPCWSTR newCode = newRegCode.c_str();
	QApplication::setQuitOnLastWindowClosed(false);
	if (ChargeW(newCode, code))
	{
		//QMessageBox::information(NULL, "Title", QString::fromLocal8Bit("充值成功！"), QMessageBox::Yes);
		QMessageBox msgBox;
		msgBox.setText(QString::fromLocal8Bit("充值成功！"));
		msgBox.exec();
	}
	else
	{
		TCHAR buffer[1024] = { 0 };
		GetLastErrorInfoW(buffer, 1024);
		QString msg = QString::fromWCharArray(buffer);

		QMessageBox box(QMessageBox::Warning, QString::fromLocal8Bit("充值失败！"),
			msg);
		box.setStandardButtons(QMessageBox::Ok);
		box.exec();

	}
	QApplication::setQuitOnLastWindowClosed(true);
}

int FengyanAndroid::regCodeVerify() {

	QString value = ui.lineEdit->text();
	wstring g_csRegCode = value.toStdWString();
	LPCWSTR code = g_csRegCode.c_str();

	if (LoginRegCodeW(code))
	{
		QString file = "config/code.ini";
		QSettings settings(file, QSettings::IniFormat);
		settings.beginGroup("code_value");
		settings.setValue("value", value);
		
		settings.endGroup();


		return 1;
	}
	else
	{
		TCHAR buffer[1024] = { 0 };
		GetLastErrorInfoW(buffer, 1024);
		QString msg = QString::fromWCharArray(buffer);
		/*::AfxMessageBox(_T("登录失败,原因：") + CString(buffer));*/
		QMessageBox::information(NULL, "Error", msg, QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
		return 0;
	}

	return 0;
}


void FengyanAndroid::enterBtnClicked() {
	qDebug() << "enterBtnClicked";

	if (tokenVerify() == 0) {
		this->close();
		return;
	}

	if (regCodeVerify() == 0) {
		this->close();
		return;
	}

	QMessageBox box(QMessageBox::Warning, QString::fromLocal8Bit("警告！"),
		QString::fromLocal8Bit("<font size='6' color='red'>一.本软件完全出于个人兴趣爱好，由本人在业余时间开发，是一款安全，绿色，可靠的软件产品.<br>二.本软件宗旨在于解放双手，降低游戏沉迷，戒除网瘾。<br>三.严禁将本软件用于任何牟利的行为，若有此行为，本人将保留追究其民事以及刑事责任的权利。<br>四.因使用本软件而引致的任何意外、疏忽、合约毁坏、诽谤、版权或知识产权侵犯及其所造成的任何损失，本人概不负责，亦概不承担任何民事或刑事法律责任。<br>五.当你第一次开始使用本人所提供的任何软件及资源的那一刻起就将被视为对本声明全部内容的认可。同时您必须认可上述免责条款，方可使用本软件及资源。如有任何异议，建议立刻删除本软件及资源并且停止使用.<br>六.以上内容，本人保留最终解释权</font>"));
	box.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
	box.setButtonText(QMessageBox::Ok, QString::fromLocal8Bit("同意"));
	box.setButtonText(QMessageBox::Cancel, QString::fromLocal8Bit("不同意"));
	//box.exec();

	int ret = box.exec();
	switch (ret) {
	case QMessageBox::Ok: {
		//MainFrame* frame = new MainFrame(this);
		//frame->show();
		emit showmainwindow();
		this->hide();
		break;
	}

	case QMessageBox::Cancel:
		this->close();
		break;
	default:
		break;
	}

}