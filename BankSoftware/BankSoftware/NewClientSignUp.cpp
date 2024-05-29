#include "NewClientSignUp.h"
#include "BankSoftware.h"
#include "AccessAccepted.h"
#include <qmessagebox.h>
#include <vector>
#include <random>
#include <set>

NewClientSignUp::NewClientSignUp(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	connect(ui.confirm_new_client_button, SIGNAL(clicked()), this, SLOT(access_accepted_greetings_page()));
	connect(ui.gen_password_button, SIGNAL(clicked()), this, SLOT(generate_password()));
	connect(ui.checkBox_password, SIGNAL(stateChanged(int)), this, SLOT(switch_mode()));
	


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
		QMessageBox msgBox;
		msgBox.setIcon(QMessageBox::Warning);
		msgBox.setWindowTitle("Error");
		msgBox.setText("Uzupelnij wszystkie pola!");
		QPushButton* okButton = msgBox.addButton(QMessageBox::Ok);
		okButton->setStyleSheet("background-color: #d3d3d3; color: #000000;");
		msgBox.setStyleSheet("QMessageBox { background-color: #ffffff; color: #000000; }");
		msgBox.exec();

	
		a = false;
	}
	if (a) 
	{
		
		QMessageBox msgBox;
		msgBox.setWindowTitle("Potwierdzenie");
		msgBox.setIcon(QMessageBox::Information);
		msgBox.setText("Czy dane napewno sa prawidlowo wpisane?");
		QPushButton* yesButton = msgBox.addButton(QMessageBox::Yes);
		yesButton->setStyleSheet("background-color: #d3d3d3; color: #000000;");
		QPushButton* noButton = msgBox.addButton(QMessageBox::No);
		noButton->setStyleSheet("background-color: #d3d3d3; color: #000000;");
		msgBox.setStyleSheet("QMessageBox { background-color: #ffffff; color: #000000; }");

	
		QMessageBox::StandardButton reply = static_cast<QMessageBox::StandardButton>(msgBox.exec());

		if (reply == QMessageBox::Yes)
		{
			AccessAccepted* new_client = new AccessAccepted();
			new_client->show();
			this->close();
		}
		
	//	msgBox.setStyleSheet("QMessageBox { background-color: #000000; color: #000000; }"
		//	"QPushButton { background-color: #0000000; color: #000000; border: 2px solid #000000; }");

		
	}
	
	
}
void NewClientSignUp::generate_password()
{
    int distinct = 12;
    int length = 12;

        std::vector<char> password;
        std::vector<char> differences;
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distr(61, 122);

        while (differences.size() < length)
        {
            char znak = distr(gen);
            differences.push_back(znak);
        }

        std::vector<char> kopiaNaWektor(differences.begin(), differences.end());

        int obecnyIndex = 0;
        for (int i = 0; i < distinct; i++)
        {
            password.push_back(kopiaNaWektor[obecnyIndex]);
            obecnyIndex = (obecnyIndex + 1) % length;
        }
        QLineEdit* lineEdit_password = ui.lineEdit_password;
        lineEdit_password->clear();
        for (int i = 0; i < password.size(); i++)
        {
            QString temp;
            temp = password[i];
            lineEdit_password->insert(temp);
        }


    

}
void NewClientSignUp::switch_mode() {
	QLineEdit* lineEditPassword = ui.lineEdit_password;

	if (lineEditPassword->echoMode() == QLineEdit::Normal) {
		lineEditPassword->setEchoMode(QLineEdit::Password);
	}
	else {
		lineEditPassword->setEchoMode(QLineEdit::Normal);
	}
}