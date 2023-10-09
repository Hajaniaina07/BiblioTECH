#ifndef AUTEUR_H
#define AUTEUR_H

#include <QString>
#include <QDate>
#include <QSqlQuery>
#include <QSqlError>


class Auteur {
public:
    int id;
    QString nom;
    QString prenom;
    QString pseudo;
    QDate naissance;

    Auteur();
    Auteur(const QString& nom, const QString& prenom, const QString& pseudo, const QDate& naissance);
    Auteur(int id, const QString& nom, const QString& prenom, const QString& pseudo, const QDate& naissance);

    static void addAuteur(const Auteur& auteur);
    static QList<Auteur> getAllAuteurs();
    static Auteur getById(int id);
    static void updateAuteur(const Auteur& auteur);
    static void deleteAuteur(int auteurId);
    bool operator==(const Auteur& other) const;
    bool operator!=(const Auteur& other) const;


};

#endif // AUTEUR_H
