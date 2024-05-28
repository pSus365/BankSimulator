#include "BankSoftware.h"
#include "MainPageLogIn.h"
#include "NewClientSignUp.h"

#include <qmessagebox.h>
#include <QDateTime>


BankSoftware::BankSoftware(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

	timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(login_clock()));
	timer->start(1000);

    connect(ui.exit_button, SIGNAL(clicked()), this, SLOT(exit_button_clicked()));
	connect(ui.signup_button, SIGNAL(clicked()), this, SLOT(signup_button_clicked()));
	connect(ui.log_button, SIGNAL(clicked()), this, SLOT(login_button_clicked())); 

}

BankSoftware::~BankSoftware()
{}

void BankSoftware::exit_button_clicked()
{
	close();
}

void BankSoftware::login_clock()
{
	QTime time = QTime::currentTime();
	QString time_text = time.toString("hh:mm:ss");
	ui.time_display->setText(time_text);
}

void BankSoftware::signup_button_clicked()
{

	NewClientSignUp* new_client = new NewClientSignUp();
	new_client->show();
	this->close();

}
void BankSoftware::login_button_clicked()
{
	QString account_number = ui.line_edit_account_number->text();
	QString password = ui.line_edit_password->text();
	if(account_number == "" || password == "")
	{
		QMessageBox::warning(this, "Error", "Prosze wypelnic oba pola!");
	}
	else if (account_number == "1" && password == "1") {
		MainPageLogIn* new_client = new MainPageLogIn();
		new_client->show();
		this->close();
	}
	else
	{
		QMessageBox::information(this, "Login", "Takie konto nie istnieje, kliknij zarejestruj sie aby dolaczyc do naszego banku!");
	}
	
}


