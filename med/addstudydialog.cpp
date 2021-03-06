#include "addstudydialog.h"
#include "ui_addstudydialog.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>

//Конструктор
AddStudyDialog::AddStudyDialog(int id, QSqlTableModel * sqlTableModel, QWidget *parent) :
    QDialog(parent), ui(new Ui::AddStudyDialog), studiesModel(sqlTableModel), patient(id)
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

//Активирует кнопку "Добавить", если введена информация
void AddStudyDialog::onDataChanged()
{
    ui->addButton->setDisabled(ui->typeEdit->text().isEmpty());
}

//Сохраняет введённые данные
void AddStudyDialog::on_addButton_clicked()
{
    QSqlDatabase().transaction();
    QSqlQuery query(QString("select * from studies where patient = %1 and type = '%2' and date = '%3'")
                    .arg(patient).arg(ui->typeEdit->text()).arg(ui->dateEdit->date().toString("yyyy-MM-dd")));

    if(query.size() > 0)
    {
        ui->addButton->setDisabled(true);
        QMessageBox msgBox(this);
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setText(tr("Данное исследование уже существует!"));
        msgBox.exec();
        QSqlDatabase().commit();
    }
    else
    {
        if(query.exec(QString("insert into studies (patient, type, date) values(%1, '%2', '%3')")
                       .arg(patient).arg(ui->typeEdit->text()).arg(ui->dateEdit->date().toString("yyyy-MM-dd"))))
        {
            QSqlDatabase().commit();
            studiesModel->select();
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
