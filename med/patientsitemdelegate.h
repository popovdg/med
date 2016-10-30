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
    QWidget * createEditor(QWidget *, const QStyleOptionViewItem &, const QModelIndex &) const Q_DECL_OVERRIDE;

    /** Сохраняет введённое значение */
    void setModelData(QWidget *, QAbstractItemModel *, const QModelIndex &) const Q_DECL_OVERRIDE;

    /** Отображает информацию в ячейках таблицы */
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const Q_DECL_OVERRIDE;
};

#endif // PATIENTSITEMDELEGATE_H
