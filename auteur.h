#ifndef AUTEUR_H
#define AUTEUR_H

#include <QString>
#include <QDate>
class Auteur {
public:
    int id;
    QString nom;
    QString prenom;
    QString pseudo;
    QDate naissance;
};


#endif // AUTEUR_H
