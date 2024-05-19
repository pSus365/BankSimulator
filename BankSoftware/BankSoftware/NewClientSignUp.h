#pragma once

#include <QMainWindow>
#include "ui_NewClientSignUp.h"

class NewClientSignUp : public QMainWindow
{
	Q_OBJECT

public:
	NewClientSignUp(QWidget *parent = nullptr);
	~NewClientSignUp();

private:
	Ui::NewClientSignUpClass ui;
};
