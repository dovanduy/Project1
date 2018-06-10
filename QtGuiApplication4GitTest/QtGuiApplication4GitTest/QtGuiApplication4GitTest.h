#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QtGuiApplication4GitTest.h"

class QtGuiApplication4GitTest : public QMainWindow
{
	Q_OBJECT

public:
	QtGuiApplication4GitTest(QWidget *parent = Q_NULLPTR);

private:
	Ui::QtGuiApplication4GitTestClass ui;
};
