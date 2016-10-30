#include "addpatientdialog.h"
#include "ui_addpatientdialog.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>

//Конструктор
AddPatientDialog::AddPatientDialog(QSqlTableModel *sqlTableModel, QWidget *parent) :
    QDialog(parent), ui(new Ui::AddPatientDialog), patientsModel(sqlTableModel), id(0)
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
    QSqlDatabase().transaction();
    QSqlQuery query(QString("select * from patients where fio = '%1' and dob = '%2'")
                    .arg(ui->fioEdit->text()).arg(ui->dateEdit->date().toString("yyyy-MM-dd")));

    if(query.size() > 0)
    {
        ui->addButton->setDisabled(true);
        QMessageBox msgBox(this);
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setText(tr("Данный пациент уже существует!"));
        msgBox.exec();
        QSqlDatabase().commit();
    }
    else
    {
        if(query.exec(QString("insert into patients (fio, dob, sex, weight) values ('%1', '%2', '%3', %4) returning id")
                      .arg(ui->fioEdit->text())
                      .arg(ui->dateEdit->date().toString("yyyy-MM-dd"))
                      .arg(ui->menButton->isChecked())
                      .arg(ui->weightBox->value())))
        {
            QSqlDatabase().commit();
            if(query.next()) id = query.value(0).toInt();
            patientsModel->select();
            accept();
        }
        else
        {
            QMessageBox msgBox(this);
            msgBox.setIcon(QMessageBox::Critical);
            msgBox.setText(tr("Не удалось сохранить данные!"));
            msgBox.setDetailedText(query.lastError().text());
            msgBox.exec();
            QSqlDatabase().commit();
        }
    }
}
