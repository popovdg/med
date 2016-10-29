#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSplitter>
#include <QTableView>
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlError>
#include <QMessageBox>

//Конструктор
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QSplitter *splitter = new QSplitter(this);
    splitter->setOrientation(Qt::Vertical);
    splitter->addWidget(ui->patientsBox);
    splitter->addWidget(ui->studiesBox);
    splitter->setChildrenCollapsible(false);
    ui->tableLayout->addWidget(splitter);

    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
    db.setDatabaseName("med");
    bool ok = db.open();

    if(!ok)
    {
        QMessageBox msgBox(this);
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setText(tr("Не удалось подключиться к базе данных!"));
        msgBox.setInformativeText(tr("Проверьте настройки сервера базы данных"));
        msgBox.setDetailedText(db.lastError().text());
        msgBox.exec();
        exit(0);
    }

    patientsModel = new QSqlTableModel(ui->patientsView, db);
    patientsModel->setTable("patients_view");
    patientsModel->setEditStrategy(QSqlTableModel::OnRowChange);
    patientsModel->setSort(1, Qt::AscendingOrder);
    patientsModel->select();
    patientsModel->setHeaderData(1, Qt::Horizontal, tr("ФИО"));
    patientsModel->setHeaderData(2, Qt::Horizontal, tr("Дата рождения"));
    patientsModel->setHeaderData(3, Qt::Horizontal, tr("Пол"));
    patientsModel->setHeaderData(4, Qt::Horizontal, tr("Вес"));
    patientsModel->setHeaderData(5, Qt::Horizontal, tr("Возраст"));
    ui->patientsView->setModel(patientsModel);
    ui->patientsView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->patientsView->hideColumn(0);
    ui->patientsView->selectRow(0);

    studiesModel = new QSqlTableModel(ui->studiesView, db);
    studiesModel->setTable("studies");
    studiesModel->setEditStrategy(QSqlTableModel::OnRowChange);
    studiesModel->setSort(2, Qt::DescendingOrder);
    studiesModel->select();
    studiesModel->setHeaderData(1, Qt::Horizontal, tr("Тип исследования"));
    studiesModel->setHeaderData(2, Qt::Horizontal, tr("Дата исследования"));
    ui->studiesView->setModel(studiesModel);
    ui->studiesView->hideColumn(0);

    connect(
      ui->patientsView->selectionModel(),
      SIGNAL(currentRowChanged(const QModelIndex &, const QModelIndex &)),
      SLOT(select_Studies(const QModelIndex &, const QModelIndex &))
     );
}

//Деструктор
MainWindow::~MainWindow()
{
    delete ui;
}

//Фильтрует исследования для выбранного клиента
void MainWindow::select_Studies(const QModelIndex &index, const QModelIndex &)
{
    studiesModel->setFilter("patient="
                            + (index.isValid() ? index.sibling(index.row(), 0).data().toString()
                                               : QString::number(0)));
    ui->removePersonButton->setEnabled(index.isValid());
    ui->addStudyButton->setEnabled(index.isValid());
}

//Фильтрует клиентов по ФИО
void MainWindow::search(const QString & string)
{
    patientsModel->setFilter(QString("fio ilike '%%1%'").arg(string));
}

//Обновляет данные из БД
void MainWindow::on_refershButton_clicked()
{
    patientsModel->select();
    studiesModel->select();
}

//Добавляет клиента
void MainWindow::on_addPersonButton_clicked()
{
}

//Удаляет выбранного клиента
void MainWindow::on_removePersonButton_clicked()
{
    QMessageBox msgBox(ui->patientsView);
    msgBox.setIcon(QMessageBox::Question);
    msgBox.setText(tr("Вы уверены, что хотите удалить выбранного клиента?"));
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::No);

    if(msgBox.exec() == QMessageBox::Yes)
    {
        patientsModel->removeRow(ui->patientsView->currentIndex().row());
        patientsModel->select();
    }
}

//Добавляет исследование
void MainWindow::on_addStudyButton_clicked()
{

}

//Удаляет выбранное исследование
void MainWindow::on_removeStudyButton_clicked()
{
    QMessageBox msgBox(ui->patientsView);
    msgBox.setIcon(QMessageBox::Question);
    msgBox.setText(tr("Вы уверены, что хотите удалить выбранное исследование?"));
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::No);

    if(msgBox.exec() == QMessageBox::Yes)
    {
        studiesModel->removeRow(ui->studiesView->currentIndex().row());
        studiesModel->select();
    }
}
