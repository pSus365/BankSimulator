#include "NewClientSignUp.h"
#include "BankSoftware.h"

NewClientSignUp::NewClientSignUp(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
}

NewClientSignUp::~NewClientSignUp()
{}

void NewClientSignUp::sp_exit_button_clicked()
{
	close();
}

void NewClientSignUp::home_page_button_clicked()
{
	BankSoftware* bank_software = new BankSoftware();
	bank_software->show();
	this->close();
}
