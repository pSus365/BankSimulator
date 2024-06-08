#include "MainPageLogIn.h"
#include "NewClientSignUp.h"
#include "BankSoftware.h"
#include "ExternalTransfer.h"
#include "InternalTransfer.h"
#include <qmessagebox.h>
#include <qfile>


MainPageLogIn::MainPageLogIn(const QString& iban, const QString& name, const QString& surname, const QString& balance, QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	ui.label_name->setText(name);
	ui.label_surname->setText(surname);
	ui.label_balance->setText(balance);
	dataDisplay(iban);
	int balance_all = 0;
	QString helper;
	int size = howMuch() - 1;
	QFile file("dane.txt");
	QTextStream stream(&file);
	QString name1, name2, name3,name4,name5;
	if (file.open(QIODevice::ReadOnly)) {
		QString FileData;
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
			name1.assign(elo.begin(), elo.end());
			std::vector<QChar> elo2;
			int k = o + 1;
			while (FileData[k] != ';') {
				elo2.push_back(FileData[k]);
				k++;
			}
			name2.assign(elo2.begin(), elo2.end());
			std::vector<QChar> elo3;
			int x = k + 1;
			while (FileData[x] != ';') {
				elo3.push_back(FileData[x]);
				x++;
			}
			name3.assign(elo3.begin(), elo3.end());
			bool ok;
			balance_all += name3.toInt(&ok);
			std::vector<QChar> elo4;
			int u = x + 1;
			while (FileData[u] != ';') {
				elo4.push_back(FileData[u]);
				u++;
			}
			name4.assign(elo4.begin(), elo4.end());
			ui.treeWidget->setColumnCount(5);
			QTreeWidgetItem* itm = new  QTreeWidgetItem(ui.treeWidget);
			itm->setText(0, name1);
			itm->setText(1, name2);
			itm->setText(2, name3);
			itm->setText(3, name4);
			itm->setText(4, result);
			ui.treeWidget->addTopLevelItem(itm);
		}
	}
	helper = QString::number(balance_all);
	ui.label_balance_all->setText(helper);
	connect(ui.log_out_button, SIGNAL(clicked()), this, SLOT(logout_button_clicked()));
	connect(ui.pushButton_add_client, SIGNAL(clicked()), this, SLOT(add_client_button_clicked()));
	connect(ui.pushButton_internal, SIGNAL(clicked()), this, SLOT(internal_button_clicked()));
	connect(ui.pushButton_external, SIGNAL(clicked()), this, SLOT(external_button_clicked()));
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
			if (date == iban) { // date == iban
				
				for (int i = 0; i < 19; i++) {
					if (i < 10) {
						final_date.push_back(FileData[i]);
					}
					else if (i > 10) {
						final_date_second.push_back(FileData[i]);
					}
				}
				result.assign(final_date.begin(), final_date.end());
				result2.assign(final_date_second.begin(), final_date_second.end());
				ui.label_date->setText(result);
				ui.label_date_2->setText(result2);
				break;
			}
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

	InternalTransfer* new_client = new InternalTransfer();
	new_client->show();

}

void MainPageLogIn::external_button_clicked() {

	ExternalTransfer* new_client = new ExternalTransfer();
	new_client->show();

}