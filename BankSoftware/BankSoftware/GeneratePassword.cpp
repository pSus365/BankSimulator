#include "GeneratePassword.h"
#include "NewClientSignUp.h"
#include <qmessagebox.h>
#include <QTimer>
#include <vector>
#include <random>
#include <set>

GeneratePassword::GeneratePassword(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
    connect(ui.gen_button, SIGNAL(clicked()), this, SLOT(generate_password()));
    connect(ui.bachk_button, SIGNAL(clicked()), this, SLOT(back_to_signup()));
}

GeneratePassword::~GeneratePassword()
{}


void GeneratePassword::generate_password() 
{
   
    
    QString lengthString, distinctString;
    lengthString = ui.lineEdit_length->text();
    distinctString = ui.lineEdit_distinct->text();
    bool ok;
    int distinct = lengthString.toInt(&ok);
    bool bok;
    int length = distinctString.toInt(&bok);
    if (lengthString == "" || distinctString == "")
    {
        QMessageBox::warning(this, "Error", "Prosze wypelnic oba pola!");
    }
    else {
        std::vector<char> password;
        std::set<char> rozneElementy;
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distr(97, 122);

        while (rozneElementy.size() < length)
        {
            char znak = distr(gen);
            rozneElementy.insert(znak);
        }

        std::vector<char> kopiaNaWektor(rozneElementy.begin(), rozneElementy.end());

        int obecnyIndex = 0;
        for (int i = 0; i < distinct; i++)
        {
            password.push_back(kopiaNaWektor[obecnyIndex]);
            obecnyIndex = (obecnyIndex + 1) % length;
        }
        QLineEdit* lineEdit_password = ui.lineEdit_result;
        lineEdit_password->clear();
        for (int i = 0; i < password.size(); i++)
        {
            QString temp;
            temp = password[i];
            lineEdit_password->insert(temp);
        }


    }
   
}
void GeneratePassword::back_to_signup()
{

    NewClientSignUp* new_client = new NewClientSignUp();
    new_client->show();
    this->close();
}