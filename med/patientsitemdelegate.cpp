#include "patientsitemdelegate.h"
#include <QSpinBox>
#include <QComboBox>
#include <QPainter>

//Конструктор
QWidget *PatientsItemDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    switch(index.column())
    {
    case 3:
    {
        QComboBox *comboBox = new QComboBox(parent);
        comboBox->addItems(QStringList() << "Мужской" << "Женский");
        comboBox->setCurrentIndex(index.data().toBool() ? 0 : 1);
        return comboBox;
    }

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

//Сохраняет введённое значение
void PatientsItemDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    if(index.column() == 3)
    {
        if(QComboBox *comboBox = qobject_cast<QComboBox*>(editor)) model->setData(index, !comboBox->currentIndex());
        else QStyledItemDelegate::setModelData(editor, model, index);
    }
    else QStyledItemDelegate::setModelData(editor, model, index);
}

//Отображает информацию в ячейках таблицы
void PatientsItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if(index.column() == 3) painter->drawText(option.rect, option.displayAlignment, index.data().toBool() ? tr("Мужской") : tr("Женский"));
    else QStyledItemDelegate::paint(painter, option, index);
}
