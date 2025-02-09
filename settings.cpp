#include "settings.h"
#include <QString>
#include <QTimer>
#include <QFile>
#include <QDir>
#include <QFileInfo>
#include <QMessageBox>
#include <QApplication>
#include <QTimer>

static QString SETTINGS_FILE = "qtdatabase-settings.json";

Settings Settings::m_instance;

Settings::Settings() {
    // Load settings from file relative to home directory
    auto absolutePath = QDir::homePath() + QDir::separator() + SETTINGS_FILE;
    QFile file(absolutePath);
    if (!file.open(QIODevice::ReadOnly)) {
        QTimer::singleShot(0, [absolutePath] {
            QMessageBox::critical(
                QApplication::activeWindow(),
                "Error",
                "Could not open settings file: " + SETTINGS_FILE + "\n"
                " at: " + absolutePath + "\n"
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