#include "FengyanAndroid.h"
#include "MainFrame.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);


	FengyanAndroid *w = new FengyanAndroid();
	MainFrame main;
	//main->hide();
	w->show();
	w->activateWindow();
	//w->hide();

	QObject::connect(w, SIGNAL(showmainwindow()), &main, SLOT(receivelogin()));

	int result = a.exec();

	return result;
}
