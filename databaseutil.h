#ifndef DATABASEUTIL_H
#define DATABASEUTIL_H

#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlField>
#include <QString>
#include <QVariant>
#include <vector>


struct User {
    QString name;
    QString email;

    static User fromQuery(QSqlQuery *q) {
        User r;
        r.name = q->value("name").toString();
        r.email = q->value("email").toString();
        return r;
    }

    QVariant getValue(const QString &key) {
        if (key == "name") {
            return this->name;
        } else if (key == "email") {
            return this->email;
        }
        return QVariant();
    }
};

struct Record {
    int zahl;
    QString name;

    static Record fromQuery(QSqlQuery *q) {
        Record r;
        r.zahl = q->value("Z").toInt();
        r.name = q->value("Name").toString();
        return r;
    }
};

template<typename X> std::vector<X> makeResults(QSqlQuery *q) {
    std::vector<X> v;
    while (q->next()) {
        v.push_back(X::fromQuery(q));
    }
    return v;
}

// konvertiere ein resultmap in ein array von maps
std::vector<std::map<QString,QVariant>> makeResultMaps(QSqlQuery *q) {
    std::vector<std::map<QString,QVariant>> results;
    auto r = q->record();
    while (q->next()) {
        std::map<QString,QVariant> map;
        for(auto i = 0; i < r.count(); i++) {
            auto field = r.field(i);
            auto v = q->value(field.name());
            map[field.name()] = v;
        }
        results.push_back(map);
    }
    return results;
}


#endif // DATABASEUTIL_H
