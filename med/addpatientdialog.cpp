#include "addpatientdialog.h"
#include "ui_addpatientdialog.h"
#include <QSqlQuery>
#include <QMessageBox>

//Конструктор
AddPatientDialog::AddPatientDialog(QSqlTableModel *sqlTableModel, QWidget *parent) :
    QDialog(parent), ui(new Ui::AddPatientDialog), patientsModel(sqlTableModel)
{
    ui->setupUi(this);
    ui->dateEdit->setMaximumDate(QDate::currentDate());
}

//Деструктор
AddPatientDialog::~AddPatientDialog()
{
    delete ui;
}

//Активирует кнопку "Добавить", если введена информация
void AddPatientDialog::onDataChanged()
{
    ui->addButton->setDisabled(ui->fioEdit->text().isEmpty());
}

//Сохраняет введённые данные
void AddPatientDialog::on_addButton_clicked()
{
    ui->addButton->setDisabled(true);

    QSqlQuery query(QString("select * from patients where fio = '%1' and dob = '%2'")
                    .arg(ui->fioEdit->text()).arg(ui->dateEdit->date().toString("yyyy-MM-dd")));

    if(query.size() > 0)
    {
        QMessageBox msgBox(this);
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setText(tr("Данный пациент уже существует!"));
        msgBox.exec();
    }
    else accept();
}
