#include "AccessAccepted.h"
#include "BankSoftware.h"
#include <random>
AccessAccepted::AccessAccepted(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	connect(ui.login_button_after_signup, SIGNAL(clicked()), this, SLOT(backToLoginPage()));
	display_account_number();
}

AccessAccepted::~AccessAccepted()
{}

void AccessAccepted::backToLoginPage()
{
	BankSoftware* returnToMainWindow = new BankSoftware();
	returnToMainWindow->show();
	this->close(); 
}

void AccessAccepted::display_account_number() 
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distr(10000000,99999999);
	QLabel* label_account_number = ui.label_account_number;
	for (int i = 0; i < 1; i++)
	{
		int num = distr(gen); 
		bool ok;
		QString second_temp = QString::number(num);
		label_account_number->setText(second_temp);

	}
		
}