#ifndef PATIENTSITEMDELEGATE_H
#define PATIENTSITEMDELEGATE_H

#include <QStyledItemDelegate>


class PatientsItemDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    PatientsItemDelegate(QObject *parent = Q_NULLPTR) : QStyledItemDelegate(parent) {}
};

#endif // PATIENTSITEMDELEGATE_H
