#include "settings.h"
#include <QString>
#include <QTimer>
#include <QMessageBox>
#include <QApplication>

static QString SETTINGS_FILE = "qtdatabase-settings.json";

Settings Settings::m_instance;

Settings::Settings() {
    // Load settings from file
    QFile file(SETTINGS_FILE);
    if (!file.open(QIODevice::ReadOnly)) {
        QTimer::singleShot(0, [] {
            QMessageBox::critical(
                QApplication::activeWindow(),
                "Error",
                "Could not open settings file: " + SETTINGS_FILE + ".\n"
                "Exiting application."
            );
            QApplication::exit(1);
        }); 
        return;
    }

    auto data = file.readAll();
    auto doc = QJsonDocument::fromJson(data);
    m_rootNode = doc.object();
    file.close();
}