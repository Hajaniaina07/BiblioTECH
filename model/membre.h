#ifndef MEMBRE_H
#define MEMBRE_H

#include <QDate>
#include <QString>
class Membre {
public:
    int id;
    QString nom;
    QString prenom;
    QDate naissance;
    QString adresse;
    QString contact;
};


#endif // MEMBRE_H
