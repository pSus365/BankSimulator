#include "MainPageLogIn.h"
#include "BankSoftware.h"
#include <qmessagebox.h>
MainPageLogIn::MainPageLogIn(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);


	connect(ui.log_out_button, SIGNAL(clicked()), this, SLOT(logout_button_clicked()));
}

MainPageLogIn::~MainPageLogIn()
{}


void MainPageLogIn::logout_button_clicked() {
	QMessageBox::information(this, "Komunikat", "Wylogowano pomyœlnie!");
	BankSoftware* mainWindow = new BankSoftware();
	mainWindow->show();
	this->close();

}