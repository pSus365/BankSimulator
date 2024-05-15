#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_BankSoftware.h"

class BankSoftware : public QMainWindow
{
    Q_OBJECT

public:
    BankSoftware(QWidget *parent = nullptr);
    ~BankSoftware();

private:
    Ui::BankSoftwareClass ui;

private slots:
    void exit_button_clicked();
};
