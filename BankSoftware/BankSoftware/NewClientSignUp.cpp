#include "NewClientSignUp.h"
#include "BankSoftware.h"
#include "AccessAccepted.h"
#include "GeneratePassword.h"
#include <qmessagebox.h>

NewClientSignUp::NewClientSignUp(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	connect(ui.confirm_new_client_button, SIGNAL(clicked()), this, SLOT(access_accepted_greetings_page()));
	connect(ui.gen_password_button, SIGNAL(clicked()), this, SLOT(generate_new_password()));

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


void NewClientSignUp::access_accepted_greetings_page()
{
	QString name, surname, balance, password;
	name = ui.lineEdit_name->text();
	surname = ui.lineEdit_surname->text();
	balance = ui.lineEdit_balance->text();
	password = ui.lineEdit_password->text();
	bool a = true;
	if (name == "" || surname == "" || balance == "" || password == "") 
	{
		QMessageBox::warning(this, "Error", "Uzupelnij wszystkie pola!");
		a = false;
	}
	if (a) 
	{
		QMessageBox::StandardButton reply = QMessageBox::question(this, "Potwierdzenie", "Czy dane napewno sa prawidlowo wpisane?", QMessageBox::Yes | QMessageBox::No);

		if (reply == QMessageBox::Yes)
		{
			AccessAccepted* new_client = new AccessAccepted();
			new_client->show();
			this->close();
		}
	}
	
	
}

void NewClientSignUp::generate_new_password()
{
	GeneratePassword* new_client = new GeneratePassword();
	new_client->show();
	this->close();
}