#include "addstudydialog.h"
#include "ui_addstudydialog.h"

AddStudyDialog::AddStudyDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddStudyDialog)
{
    ui->setupUi(this);
}

AddStudyDialog::~AddStudyDialog()
{
    delete ui;
}
