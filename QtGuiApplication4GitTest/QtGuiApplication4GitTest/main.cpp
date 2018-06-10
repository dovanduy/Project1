#include "QtGuiApplication4GitTest.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QtGuiApplication4GitTest w;
	w.show();
	return a.exec();
}
