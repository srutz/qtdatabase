#include "datatable.h"
#include <QVBoxLayout>
#include <QHeaderView>
#include <utility>

using std::move;

DataTable::DataTable(QWidget *parent) : QWidget(parent) {

    auto mainLayout = new QVBoxLayout(this);
    m_tableView = new QTableView(this);
    mainLayout->addWidget(m_tableView, 1);
}

DataTable::~DataTable() {
    
}

void DataTable::setConfig(const DataTableConfig& config) {
    m_config = config;

    auto oldModel = dynamic_cast<QSqlQueryModel*>(m_tableView->model());
    if (oldModel) {
        delete oldModel;
    }   
    auto model = new QSqlQueryModel(this);
    QSqlQuery query(config.sql);
    for (auto param : config.params) {
        query.addBindValue(param);
    }
    model->setQuery(std::move(query));
    m_tableView->setModel(model);

    //m_tableView->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    //m_tableView->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    //m_tableView->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);
}
