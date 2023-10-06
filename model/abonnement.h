#ifndef ABONNEMENT_H
#define ABONNEMENT_H

#include <QString>
class Abonnement {
public:
    int id;
    QString type;
    int duree;
    int maxEmpruntSimultane;
    int maxDureeEmpruntUnitaire;
};


#endif // ABONNEMENT_H
