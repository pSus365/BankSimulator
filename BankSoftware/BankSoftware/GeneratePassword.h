#pragma once

#include <QMainWindow>
#include "ui_GeneratePassword.h"

class GeneratePassword : public QMainWindow
{
	Q_OBJECT

public:
	GeneratePassword(QWidget *parent = nullptr);
	~GeneratePassword();

private:
	Ui::GeneratePasswordClass ui;
private slots:
	void generate_password();
	void back_to_signup();
};
