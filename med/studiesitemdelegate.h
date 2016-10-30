#ifndef STUDIESITEMDELEGATE_H
#define STUDIESITEMDELEGATE_H

#include <QStyledItemDelegate>


/** Делегат элементов таблицы исследований */
class StudiesItemDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:

    /** Конструктор */
    StudiesItemDelegate(QObject *parent = Q_NULLPTR) : QStyledItemDelegate(parent) {}

    /** Создаёт редактор элемениов */
    QWidget * createEditor(QWidget *, const QStyleOptionViewItem &, const QModelIndex &) const Q_DECL_OVERRIDE;
};

#endif // STUDIESITEMDELEGATE_H
