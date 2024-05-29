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

private slots:
	void sp_exit_button_clicked();
	void home_page_button_clicked();
	void access_accepted_greetings_page();
	void generate_password();
	void switch_mode();
};
