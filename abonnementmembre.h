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
};


#endif // ABONNEMENTMEMBRE_H
