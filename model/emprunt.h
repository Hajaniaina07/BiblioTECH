#ifndef EMPRUNT_H
#define EMPRUNT_H

#include <QDate>
#include "model/livre.h"
#include "model/membre.h"
#include "util/boolResult.h"

class Emprunt {
public:
    int id;
    Livre livre;
    Membre membre;
    QDate dateEmprunt;
    QDate dateMax;
    QDate dateRendue;
    float note;

    Emprunt();
    Emprunt(const Livre& livre, const Membre& membre, const QDate& dateEmprunt);

    static void addEmprunt(const Emprunt& emprunt);
    static QList<Emprunt> getAllEmprunts();
    static QList<Emprunt> getTopLatest(int idMembre);
    static void updateEmprunt(const Emprunt& emprunt);
    static void deleteEmprunt(int empruntId);
    static BoolResult validateEmprunt(Emprunt  &emprunt);
};

#endif // EMPRUNT_H
