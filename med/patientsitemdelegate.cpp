#include "patientsitemdelegate.h"

QWidget *PatientsItemDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if(index.column() == 5) return NULL;
    return QStyledItemDelegate::createEditor(parent, option, index);
}
