#include "ExternalTransfer.h"
#include "MainPageLogIn.h"
#include <qmessagebox>
#include <QFile>

ExternalTransfer::ExternalTransfer(const QString& iban, const QString& name, const QString& surname, const QString& balance, const QString& password, QWidget* parent)
    : QMainWindow(parent),
    iban(iban),
    name(name),
    surname(surname),
    balance(balance),
    password(password)
{
    ui.setupUi(this);

    connect(ui.log_out_button, SIGNAL(clicked()), this, SLOT(log_in_page()));
    connect(ui.pushButton_external, SIGNAL(clicked()), this, SLOT(confirm_tranfer()));
}

ExternalTransfer::~ExternalTransfer()
{
}

void ExternalTransfer::log_in_page() {

    MainPageLogIn* new_client = new MainPageLogIn(iban, name, surname, balance,password);
    new_client->show();
    this->close();


}

void ExternalTransfer::confirm_tranfer() {

    QString iban_needed = ui.lineEdit_iban->text();
    QString price = ui.lineEdit_price->text();
    QString password_needed = ui.lineEdit_password->text();
    QString swift = ui.lineEdit_swift->text();
    if (swift == "" || password_needed == "" || price == "" || iban_needed == "") {

        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setWindowTitle("Error");
        msgBox.setText("Prosze wypelnic wszystkie pola!");
        QPushButton* okButton = msgBox.addButton(QMessageBox::Ok);
        okButton->setStyleSheet("background-color: #d3d3d3; color: #000000;");
        msgBox.setStyleSheet("QMessageBox { background-color: #ffffff; color: #000000; }");
        msgBox.exec();

    }
    else {
        int iterator = 0;
        QString  balanceOf;
        QString name4, name5;
        QString helper1, helper2;
        if (password_needed == password) {
            bool check = 0;
            QFile file("dane.txt");
            QTextStream stream(&file);
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
                    helper1.assign(elo.begin(), elo.end());
                    std::vector<QChar> elo2;
                    int k = o + 1;
                    while (FileData[k] != ';') {
                        elo2.push_back(FileData[k]);
                        k++;
                    }
                    helper2.assign(elo2.begin(), elo2.end());
                    std::vector<QChar> elo3;
                    int x = k + 1;
                    while (FileData[x] != ';') {
                        elo3.push_back(FileData[x]);
                        x++;
                    }
                    balanceOf.assign(elo3.begin(), elo3.end());
                    std::vector<QChar> elo4;
                    int u = x + 1;
                    while (FileData[u] != ';') {
                        elo4.push_back(FileData[u]);
                        u++;
                    }
                    name4.assign(elo4.begin(), elo4.end());

                    std::vector<QChar> elo5;
                    int q = u + 1;
                    while (FileData[q] != '\n') {
                        elo5.push_back(FileData[q]);
                        q++;
                    }
                    name5.assign(elo5.begin(), elo5.end());
                    if (name5 == iban_needed) {
                        check = 1;
                        break;
                    }
                    iterator++;
                }

            }

            if (check) {
                int temp;
                bool ok;
                temp = swift.toInt(&ok);
                if (temp > 10'000'000 && temp < 99'999'999) {

                    bool ok;
                    int balanceOfInt = balanceOf.toInt(&ok);
                    bool ok2;
                    int priceInt = price.toInt(&ok2);
                    balanceOfInt += priceInt;
                    balanceOf = QString::number(balanceOfInt);
                    QString value = helper1 + ";" + helper2 + ";" + balanceOf + +";" + name4 + ";" + name5;
                    QFile file("dane.txt");
                    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
                        qCritical() << "Failed to open file for reading:" << file.errorString();
                        return;
                    }

                    QStringList lines;
                    QTextStream in(&file);
                    int currentLine = 0;
                    while (!in.atEnd()) {
                        QString line = in.readLine();
                        lines.append(line);
                        currentLine++;
                    }
                    file.close();


                    lines[iterator + 1] = value; 
                    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
                        qCritical() << "Failed to open file for writing:" << file.errorString();
                        return;
                    }

                    QTextStream out(&file);
                    for (const QString& line : lines) {
                        out << line << "\n";
                    }
                    file.close();

                    MainPageLogIn* new_client = new MainPageLogIn(iban, name, surname, balance, password);
                    new_client->show();
                    this->close();
                }
                else {
                    QMessageBox msgBox;
                    msgBox.setIcon(QMessageBox::Warning);
                    msgBox.setWindowTitle("Error");
                    msgBox.setText("Kod SWITF musi miec dokladnie 8 cyfr!");
                    QPushButton* okButton = msgBox.addButton(QMessageBox::Ok);
                    okButton->setStyleSheet("background-color: #d3d3d3; color: #000000;");
                    msgBox.setStyleSheet("QMessageBox { background-color: #ffffff; color: #000000; }");
                    msgBox.exec();
                }
            }
            else {
                QMessageBox msgBox;
                msgBox.setIcon(QMessageBox::Warning);
                msgBox.setWindowTitle("Error");
                msgBox.setText("Nie ma takiego rachunku IBAN w naszym banku!");
                QPushButton* okButton = msgBox.addButton(QMessageBox::Ok);
                okButton->setStyleSheet("background-color: #d3d3d3; color: #000000;");
                msgBox.setStyleSheet("QMessageBox { background-color: #ffffff; color: #000000; }");
                msgBox.exec();

            }

        }
        else {
            QMessageBox msgBox;
            msgBox.setIcon(QMessageBox::Warning);
            msgBox.setWindowTitle("Error");
            msgBox.setText("Wpisano zle haslo, sprobuj jeszcze raz");
            QPushButton* okButton = msgBox.addButton(QMessageBox::Ok);
            okButton->setStyleSheet("background-color: #d3d3d3; color: #000000;");
            msgBox.setStyleSheet("QMessageBox { background-color: #ffffff; color: #000000; }");
            msgBox.exec();
        }


    }


}
