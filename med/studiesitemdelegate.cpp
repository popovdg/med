#include "studiesitemdelegate.h"
#include <QDateEdit>

//Создаёт редактор элемениов
QWidget *StudiesItemDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    switch(index.column())
    {
    case 2:
    {
        QDateEdit *dateEdit = new QDateEdit(parent);
        dateEdit->setMaximumDate(QDate::currentDate());
        dateEdit->setDate(index.data().toDate());
        dateEdit->setCalendarPopup(true);
        return dateEdit;
    }
    default: return QStyledItemDelegate::createEditor(parent, option, index);
    }
}
