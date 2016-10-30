#ifndef ADDPATIENTDIALOG_H
#define ADDPATIENTDIALOG_H

#include <QDialog>
#include <QSqlTableModel>

namespace Ui {
class AddPatientDialog;
}

/** Класс диалогового окна добавления нового клиента */
class AddPatientDialog : public QDialog
{
    Q_OBJECT

public:

    /** Конструктор */
    explicit AddPatientDialog(QSqlTableModel *, QWidget * = 0);

    /** Деструктор */
    ~AddPatientDialog();

private slots:

    /** Активирует кнопку "Добавить", если введена информация */
    void onDataChanged();

    /** Сохраняет введённые данные */
    void on_addButton_clicked();

private:
    Ui::AddPatientDialog *ui;
    QSqlTableModel *patientsModel; /**< Модель данных клиентов */
};

#endif // ADDPATIENTDIALOG_H
