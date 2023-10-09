#ifndef EMPRUNT_H
#define EMPRUNT_H

#include <QDate>
#include "model/livre.h"
#include "model/membre.h"

class Emprunt {
public:
    int id;
    Livre livre;
    Membre membre;
    QDate dateEmprunt;
    QDate dateMax;
    QDate dateRendue;

    Emprunt();
    Emprunt(const Livre& livre, const Membre& membre, const QDate& dateEmprunt);

    static void addEmprunt(const Emprunt& emprunt);
    static QList<Emprunt> getAllEmprunts();
    static void updateEmprunt(const Emprunt& emprunt);
    static void deleteEmprunt(int empruntId);
};

#endif // EMPRUNT_H
