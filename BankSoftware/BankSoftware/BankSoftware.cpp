#include "BankSoftware.h"
#include "NewClientSignUp.h"
#include <QDateTime>

BankSoftware::BankSoftware(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

	timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(login_clock()));
	timer->start(1000);

    connect(ui.exit_button, SIGNAL(clicked()), this, SLOT(exit_button_clicked()));
	connect(ui.signup_button, SIGNAL(clicked()), this, SLOT(new_client_button_clicked()));
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
