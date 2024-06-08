#pragma once

#include <QMainWindow>
#include "ui_InternalTransfer.h"

class InternalTransfer : public QMainWindow
{
	Q_OBJECT

public:
	InternalTransfer(QWidget *parent = nullptr);
	~InternalTransfer();

private:
	Ui::InternalTransferClass ui;
};
