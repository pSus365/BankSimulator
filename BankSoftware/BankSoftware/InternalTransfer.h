#pragma once

#include <QMainWindow>
#include "ui_InternalTransfer.h"

class InternalTransfer : public QMainWindow
{
    Q_OBJECT

public:
    InternalTransfer(const QString& iban, const QString& name, const QString& surname, const QString& balance, const QString& password, QWidget* parent = nullptr);
    ~InternalTransfer();

private:
    Ui::InternalTransferClass ui;
    QString iban;
    QString name;
    QString surname;
    QString balance;
    QString password;

private slots:
    void log_in_page();
    void confirm_tranfer();
    void find_and_replace(QString iban_needed, QString price);
};
