#pragma once

#include <QMainWindow>
#include "ui_ExternalTransfer.h"

class ExternalTransfer : public QMainWindow
{
	Q_OBJECT

public:
	ExternalTransfer(const QString& iban, const QString& name, const QString& surname, const QString& balance, const QString& password, QWidget* parent = nullptr);
	~ExternalTransfer();

private:
	Ui::ExternalTransferClass ui;
	QString iban;
	QString name;
	QString surname;
	QString balance;
	QString password;

private slots:
	void log_in_page();
	void confirm_tranfer();
		
};
