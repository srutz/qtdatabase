#ifndef DATATABLE_H
#define DATATABLE_H

#include <QTableView>
#include <QWidget>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QSqlError>
#include <QLabel>
#include <vector>
#include <cmath>

using std::vector;

enum SortOrder { NONE = 0, ASC = 1, DESC = 2 };   

struct DataTableConfig {
    QString sql;
    vector<QVariant> params;
    qint64 page = 1;
    qint64 pageCount = 0;
    qint64 totalCount = 0;
    qint64 pageSize = 50;
    SortOrder sortOrder = SortOrder::NONE;
    QString sortColumn;
    
    void finalize() {
        // compute total count and then pageCount
        QString countSql = "SELECT COUNT(*) as C FROM (" + sql + ") AS count_query";
        QSqlQuery countQuery;
        countQuery.prepare(countSql);
        for (auto param : params) {
            countQuery.addBindValue(param);
        }
        auto result = countQuery.exec();
        if (!result) {
            qWarning() << "Error executing count query: " << countQuery.lastError().text();
            return;
        }
        if (countQuery.next()) {
            totalCount = countQuery.value(0).toInt();
            pageCount = ceil((double)totalCount / pageSize);
        } else {
            qWarning() << "Error fetching count query result: " << countQuery.lastError().text();
            totalCount = 0;
        }
    }
};

class DataTable : public QWidget
{
    Q_OBJECT

    QTableView *m_tableView;
    QLabel *m_label;
    DataTableConfig m_config;

public:
    DataTable(QWidget *parent = nullptr);
    virtual ~DataTable();

    const DataTableConfig& config() const;
    void setConfig(const DataTableConfig& config);
    void setPage(qint64 page, bool forced = false);

private slots:
    void handleHeaderClicked(int section);

signals:
    void configChanged(const DataTableConfig& config);
    void pageChanged(qint64 page);

};

#endif // DATATABLE_H