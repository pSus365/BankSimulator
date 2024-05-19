#include "BankSoftware.h"
#include "NewClientSignUp.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    BankSoftware w;
    w.show();
    return a.exec();
}
