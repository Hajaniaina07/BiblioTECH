#ifndef ABONNEMENT_H
#define ABONNEMENT_H

#include <QString>

class Abonnement {
public:
    int id;
    QString nom;
    int duree;
    int maxEmpruntSimultane;
    int maxDureeEmpruntUnitaire;

    Abonnement();
    Abonnement(const QString& nom, int duree, int maxEmpruntSimultane, int maxDureeEmpruntUnitaire);

    // Fonctions CRUD
    static void addAbonnement(const Abonnement& abonnement);
    static Abonnement getById(int abonnementID);
    static QList<Abonnement> getAllAbonnements();
    static void updateAbonnement(const Abonnement& abonnement);
    static void deleteAbonnement(int abonnementId);
};

#endif // ABONNEMENT_H
