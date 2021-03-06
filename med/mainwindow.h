#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlTableModel>
#include <QItemSelection>
#include <QSortFilterProxyModel>

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
    void onPatientSelectionChanged(const QItemSelection &, const QItemSelection &);

    /** Активирует кнопки при изменении текущего клиента */
    void onCurrentStudyChanged(const QModelIndex &, const QModelIndex &);

    /** Деактивирует кнопки при изменении модели клиентов */
    void onPatientsReset();

    /** Деактивирует кнопки при изменении модели исследований */
    void onStudiesReset();

    /** Фильтрует клиентов по ФИО */
    void search(const QString &);

    /** Обновляет данные из БД */
    void on_refershButton_clicked();

    /** Добавляет исследование */
    void on_addStudyButton_clicked();

    /** Удаляет выбранное исследование */
    void on_removeStudyButton_clicked();

    /** Добавляет клиента */
    void on_addPatientButton_clicked();

    /** Удаляет выбранного клиента */
    void on_removePatientButton_clicked();

    /** Проверяет корректность данных клиента перед обновлением */
    void onPatientUpdate(int, QSqlRecord &);

    /** Проверяет корректность данных исследования перед обновлением */
    void onStudyUpdate(int, QSqlRecord &);

private:
    Ui::MainWindow *ui;
    QSortFilterProxyModel *patientsFilterModel; /**< Модель фильтрации клиентов */
    QSqlTableModel *patientsModel; /**< Модель данных клиентов */
    QSqlTableModel *studiesModel; /**< Модель данных исследований */
};

#endif // MAINWINDOW_H
