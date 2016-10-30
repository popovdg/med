#ifndef ADDSTUDYDIALOG_H
#define ADDSTUDYDIALOG_H

#include <QDialog>

namespace Ui {
class AddStudyDialog;
}

/** Класс диалогового окна добавления нового исследования */
class AddStudyDialog : public QDialog
{
    Q_OBJECT

public:

    /** Конструктор */
    explicit AddStudyDialog(QWidget *parent = 0);

    /** Деструктор */
    ~AddStudyDialog();

private slots:
    /** Активирует кнопку "Добавить", если информация верна */
    void onDataChanged();

private:
    Ui::AddStudyDialog *ui;
};

#endif // ADDSTUDYDIALOG_H
