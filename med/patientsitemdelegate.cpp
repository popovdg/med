#include "patientsitemdelegate.h"
#include <QSpinBox>

QWidget *PatientsItemDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    switch(index.column())
    {
    //case 3: break;
    case 4:
    {
        QSpinBox *spinBox = new QSpinBox(parent);
        spinBox->setMinimum(1);
        return spinBox;
    }
    case 5: return NULL;
    default: return QStyledItemDelegate::createEditor(parent, option, index);
    }
}
