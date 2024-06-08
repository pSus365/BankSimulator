#pragma once

#include <QMainWindow>
#include <QDir>
#include <QDebug>
#include <QString>
#include <QTextStream>
#include "ui_AccessAccepted.h"

class AccessAccepted : public QMainWindow
{
	Q_OBJECT

public:
	AccessAccepted(QWidget *parent = nullptr);
	~AccessAccepted();

private:
	Ui::AccessAcceptedClass ui;
	QString date;
	QString time;
private slots:
	void backToLoginPage();
	void display_account_number();
};
