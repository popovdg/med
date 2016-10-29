#ifndef PATIENTSITEMDELEGATE_H
#define PATIENTSITEMDELEGATE_H

#include <QStyledItemDelegate>

/**  */
class PatientsItemDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:

    /** Конструктор */
    PatientsItemDelegate(QObject *parent = Q_NULLPTR) : QStyledItemDelegate(parent) {}

    /** Создаёт редактор элемениов */
    QWidget * createEditor(QWidget *, const QStyleOptionViewItem &, const QModelIndex &) const;
};

#endif // PATIENTSITEMDELEGATE_H
