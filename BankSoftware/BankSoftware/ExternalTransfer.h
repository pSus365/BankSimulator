#pragma once

#include <QMainWindow>
#include "ui_ExternalTransfer.h"

class ExternalTransfer : public QMainWindow
{
	Q_OBJECT

public:
	ExternalTransfer(QWidget *parent = nullptr);
	~ExternalTransfer();

private:
	Ui::ExternalTransferClass ui;
};
