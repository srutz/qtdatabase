#ifndef SETTINGS_H
#define SETTINGS_H

#include <QJsonObject>
#include <QJsonDocument>
#include <QFile>
#include <QApplication>


class Settings {
    public:        
        const QJsonObject& rootNode() { return m_rootNode; }        
        static Settings* instance() { return &m_instance; }

    private:
        QJsonObject m_rootNode;

        Settings();
        static Settings m_instance;
};

#endif /* SETTINGS_H */

