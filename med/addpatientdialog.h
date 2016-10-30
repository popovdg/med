#ifndef ADDPATIENTDIALOG_H
#define ADDPATIENTDIALOG_H

#include <QDialog>

namespace Ui {
class AddPatientDialog;
}

/** Класс диалогового окна добавления нового клиента */
class AddPatientDialog : public QDialog
{
    Q_OBJECT

public:

    /** Конструктор */
    explicit AddPatientDialog(QWidget *parent = 0);

    /** Деструктор */
    ~AddPatientDialog();

private slots:

    /** Активирует кнопку "Добавить", если информация верна */
    void onDataChanged();

private:
    Ui::AddPatientDialog *ui;
};

#endif // ADDPATIENTDIALOG_H
