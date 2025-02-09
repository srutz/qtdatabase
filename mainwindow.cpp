
#include "mainwindow.h"
#include "settings.h"
#include "./ui_mainwindow.h"
#include "datatable.h"
#include <QJsonObject>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTextBrowser>
#include <QLabel>
#include <QTimer>
#include <QDebug>
#include <QMessageBox>
#include <QSplitter>
#include <QMargins>
#include <QFontDatabase>

static void initDatabase() {
    auto settings = Settings::instance();

    auto host = settings->get("database.host");
    auto name = settings->get("database.name");
    auto username = settings->get("database.username");
    auto password = settings->get("database.password");

    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName(host.value_or("localhost"));
    db.setDatabaseName(name.value_or("database"));
    db.setUserName(username.value_or("admin"));
    db.setPassword(password.value_or("password"));
    bool ok = db.open();
    qInfo() << "database connection status " << ok;

    if (!ok) {
        QMessageBox::critical(nullptr, "Database connection failed", "Could not connect to the database");
        exit(1);
    }
}


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initDatabase();
    auto layout = new QVBoxLayout(this->centralWidget());

    auto splitter = new QSplitter(Qt::Vertical, this);
    layout->addWidget(splitter, 1);

    auto dataTable = new DataTable(this);
    splitter->addWidget(dataTable);

    auto textBrowser = new QTextBrowser(this);
    auto fixedFont = QFontDatabase::systemFont(QFontDatabase::FixedFont);
    fixedFont.setPointSize(9);
    textBrowser->setFont(fixedFont);
    splitter->addWidget(textBrowser);


    QList<int> sizes;
    sizes << 500 << 50;
    splitter->setSizes(sizes);

    auto buttonsPanel = new QWidget(this);
    auto buttonsPanelLayout = new QHBoxLayout(buttonsPanel);
    buttonsPanelLayout->addStretch();
    buttonsPanelLayout->setContentsMargins(QMargins(0, 0, 0, 0));
    layout->addWidget(buttonsPanel);

    auto settings = Settings::instance()->rootNode();

    QTimer::singleShot(0, [dataTable,this] {
        DataTableConfig config({
            .sql = "SELECT * FROM information_schema.tables",
        });
        dataTable->setConfig(config);
    });

    connect(dataTable, &DataTable::configChanged, this, [textBrowser, settings](const DataTableConfig& config) {
        textBrowser->setPlainText(config.sql);
    });

    connect(ui->aboutAction, &QAction::triggered, this, [this] {
        QMessageBox::about(this, "About Database", "Perform paged queries on a Database Table into a TableView");
    });

    
}

MainWindow::~MainWindow()
{
    delete ui;
}
