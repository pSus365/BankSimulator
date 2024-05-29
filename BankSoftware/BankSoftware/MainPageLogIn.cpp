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
    QMessageBox msgBox;
    msgBox.setIcon(QMessageBox::Information);
    msgBox.setWindowTitle("Komunikat");
    msgBox.setText("Wylogowano pomyslnie!");
    QPushButton* okButton = msgBox.addButton(QMessageBox::Ok);
    okButton->setStyleSheet("background-color: #d3d3d3; color: #000000;");
    msgBox.setStyleSheet("QMessageBox { background-color: #ffffff; color: #000000; }");
    msgBox.exec();

	BankSoftware* mainWindow = new BankSoftware();
	mainWindow->show();
	this->close();

}