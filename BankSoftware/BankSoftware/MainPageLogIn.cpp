#include "MainPageLogIn.h"
#include "NewClientSignUp.h"
#include "BankSoftware.h"
#include "ExternalTransfer.h"
#include "InternalTransfer.h"
#include "DeleteAccount.h"
#include <qmessagebox.h>
#include <qfile>


MainPageLogIn::MainPageLogIn(const QString& iban, const QString& name, const QString& surname, const QString& balance, const QString& password, QWidget* parent)
	: QMainWindow(parent),
	iban(iban),
	name(name),
	surname(surname),
	balance(balance),
	password(password)
{
	ui.setupUi(this);
	ui.label_name->setText(name);
	ui.label_surname->setText(surname);
	ui.label_balance->setText(balance);
	dataDisplay(iban);
	QString helpStr = QString::number(help);
	int balance_all = 0;
	QString helper;
	int size = howMuch() - 1;
	if (size >= 0) {
		QFile file("dane.txt");
		if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
			QTextStream stream(&file);
			QString line;
			QStringList fields;
			int i = 0;
			bool a = 0;
			while (!stream.atEnd()) {
				line = stream.readLine();
				fields = line.split(';');

				if (fields.size() >= 4) {
					QString name1 = fields[0];
					QString name2 = fields[1];
					QString name3 = fields[2];
					QString name4 = fields[3];

					bool ok;
					int balanceValue = name3.toInt(&ok);
					if (ok) {
						balance_all += balanceValue;
					}
					else {
						qWarning() << "Invalid balance value:" << name3;
					}

					ui.treeWidget->setColumnCount(5);
					QTreeWidgetItem* itm = new QTreeWidgetItem(ui.treeWidget);
					itm->setText(0, name1);
					itm->setText(1, name2);
					itm->setText(2, name3);
					itm->setText(3, name4);
					itm->setText(4, "Dates");
					if (i < help && a == 1) {
					
						itm->setText(4, daty[i]);
						i++;
					}
					ui.treeWidget->addTopLevelItem(itm);
					a = 1;
				}
				
			}
			file.close();
		}
	}

	helper = QString::number(balance_all);
	ui.label_balance_all->setText(helper);

	connect(ui.log_out_button, SIGNAL(clicked()), this, SLOT(logout_button_clicked()));
	connect(ui.pushButton_add_client, SIGNAL(clicked()), this, SLOT(add_client_button_clicked()));
	connect(ui.pushButton_internal, SIGNAL(clicked()), this, SLOT(internal_button_clicked()));
	connect(ui.pushButton_external, SIGNAL(clicked()), this, SLOT(external_button_clicked()));
	connect(ui.pushButton_remove_client, SIGNAL(clicked()), this, SLOT(remove_client()));
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

void MainPageLogIn::dataDisplay(QString iban) {

	QFile file("daty.txt");
	QTextStream stream(&file);
	if (file.open(QIODevice::ReadOnly)) {
		QString FileData;
		QString FileData_help;
		FileData_help = stream.readLine() + "\n";
		while (stream.atEnd() == false) {
			FileData = stream.readLine() + "\n";
			int j = 0;
			for (int i = 0; i < FileData.length(); i++) {

				if (FileData[i] == ';') {
					j++;
				}
				if (j == 2)
				{
					j = i + 1;
					break;
				}
			}
			
			std::vector<QChar> dates;
			for (int i = j; i < FileData.length()-1; i++)
			{
				dates.push_back(FileData[i]);
			}
			QString date;
			date.assign(dates.begin(), dates.end());
			std::vector<QChar> final_date;
			std::vector<QChar> final_date_second;
			
			for (int i = 0; i < 19; i++) {
				if (i < 10) {
					final_date.push_back(FileData[i]);
				}
				else if (i > 10) {
					final_date_second.push_back(FileData[i]);
				}
			}
			result.assign(final_date.begin(), final_date.end());
			daty.push_back(result);
			result2.assign(final_date_second.begin(), final_date_second.end());
			ui.label_date->setText(result);
			ui.label_date_2->setText(result2);				
			
			help++;
		}
	}

}

int MainPageLogIn::howMuch() {

	QFile file("daty.txt");
	int iterator = 0;
	QTextStream stream(&file);
	if (file.open(QIODevice::ReadOnly)) {
		QString FileData;
		QString FileData_help;
		FileData_help = stream.readLine() + "\n";
		while (stream.atEnd() == false) {
			FileData = stream.readLine() + "\n";
			iterator++;
		}
	}
	return iterator;
}


void MainPageLogIn::add_client_button_clicked() {
	NewClientSignUp* new_client = new NewClientSignUp();
	new_client->show();
	this->close();

}

void MainPageLogIn::internal_button_clicked() {

	InternalTransfer* new_client = new InternalTransfer(iban, name, surname, balance,password);
	new_client->show();
	this->close();

}

void MainPageLogIn::external_button_clicked() {

	ExternalTransfer* new_client = new ExternalTransfer(iban, name, surname, balance,password);
	new_client->show();
	this->close();

}

void MainPageLogIn::remove_client() {

	DeleteAccount* new_client = new DeleteAccount(iban, name, surname, balance,password);
	new_client->show();
	this->close();

}