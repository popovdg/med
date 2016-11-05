#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "patientsitemdelegate.h"
#include "studiesitemdelegate.h"
#include "addpatientdialog.h"
#include "addstudydialog.h"
#include <QSplitter>
#include <QTableView>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QMessageBox>
#include <QDate>

//Конструктор
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
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

    ui->setupUi(this);
    QSplitter *splitter = new QSplitter(this);
    splitter->setOrientation(Qt::Vertical);
    splitter->addWidget(ui->patientsBox);
    splitter->addWidget(ui->studiesBox);
    splitter->setChildrenCollapsible(false);
    ui->tableLayout->addWidget(splitter);

    patientsModel = new QSqlTableModel(ui->patientsView, db);
    patientsModel->setTable("patients_view");
    patientsModel->setEditStrategy(QSqlTableModel::OnFieldChange);
    patientsModel->setSort(1, Qt::AscendingOrder);
    patientsModel->select();
    patientsModel->setHeaderData(1, Qt::Horizontal, tr("ФИО"));
    patientsModel->setHeaderData(2, Qt::Horizontal, tr("Дата рождения"));
    patientsModel->setHeaderData(3, Qt::Horizontal, tr("Пол"));
    patientsModel->setHeaderData(4, Qt::Horizontal, tr("Вес, кг"));
    patientsModel->setHeaderData(5, Qt::Horizontal, tr("Количество полных лет"));

    patientsFilterModel = new QSortFilterProxyModel(patientsModel);
    patientsFilterModel->setFilterCaseSensitivity(Qt::CaseInsensitive);
    patientsFilterModel->setSourceModel(patientsModel);
    patientsFilterModel->setFilterKeyColumn(1);
    ui->patientsView->setItemDelegate(new PatientsItemDelegate(ui->patientsView));
    ui->patientsView->setModel(patientsFilterModel);
    ui->patientsView->hideColumn(0);

    studiesModel = new QSqlTableModel(ui->studiesView, db);
    studiesModel->setTable("studies");
    studiesModel->setEditStrategy(QSqlTableModel::OnFieldChange);
    studiesModel->setSort(2, Qt::DescendingOrder);
    studiesModel->setFilter("patient=0");
    studiesModel->select();
    studiesModel->setHeaderData(1, Qt::Horizontal, tr("Тип"));
    studiesModel->setHeaderData(2, Qt::Horizontal, tr("Дата"));
    ui->studiesView->setItemDelegate(new StudiesItemDelegate(ui->studiesView));
    ui->studiesView->setModel(studiesModel);
    ui->studiesView->hideColumn(0);

    connect(
      ui->patientsView->selectionModel(),
      SIGNAL(selectionChanged(const QItemSelection &, const QItemSelection &)),
      SLOT(onPatientSelectionChanged(const QItemSelection &, const QItemSelection&))
     );

    connect(
      ui->studiesView->selectionModel(),
      SIGNAL(currentRowChanged(const QModelIndex &, const QModelIndex &)),
      SLOT(onCurrentStudyChanged(const QModelIndex &, const QModelIndex &))
     );

    connect(patientsFilterModel, SIGNAL(modelReset()), SLOT(onPatientsReset()));
    connect(studiesModel, SIGNAL(modelReset()), SLOT(onStudiesReset()));
    connect(patientsModel, SIGNAL(beforeUpdate(int, QSqlRecord &)), SLOT(onPatientUpdate(int, QSqlRecord &)));
    connect(studiesModel, SIGNAL(beforeUpdate(int, QSqlRecord &)), SLOT(onStudyUpdate(int, QSqlRecord &)));
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
void MainWindow::onCurrentStudyChanged(const QModelIndex &current, const QModelIndex &)
{
    ui->removeStudyButton->setEnabled(current.isValid());
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
    patientsFilterModel->setFilterWildcard(QString("*%1*").arg(string));
}

//Обновляет данные из БД
void MainWindow::on_refershButton_clicked()
{
    qApp->setOverrideCursor(Qt::WaitCursor);
    patientsModel->select();
    studiesModel->select();
    qApp->restoreOverrideCursor();
}

//Добавляет клиента
void MainWindow::on_addPatientButton_clicked()
{
    AddPatientDialog dlg(patientsModel, this);
    if(dlg.exec()) for(int i = 0; i < ui->patientsView->model()->rowCount(); ++i)
        if(ui->patientsView->model()->index(i, 0).data().toInt() == dlg.getId())
        {
            ui->patientsView->selectRow(i);
            ui->patientsView->scrollTo(ui->patientsView->model()->index(i, 0));
        }
}

//Добавляет исследование
void MainWindow::on_addStudyButton_clicked()
{
    AddStudyDialog(ui->patientsView->currentIndex()
                   .sibling(ui->patientsView->currentIndex().row(), 0)
                   .data().toInt(), studiesModel, this).exec();
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

//Проверяет корректность данных клиента перед обновлением
void MainWindow::onPatientUpdate(int row, QSqlRecord &record)
{
    if(record.value("fio").toString().isEmpty())
    {
        QMessageBox msgBox(this);
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setText(tr("Не заполнено имя клиента!"));
        msgBox.setInformativeText("Данные не сохранены.");
        msgBox.exec();
        patientsModel->revertRow(row);
        return;
    }

    QSqlQuery query(QString("select * from patients where fio = '%1' and dob = '%2'")
                    .arg(record.value("fio").toString())
                    .arg(record.value("dob").toDate().toString("yyyy-MM-dd")));

    if(query.size() > 0)
    {
        QMessageBox msgBox(this);
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setText(tr("Данный пациент уже существует!"));
        msgBox.exec();
        patientsModel->revertRow(row);
    }
}

//Проверяет корректность данных исследования перед обновлением
void MainWindow::onStudyUpdate(int row, QSqlRecord &record)
{
    if(record.value("type").toString().isEmpty())
    {
        QMessageBox msgBox(this);
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setText(tr("Не заполнен тип исследования!"));
        msgBox.setInformativeText("Данные не сохранены.");
        msgBox.exec();
        studiesModel->revertRow(row);
        return;
    }

    QSqlQuery query(QString("select * from studies where patient = %1 and type = '%2' and date = '%3'")
                    .arg(record.value("patient").toInt())
                    .arg(record.value("type").toString())
                    .arg(record.value("date").toDate().toString("yyyy-MM-dd")));

    if(query.size() > 0)
    {
        QMessageBox msgBox(this);
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setText(tr("Данное исследование уже существует!"));
        msgBox.exec();
        studiesModel->revertRow(row);
    }
}
