#include "addstudydialog.h"
#include "ui_addstudydialog.h"

//Конструктор
AddStudyDialog::AddStudyDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddStudyDialog)
{
    ui->setupUi(this);
    ui->dateEdit->setMaximumDate(QDate::currentDate());
    ui->dateEdit->setDate(QDate::currentDate());
}

//Деструктор
AddStudyDialog::~AddStudyDialog()
{
    delete ui;
}

//Активирует кнопку "Добавить", если информация верна
void AddStudyDialog::onDataChanged()
{

}
