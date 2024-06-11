#include "BankSoftware.h"
#include "MainPageLogIn.h"
#include "NewClientSignUp.h"
#include <QString>
#include <unordered_map>
#include <qmessagebox.h>
#include <QDateTime>
#include <vector>


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
	connect(ui.checkBox_password, SIGNAL(stateChanged(int)), this, SLOT(switch_mode()));

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
	bool a = false;
	if (account_number == "1" && password == "1") {
	}
	else {
		std::vector<QChar> ourWord;
		for (int i = 0; i < password.length(); i++)
		{
			ourWord.push_back(password[i]);
		}
		ourWord.push_back(';');
		for (int i = 0; i < account_number.length(); i++)
		{
			ourWord.push_back(account_number[i]);
		}
		QString ourWordString = password + ';' + account_number;
		QFile file("dane.txt");
		QTextStream stream(&file);
		if (file.open(QIODevice::ReadOnly)) {
			QString FileData;
			QString name4;
			QString FileData_help;
			FileData_help = stream.readLine() + "\n";
			while (stream.atEnd() == false) {
				FileData = stream.readLine() + "\n";
				std::vector<QChar> elo;
				int o = 0;
				while (FileData[o] != ';') {
					elo.push_back(FileData[o]);
					o++;
				}
				name.assign(elo.begin(), elo.end());
				std::vector<QChar> elo2;
				int k = o + 1;
				while (FileData[k] != ';') {
					elo2.push_back(FileData[k]);
					k++;
				}
				surname.assign(elo2.begin(), elo2.end());
				std::vector<QChar> elo3;
				int x = k + 1;
				while (FileData[x] != ';') {
					elo3.push_back(FileData[x]);
					x++;
				}
				balance.assign(elo3.begin(), elo3.end());
				std::vector<QChar> elo4;
				int u = x + 1;
				while (FileData[u] != '\n') {
					elo4.push_back(FileData[u]);
					u++;
				}
				name4.assign(elo4.begin(), elo4.end());
				if (ourWordString == name4) {
					a = 1;
				
					break;
				}
			}
			
		}
	}
	if (account_number == "" || password == "")
	{
		QMessageBox msgBox;
		msgBox.setIcon(QMessageBox::Warning);
		msgBox.setWindowTitle("Error");
		msgBox.setText("Prosze wypelnic oba pola!");
		QPushButton* okButton = msgBox.addButton(QMessageBox::Ok);
		okButton->setStyleSheet("background-color: #d3d3d3; color: #000000;");
		msgBox.setStyleSheet("QMessageBox { background-color: #ffffff; color: #000000; }");
		msgBox.exec();
	}else if (account_number == "1" && password == "1") {
		name = "admin";
		surname = "admin";
		balance = "111111";
		MainPageLogIn* new_client = new MainPageLogIn(account_number,name,surname,balance,password);
		new_client->show();
		this->close();
	}
	else if (a) {
		QString iban = ui.line_edit_account_number->text();
		MainPageLogIn* new_client = new MainPageLogIn(iban,name, surname,balance,password);
		new_client->show();
		this->close();
	}
	else
	{
		QMessageBox msgBox;
		msgBox.setIcon(QMessageBox::Information);
		msgBox.setWindowTitle("Login");
		msgBox.setText("Takie konto nie istnieje, kliknij zarejestruj sie aby dolaczyc do naszego banku!");
		QPushButton* okButton = msgBox.addButton(QMessageBox::Ok);
		okButton->setStyleSheet("background-color: #d3d3d3; color: #000000;");
		msgBox.setStyleSheet("QMessageBox { background-color: #ffffff; color: #000000; }");
		msgBox.exec();

	}
	
}

void BankSoftware::switch_mode() {
	QLineEdit* lineEditPassword = ui.line_edit_password;

	if (lineEditPassword->echoMode() == QLineEdit::Normal) {
		lineEditPassword->setEchoMode(QLineEdit::Password);
	}
	else {
		lineEditPassword->setEchoMode(QLineEdit::Normal);
	}
}