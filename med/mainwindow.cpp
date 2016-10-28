#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSplitter>
#include <QTableView>
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlError>
#include <QSqlTableModel>

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
    db.setPort(5433);
    db.setDatabaseName("med");
    bool ok = db.open();

    QSqlTableModel *patientsModel = new QSqlTableModel(ui->patientsView, db);
    patientsModel->setTable("patients");
    patientsModel->setEditStrategy(QSqlTableModel::OnRowChange);
    patientsModel->select();
    patientsModel->setHeaderData(1, Qt::Horizontal, tr("ФИО"));
    patientsModel->setHeaderData(2, Qt::Horizontal, tr("Дата рождения"));
    patientsModel->setHeaderData(3, Qt::Horizontal, tr("Пол"));
    patientsModel->setHeaderData(4, Qt::Horizontal, tr("Вес"));
    ui->patientsView->setModel(patientsModel);
    ui->patientsView->hideColumn(0);

    QSqlTableModel *studiesModel = new QSqlTableModel(ui->studiesView, db);
    studiesModel->setTable("studies");
    studiesModel->setEditStrategy(QSqlTableModel::OnRowChange);
    studiesModel->select();
    studiesModel->setHeaderData(1, Qt::Horizontal, tr("Тип исследования"));
    studiesModel->setHeaderData(2, Qt::Horizontal, tr("Дата исследования"));
    ui->studiesView->setModel(studiesModel);
    ui->studiesView->hideColumn(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}
