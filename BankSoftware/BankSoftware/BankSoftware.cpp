#include "BankSoftware.h"

BankSoftware::BankSoftware(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    connect(ui.exit_button, SIGNAL(clicked()), this, SLOT(exit_button_clicked()));
}

BankSoftware::~BankSoftware()
{}

void BankSoftware::exit_button_clicked()
{
	close();
}