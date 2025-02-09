
#include "querytablemodel.h"

QVariant QueryTableModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid() || role != Qt::DisplayRole)
        return QVariant();
    int row = index.row();
    int col = index.column();
    int number = row + 1;
    int square = number * number;
    int previousSquare = (number - 1) * (number - 1);
    switch (col)
    {
    case 0:
        return QString::number(number);
    case 1:
        return QString::number(square);
    case 2:
        return QString::number(square - previousSquare);
    default:
        return QVariant();
    }
}

QVariant QueryTableModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role != Qt::DisplayRole)
        return QVariant();
    if (orientation == Qt::Horizontal)
    {
        switch (section)
        {
        case 0:
            return QString("Number");
        case 1:
            return QString("Square");
        case 2:
            return QString("Delta Previous Square");
        default:
            return QVariant();
        }
    }
    return QVariant();
}