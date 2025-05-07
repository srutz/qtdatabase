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


/**
 * @brief Erstellt eine Liste von Ergebnissen aus einer QSqlQuery.
 * 
 * Diese Funktion iteriert über die Ergebnisse einer QSqlQuery und erstellt
 * ein std::vector von Objekten des Typs X. Es wird erwartet, dass der Typ X
 * eine statische Methode `fromQuery(QSqlQuery*)` besitzt, die ein Objekt
 * des Typs X aus einer QSqlQuery erstellt.
 * 
 * @tparam X Der Typ der Objekte, die aus der QSqlQuery erstellt werden.
 * @param q Ein Zeiger auf die QSqlQuery, die die Ergebnisse enthält.
 * @return std::vector<X> Ein Vektor mit den aus der QSqlQuery erstellten Objekten.
 */
template<typename X> std::vector<X> makeResults(QSqlQuery *q) {
    std::vector<X> v;
    while (q->next()) {
        v.push_back(X::fromQuery(q));
    }
    return v;
}

// konvertiere ein QSqlQuery-result in ein array von maps
using ResultMap = std::map<QString, QVariant>;

/**
 * @brief Erstellt eine Liste von Ergebnis-Mappings aus einer QSqlQuery.
 *
 * Diese Funktion nimmt einen Zeiger auf ein QSqlQuery-Objekt und iteriert über
 * die Ergebnisse der Abfrage. Für jede Zeile der Abfrage wird eine Map erstellt,
 * die die Spaltennamen als Schlüssel und die entsprechenden Werte als Werte enthält.
 * Diese Maps werden in einem Vektor gesammelt und zurückgegeben.
 *
 * @param q Ein Zeiger auf ein QSqlQuery-Objekt, das die Abfrageergebnisse enthält.
 *          Es wird erwartet, dass die Abfrage bereits ausgeführt wurde und gültig ist.
 * @return Ein std::vector von ResultMap-Objekten, wobei jedes ResultMap die Daten
 *         einer Zeile der Abfrage repräsentiert.
 *
 * @note Es wird davon ausgegangen, dass die Klasse ResultMap eine geeignete
 *       Datenstruktur ist, die Schlüssel-Wert-Paare speichern kann, z. B. eine
 *       std::map oder std::unordered_map.
 *
 * @warning Diese Funktion geht davon aus, dass die Abfrageergebnisse korrekt
 *          sind und keine Fehler aufgetreten sind. Es wird keine Fehlerprüfung
 *          durchgeführt.
 *
 * Beispiel:
 * @code
 * QSqlQuery query("SELECT id, name FROM users");
 * if (query.exec()) {
 *     std::vector<ResultMap> results = makeResultMaps(&query);
 *     for (const auto& row : results) {
 *         std::cout << "ID: " << row["id"].toString().toStdString()
 *                   << ", Name: " << row["name"].toString().toStdString() << std::endl;
 *     }
 * }
 * @endcode
 */
std::vector<ResultMap> makeResultMaps(QSqlQuery *q) {
    std::vector<ResultMap> results;
    auto r = q->record();
    while (q->next()) {
        ResultMap map;
        for (auto i = 0; i < r.count(); i++) {
            auto field = r.field(i);
            map[field.name()] = q->value(field.name());
        }
        results.push_back(map);
    }
    return results;
}


#endif // DATABASEUTIL_H
