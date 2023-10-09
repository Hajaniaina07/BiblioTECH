#ifndef ABONNEMENTMEMBRE_H
#define ABONNEMENTMEMBRE_H

#include <QString>
#include <QDate>
#include "membre.h"
#include "abonnement.h"

class AbonnementMembre {
public:
    int id;
    Membre membre;
    Abonnement abonnement;
    QDate debut;
    QDate fin;


    AbonnementMembre();
    AbonnementMembre(const Membre& membre, const Abonnement& abonnement, const QDate& debut, const QDate& fin);
    AbonnementMembre(int id, const Membre& membre, const Abonnement& abonnement, const QDate& debut, const QDate& fin);


    static void addAbonnementMembre(const AbonnementMembre& abonnementMembre);
    static AbonnementMembre getById(int id);
    static QList<AbonnementMembre> getAllAbonnementMembres();
    static void updateAbonnementMembre(const AbonnementMembre& abonnementMembre);
    static void deleteAbonnementMembre(int abonnementMembreId);
};


#endif // ABONNEMENTMEMBRE_H
