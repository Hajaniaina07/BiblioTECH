#ifndef LANGUE_H
#define LANGUE_H

#include <QString>
#include <QDate>
#include <QSqlQuery>
#include <QSqlError>

class Langue {
public:
    int id;
    QString nom;
    
    Langue();
    Langue(const QString& nom);
    Langue(int id, const QString& nom);
    
    static void addLangue(const Langue& Langue);
    static QList<Langue> getAllLangues();
    static void updateLangue(const Langue& Langue);
    static void deleteLangue(int LangueId);
    bool operator==(const Langue& other) const;
    bool operator!=(const Langue& other) const;
};


#endif // LANGUE_H
