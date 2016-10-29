#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "patientsitemdelegate.h"
#include "studiesitemdelegate.h"
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

    QSplitter *splitter = new QSplitter(this);
    splitter->setOrientation(Qt::Vertical);
    splitter->addWidget(ui->patientsBox);
    splitter->addWidget(ui->studiesBox);
    splitter->setChildrenCollapsible(false);
    ui->tableLayout->addWidget(splitter);

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
    ui->patientsView->setItemDelegate(new PatientsItemDelegate(ui->patientsView));
    ui->patientsView->setModel(patientsModel);
    ui->patientsView->hideColumn(0);

    studiesModel = new QSqlTableModel(ui->studiesView, db);
    studiesModel->setTable("studies");
    studiesModel->setEditStrategy(QSqlTableModel::OnRowChange);
    studiesModel->setSort(2, Qt::DescendingOrder);
    studiesModel->setFilter("patient=0");
    studiesModel->select();
    studiesModel->setHeaderData(1, Qt::Horizontal, tr("Тип"));
    studiesModel->setHeaderData(2, Qt::Horizontal, tr("Дата"));
    ui->studiesView->setModel(studiesModel);
    ui->studiesView->hideColumn(0);

    connect(
      ui->patientsView->selectionModel(),
      SIGNAL(selectionChanged(const QItemSelection &, const QItemSelection &)),
      SLOT(onPatientSelectionChanged(QItemSelection,QItemSelection))
     );

    connect(
      ui->studiesView->selectionModel(),
      SIGNAL(selectionChanged(const QItemSelection &, const QItemSelection &)),
      SLOT(onStudySelectionChanged(const QItemSelection &, const QItemSelection &))
     );

    connect(patientsModel, SIGNAL(modelReset()), SLOT(onPatientsReset()));
    connect(studiesModel, SIGNAL(modelReset()), SLOT(onStudiesReset()));
}

//Деструктор
MainWindow::~MainWindow()
{
    delete ui;
}

//Фильтрует исследования для выбранного клиента
void MainWindow::onPatientSelectionChanged(const QItemSelection &selected, const QItemSelection &)
{
    studiesModel->setFilter("patient="
                            + (selected.indexes().empty()
                               ? QString::number(0)
                               : selected.indexes().at(0).data().toString()));
    ui->removePatientButton->setDisabled(selected.indexes().empty());
    ui->addStudyButton->setDisabled(selected.indexes().empty());
}

//Активирует кнопку удаления исследования
void MainWindow::onStudySelectionChanged(const QItemSelection &selected, const QItemSelection &)
{
    ui->removeStudyButton->setDisabled(selected.indexes().empty());
}

//Деактивирует кнопки при изменении модели клиентов
void MainWindow::onPatientsReset()
{
    ui->removePatientButton->setEnabled(ui->patientsView->selectionModel()->hasSelection());
    ui->addStudyButton->setEnabled(ui->patientsView->selectionModel()->hasSelection());
    if(!ui->patientsView->selectionModel()->hasSelection()) studiesModel->setFilter("patient=0");
}

//Деактивирует кнопки при изменении модели исследований
void MainWindow::onStudiesReset()
{
    ui->removeStudyButton->setEnabled(ui->studiesView->selectionModel()->hasSelection());
}

//Фильтрует клиентов по ФИО
void MainWindow::search(const QString & string)
{
    patientsModel->setFilter(QString("fio ilike '%%1%'").arg(string));
}

//Обновляет данные из БД
void MainWindow::on_refershButton_clicked()
{
    qApp->setOverrideCursor(Qt::WaitCursor);
    patientsModel->select();
    studiesModel->select();
    qApp->restoreOverrideCursor();
}

//Добавляет исследование
void MainWindow::on_addStudyButton_clicked()
{

}

//Добавляет клиента
void MainWindow::on_addPatientButton_clicked()
{

}

//Удаляет выбранное исследование
void MainWindow::on_removeStudyButton_clicked()
{
    QMessageBox msgBox(ui->patientsView);
    msgBox.setIcon(QMessageBox::Question);
    msgBox.setText(tr("Удалить выбранное исследование?"));
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::No);

    if(msgBox.exec() == QMessageBox::Yes)
    {
        studiesModel->removeRow(ui->studiesView->currentIndex().row());
        studiesModel->select();
    }
}

//Удаляет выбранного клиента
void MainWindow::on_removePatientButton_clicked()
{
    QMessageBox msgBox(ui->patientsView);
    msgBox.setIcon(QMessageBox::Question);
    msgBox.setText(tr("Удалить информацию о выбраннм клиенте и всех его исследованиях?"));
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::No);

    if(msgBox.exec() == QMessageBox::Yes)
    {
        patientsModel->removeRow(ui->patientsView->currentIndex().row());
        patientsModel->select();
        studiesModel->select();
    }
}
