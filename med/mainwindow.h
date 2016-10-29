#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlTableModel>

namespace Ui {
class MainWindow;
}

/** Класс главного окна */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /** Конструктор */
    explicit MainWindow(QWidget *parent = 0);
    /** Деструктор */
    ~MainWindow();

private slots:
    /** Фильтрует исследования для выбранного клиента */
    void select_Studies(const QModelIndex &, const QModelIndex &);

    /** Фильтрует клиентов по ФИО */
    void search(const QString&);

    /** Обновляет данные из БД */
    void on_refershButton_clicked();

    /** Добавляет клиента */
    void on_addPersonButton_clicked();

    /** Удаляет выбранного клиента */
    void on_removePersonButton_clicked();

    /** Добавляет исследование */
    void on_addStudyButton_clicked();

    /** Удаляет выбранное исследование */
    void on_removeStudyButton_clicked();

private:
    Ui::MainWindow *ui;
    QSqlTableModel *patientsModel; /**< Модель данных клиентов */
    QSqlTableModel *studiesModel; /**< Модель данных исследований */
};

#endif // MAINWINDOW_H
