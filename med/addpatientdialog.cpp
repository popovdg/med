#include "addpatientdialog.h"
#include "ui_addpatientdialog.h"

//Конструктор
AddPatientDialog::AddPatientDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddPatientDialog)
{
    ui->setupUi(this);
    ui->dateEdit->setMaximumDate(QDate::currentDate());
}

//Деструктор
AddPatientDialog::~AddPatientDialog()
{
    delete ui;
}

//Активирует кнопку "Добавить", если информация верна
void AddPatientDialog::onDataChanged()
{

}
