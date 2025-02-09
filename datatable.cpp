#include "datatable.h"
#include <QVBoxLayout>
#include <QSqlError>
#include <QSqlQuery>
#include <QHeaderView>
#include <QSqlQueryModel>
#include <QHBoxLayout>
#include <QPushButton>
#include <utility>

using std::move;

DataTable::DataTable(QWidget *parent) : QWidget(parent) {

    auto mainLayout = new QVBoxLayout(this);
    m_tableView = new QTableView(this);
    mainLayout->addWidget(m_tableView, 1);

    auto bottomLayout = new QHBoxLayout();
    mainLayout->addLayout(bottomLayout);
    m_label = new QLabel(this);
    bottomLayout->addWidget(m_label);
    bottomLayout->addStretch(1);
    auto prevButton = new QPushButton(this);
    prevButton->setIcon(QIcon::fromTheme("go-previous"));
    prevButton->setText("Prev");
    bottomLayout->addWidget(prevButton);
    connect(prevButton, &QPushButton::clicked, [this]() {
        if (m_config.page > 1) {
            setPage(m_config.page -1);
        }
    });

    auto nextButton = new QPushButton(this);
    nextButton->setIcon(QIcon::fromTheme("go-next"));
    nextButton->setText("Next");
    bottomLayout->addWidget(nextButton);
    connect(nextButton, &QPushButton::clicked, [this]() {
        if (m_config.page < m_config.pageCount) {
            setPage(m_config.page + 1);
        }
    });
}

DataTable::~DataTable() {
    
}

void DataTable::setConfig(const DataTableConfig& config) {
    m_config = config;
    m_config.finalize();

    auto oldModel = dynamic_cast<QSqlQueryModel*>(m_tableView->model());
    if (oldModel) {
        delete oldModel;
    }   
    auto model = new QSqlQueryModel(this);
    m_tableView->setModel(model);
    setPage(1, true);
    emit configChanged(m_config);
    emit pageChanged(m_config.page);
}

void DataTable::setPage(qint64 page, bool forced) {
    if (!forced && page == m_config.page) {
        return;
    }
    m_config.page = page;
    auto pagedSql = "SELECT * FROM (" 
        + m_config.sql + ") AS A1 LIMIT " 
        + QString::number(m_config.pageSize) + " OFFSET " 
        + QString::number((page - 1) * m_config.pageSize);

    QSqlQuery query;
    query.prepare(pagedSql);
    for (auto param : m_config.params) {
        query.addBindValue(param);
    }
   if (!query.exec()) {
        qDebug() << "Query execution error: " << query.lastError();
        return;
    }    
    auto model = dynamic_cast<QSqlQueryModel*>(m_tableView->model());
    model->setQuery(std::move(query));
    m_label->setText("Page: " + QString::number(m_config.page) + " of " + QString::number(m_config.pageCount));
    emit pageChanged(m_config.page);
    //m_tableView->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
}
