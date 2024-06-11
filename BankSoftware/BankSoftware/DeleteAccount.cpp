#include "DeleteAccount.h"
#include <QMessagebox>
#include <qfile>
#include "MainPageLogIn.h"

DeleteAccount::DeleteAccount(const QString& iban, const QString& name, const QString& surname, const QString& balance, const QString& password, QWidget* parent)
	: QMainWindow(parent),
	iban(iban),
	name(name),
	surname(surname),
	balance(balance),
	password(password)
{
	ui.setupUi(this);

	connect(ui.pushButton_delete_acc, SIGNAL(clicked()), this, SLOT(delete_account()));
	connect(ui.log_out_button, SIGNAL(clicked()), this, SLOT(back_to_log_in_page()));
}

DeleteAccount::~DeleteAccount()
{}


void DeleteAccount::delete_account(){

	QString iban_to_delete = ui.lineEdit_iban_to_delete->text();
	QString password_from_user = ui.lineEdit_password->text();
	bool is_aproved = ui.checkBox_aproved->isChecked();
	bool is_more_aproved = ui.checkBox_more_aproved->isChecked();
	if (is_aproved && is_more_aproved) {
		if (password_from_user == "" || iban_to_delete == "") {

			QMessageBox msgBox;
			msgBox.setIcon(QMessageBox::Warning);
			msgBox.setWindowTitle("Error");
			msgBox.setText("Uzupenij oba pola!");
			QPushButton* okButton = msgBox.addButton(QMessageBox::Ok);
			okButton->setStyleSheet("background-color: #d3d3d3; color: #000000;");
			msgBox.setStyleSheet("QMessageBox { background-color: #ffffff; color: #000000; }");
			msgBox.exec();

		}
		else if (iban_to_delete.length() != 8) {


			QMessageBox msgBox;
			msgBox.setIcon(QMessageBox::Warning);
			msgBox.setWindowTitle("Error");
			msgBox.setText("Numer IBAN musi miec 8 cyfr!");
			QPushButton* okButton = msgBox.addButton(QMessageBox::Ok);
			okButton->setStyleSheet("background-color: #d3d3d3; color: #000000;");
			msgBox.setStyleSheet("QMessageBox { background-color: #ffffff; color: #000000; }");
			msgBox.exec();
		}
		else {
			// tutaj sprawdzam czy taki iban istnieje
			if (password_from_user == password) {
				QMessageBox msgBox;
				msgBox.setWindowTitle("Potwierdzenie");
				msgBox.setIcon(QMessageBox::Information);
				msgBox.setText("Potwierdzam swiadomosc konsekwencji wiazacych sie z dezaktywacja i usunieciem konta bankowego");
				QPushButton* yesButton = msgBox.addButton(QMessageBox::Yes);
				yesButton->setStyleSheet("background-color: #d3d3d3; color: #000000;");
				QPushButton* noButton = msgBox.addButton(QMessageBox::No);
				noButton->setStyleSheet("background-color: #d3d3d3; color: #000000;");
				msgBox.setStyleSheet("QMessageBox { background-color: #ffffff; color: #000000; }");


				QMessageBox::StandardButton reply = static_cast<QMessageBox::StandardButton>(msgBox.exec());

				if (reply == QMessageBox::Yes)
				{
					QStringList lines;
					QFile file("dane.txt");
					if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
						QTextStream stream(&file);
						QString line;
						QStringList fields;
						while (!stream.atEnd()) {
							line = stream.readLine();
							fields = line.split(';');

							if (fields.size() >= 5) {
								QString name1 = fields[0];
								QString name2 = fields[1];
								QString name3 = fields[2];
								QString name4 = fields[3];
								QString name5 = fields[4];

								if (name5 != iban_to_delete) {
									lines.append(line);
								}
								
							}
						}
						file.close();
					}
					QFile outFile("dane.txt");
					if (!outFile.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
						qCritical() << "Failed to open file for writing:" << outFile.errorString();
						return;
					}

					QTextStream out(&outFile);
					for (const QString& line : lines) {
						out << line << "\n";
					}
					outFile.close();

					delete_date(iban_to_delete);


					MainPageLogIn* new_client = new MainPageLogIn(iban, name, surname, balance, password);
					new_client->show();
					this->close();
					
                }
			}
			else {
				QMessageBox msgBox;
				msgBox.setIcon(QMessageBox::Warning);
				msgBox.setWindowTitle("Error");
				msgBox.setText("Niepoprawne haslo!");
				QPushButton* okButton = msgBox.addButton(QMessageBox::Ok);
				okButton->setStyleSheet("background-color: #d3d3d3; color: #000000;");
				msgBox.setStyleSheet("QMessageBox { background-color: #ffffff; color: #000000; }");
				msgBox.exec();

			}

		}

	}
	else {
		QMessageBox msgBox;
		msgBox.setIcon(QMessageBox::Warning);
		msgBox.setWindowTitle("Error");
		msgBox.setText("Aby kontynuowac zaznacz puste pola");
		QPushButton* okButton = msgBox.addButton(QMessageBox::Ok);
		okButton->setStyleSheet("background-color: #d3d3d3; color: #000000;");
		msgBox.setStyleSheet("QMessageBox { background-color: #ffffff; color: #000000; }");
		msgBox.exec();
	}
}

void  DeleteAccount::back_to_log_in_page() {


	MainPageLogIn* new_client = new MainPageLogIn(iban, name, surname, balance, password);
	new_client->show();
	this->close();

}

void DeleteAccount::delete_date(QString iban_to_delete) {

	QStringList lines;
	QFile file("daty.txt");
	if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
		QTextStream stream(&file);
		QString line;
		QStringList fields;
		while (!stream.atEnd()) {
			line = stream.readLine();
			fields = line.split(';');

			if (fields.size() >= 3) {
				QString name1 = fields[0];
				QString name2 = fields[1];
				QString name3 = fields[2];
				if (name3 != iban_to_delete) {
					lines.append(line);
				}

			}
		}
		file.close();
	}
	QFile outFile("daty.txt");
	if (!outFile.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
		qCritical() << "Failed to open file for writing:" << outFile.errorString();
		return;
	}

	QTextStream out(&outFile);
	for (const QString& line : lines) {
		out << line << "\n";
	}
	outFile.close();

}