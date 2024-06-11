#pragma once

#include <QMainWindow>
#include "ui_DeleteAccount.h"

class DeleteAccount : public QMainWindow
{
	Q_OBJECT

public:
	DeleteAccount(const QString& iban, const QString& name, const QString& surname, const QString& balance, const QString& password, QWidget* parent = nullptr);
	~DeleteAccount();

private:
	Ui::DeleteAccountClass ui;
	QString iban;
	QString name;
	QString surname;
	QString balance;
	QString password;
private slots:
	void delete_account();
	void back_to_log_in_page();
	void delete_date(QString iban_to_delete);
};
