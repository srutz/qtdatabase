#ifndef QUERYTABLEMODEL_H
#define QUERYTABLEMODEL_H

#include <QObject>
#include <QAbstractTableModel>


class QueryTableModel : public QAbstractTableModel {
    Q_OBJECT

public:
    QueryTableModel(QObject *parent = nullptr) : QAbstractTableModel(parent) {}

    int rowCount(const QModelIndex &parent = QModelIndex()) const override { return N_ROWS;}
    int columnCount(const QModelIndex &parent = QModelIndex()) const override { return 3; }
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
private:
    static const int N_ROWS = 1000;
};

#endif // QUERYTABLEMODEL_H
