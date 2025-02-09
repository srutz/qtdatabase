#ifndef SETTINGS_H
#define SETTINGS_H

#include <QJsonObject>
#include <QJsonDocument>
#include <QFile>
#include <QApplication>
#include <optional>

using std::optional;

class Settings {
    public:        
        const QJsonObject& rootNode() { return m_rootNode; }        
        static Settings* instance() { return &m_instance; }
        optional<QString> get(const QString& key) {
            if (m_rootNode.contains(key)) {
                return m_rootNode[key].toString();
            }
            return {};
        }

    private:
        QJsonObject m_rootNode;

        Settings();
        static Settings m_instance;
};

#endif /* SETTINGS_H */

