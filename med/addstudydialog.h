#ifndef ADDSTUDYDIALOG_H
#define ADDSTUDYDIALOG_H

#include <QDialog>
#include <QSqlTableModel>

namespace Ui {
class AddStudyDialog;
}

/** Класс диалогового окна добавления нового исследования */
class AddStudyDialog : public QDialog
{
    Q_OBJECT

public:

    /** Конструктор */
    explicit AddStudyDialog(int, QSqlTableModel *, QWidget * = 0);

    /** Деструктор */
    ~AddStudyDialog();

private slots:
    /** Активирует кнопку "Добавить", если введена информация */
    void onDataChanged();

    /** Сохраняет введённые данные */
    void on_addButton_clicked();

private:
    Ui::AddStudyDialog *ui;
    QSqlTableModel *studiesModel; /**< Модель данных исследований */
    int patient; /**< Идентификатор пациента */
};

#endif // ADDSTUDYDIALOG_H
