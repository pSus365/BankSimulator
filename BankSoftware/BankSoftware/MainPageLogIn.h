#pragma once

#include <QMainWindow>
#include "ui_MainPageLogIn.h"

class MainPageLogIn : public QMainWindow
{
	Q_OBJECT

public:
	MainPageLogIn(const QString& iban, const QString& name,const QString& surname, const QString& balance, const QString& password, QWidget *parent = nullptr);
	~MainPageLogIn();

private:
	Ui::MainPageLogInClass ui;
	QString iban;
	QString name;
	QString surname;
	QString balance;
	QString password;
	QString result, result2;
	std::vector<QString> daty;
	int help;
private slots:
	void logout_button_clicked();
	void dataDisplay(QString iban);
	int howMuch();
	void add_client_button_clicked();
	void internal_button_clicked();
	void external_button_clicked();
	void remove_client();

};
