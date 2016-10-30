#ifndef ADDSTUDYDIALOG_H
#define ADDSTUDYDIALOG_H

#include <QDialog>

namespace Ui {
class AddStudyDialog;
}

class AddStudyDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddStudyDialog(QWidget *parent = 0);
    ~AddStudyDialog();

private:
    Ui::AddStudyDialog *ui;
};

#endif // ADDSTUDYDIALOG_H
