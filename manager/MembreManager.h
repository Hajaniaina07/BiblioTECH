#ifndef MEMBREMANAGER_H
#define MEMBREMANAGER_H

#include "model/membre.h"
#include <QSqlQuery>
#include <QSqlError>

class MembreManager {
public:
    static void addMembre(const Membre& membre);
    static QList<Membre> getAllMembres();
    static void updateMembre(const Membre& membre);
    static void deleteMembre(int memberId);
};

#endif // MEMBREMANAGER_H
