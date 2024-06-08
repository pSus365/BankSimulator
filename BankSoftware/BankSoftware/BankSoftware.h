#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_BankSoftware.h"
#include <QTimer> 


class BankSoftware : public QMainWindow
{
    Q_OBJECT

public:
    BankSoftware(QWidget *parent = nullptr);
    ~BankSoftware();

private:
    Ui::BankSoftwareClass ui;
	QTimer* timer;
    QString iban;
    QString name;
    QString surname;
    QString balance;

private slots:
    void exit_button_clicked();
    void login_clock();
	void signup_button_clicked();
    void login_button_clicked();
    void switch_mode();
};

