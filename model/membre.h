#ifndef MEMBRE_H
#define MEMBRE_H

#include <QDate>
#include <QString>
#include <QSqlQuery>
#include <QSqlError>
class Membre {
public:
    int id;
    QString nom;
    QString prenom;
    QDate naissance;
    QString adresse;
    QString contact;

    Membre();
    Membre(const QString& nom, const QString& prenom, const QDate& naissance, const QString& adresse, const QString& contact);
    Membre(int id, const QString& nom, const QString& prenom, const QDate& naissance, const QString& adresse, const QString& contact);


    static int addMembre(const Membre& membre);
    static Membre getById(int id);
    static QList<Membre> getAllMembres();
    static void updateMembre(const Membre& membre);
    static void deleteMembre(int membreId);
};


#endif // MEMBRE_H
