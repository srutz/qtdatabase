#ifndef DATATABLE_H
#define DATATABLE_H

#include <QTableView>
#include <QWidget>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <vector>

using std::vector;

struct DataTableConfig {
    QString sql;
    vector<QVariant> params;
    long page = 1;
    long pageSize = 10;
};

class DataTable : public QWidget
{
    Q_OBJECT

    QTableView *m_tableView;
    DataTableConfig m_config;   

public:
    DataTable(QWidget *parent = nullptr);
    virtual ~DataTable();

    const DataTableConfig& config() const;
    void setConfig(const DataTableConfig& config);
};

#endif // DATATABLE_H
