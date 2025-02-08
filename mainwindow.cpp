
#include "mainwindow.h"
#include "settings.h"
#include "./ui_mainwindow.h"
#include <QJsonObject>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTextBrowser>
#include <QLabel>
#include <QDebug>
#include <QScrollArea>
#include <QSplitter>
#include <QMargins>
#include <QFontDatabase>
#include <future>
#include <memory>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    auto layout = new QVBoxLayout(this->centralWidget());

    auto splitter = new QSplitter(Qt::Horizontal, this);
    layout->addWidget(splitter, 1);

    auto textBrowser = new QTextBrowser(this);
    auto fixedFont = QFontDatabase::systemFont(QFontDatabase::FixedFont);
    fixedFont.setPointSize(9);
    textBrowser->setFont(fixedFont);
    splitter->addWidget(textBrowser);

    auto dataTable = new QLabel("test");
    splitter->addWidget(dataTable);

    QList<int> sizes;
    sizes << 200 << 300;
    splitter->setSizes(sizes);

    auto buttonsPanel = new QWidget(this);
    auto buttonsPanelLayout = new QHBoxLayout(buttonsPanel);
    buttonsPanelLayout->addStretch();
    buttonsPanelLayout->setContentsMargins(QMargins(0, 0, 0, 0));
    layout->addWidget(buttonsPanel);

    auto settings = Settings::instance()->rootNode();
}

MainWindow::~MainWindow()
{
    delete ui;
}
