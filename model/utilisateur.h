#ifndef UTILISATEUR_H
#define UTILISATEUR_H

#include <QString>
#include <QSqlQuery>
#include <QSqlError>


class Utilisateur
{
public:
    int id;
    QString login;
    QString mdp;

    Utilisateur();
    Utilisateur(const QString& login,const QString& mdp);
    bool isConnected();
};

#endif // UTILISATEUR_H
