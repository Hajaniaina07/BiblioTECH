#ifndef CATEGORIE_H
#define CATEGORIE_H

#include <QString>
#include <QDate>
#include <QSqlQuery>
#include <QSqlError>

class Categorie {
public:
    int id;
    QString nom;
    
    Categorie();
    Categorie(const QString& nom);
    Categorie(int id, const QString& nom);
    
    static void addCategorie(const Categorie& Categorie);
    static Categorie getById(int id);
    static QList<Categorie> getAllCategories();
    static void updateCategorie(const Categorie& Categorie);
    static void deleteCategorie(int CategorieId);
    bool operator==(const Categorie& other) const;
    bool operator!=(const Categorie& other) const;
};

#endif // CATEGORIE_H
