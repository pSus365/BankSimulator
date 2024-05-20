#pragma once

#include <QMainWindow>
#include "ui_MainPageLogIn.h"

class MainPageLogIn : public QMainWindow
{
	Q_OBJECT

public:
	MainPageLogIn(QWidget *parent = nullptr);
	~MainPageLogIn();

private:
	Ui::MainPageLogInClass ui;
private slots:
	void logout_button_clicked();

};
