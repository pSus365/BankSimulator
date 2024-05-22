#pragma once

#include <QMainWindow>
#include "ui_AccessAccepted.h"

class AccessAccepted : public QMainWindow
{
	Q_OBJECT

public:
	AccessAccepted(QWidget *parent = nullptr);
	~AccessAccepted();

private:
	Ui::AccessAcceptedClass ui;
private slots:
	void backToLoginPage();
	void display_account_number();
};
