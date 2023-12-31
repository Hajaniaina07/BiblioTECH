#include "model/abonnementmembre.h"

AbonnementMembre::AbonnementMembre() : id(0) {}

AbonnementMembre::AbonnementMembre(const Membre& membre, const Abonnement& abonnement, const QDate& debut, const QDate& fin)
    : membre(membre), abonnement(abonnement), debut(debut), fin(fin) {}

AbonnementMembre::AbonnementMembre(int id, const Membre& membre, const Abonnement& abonnement, const QDate& debut, const QDate& fin)
    : id(id), membre(membre), abonnement(abonnement), debut(debut), fin(fin) {}

void AbonnementMembre::addAbonnementMembre(const AbonnementMembre& abonnementMembre) {
    QSqlQuery query;
    query.prepare("INSERT INTO ABONNEMENT_MEMBRE (Membre_ID, Abonnement_ID, Debut, Fin) "
                  "VALUES (?, ?, ?, ?)");

    query.addBindValue(abonnementMembre.membre.id);
    query.addBindValue(abonnementMembre.abonnement.id);
    query.addBindValue(abonnementMembre.debut.toString("yyyy-MM-dd"));
    query.addBindValue(abonnementMembre.fin.toString("yyyy-MM-dd"));

    if (!query.exec()) {
        qDebug() << "Erreur lors de l'ajout de l'abonnement du membre : " << query.lastError().text();
    }

}

AbonnementMembre AbonnementMembre::getById(int id) {
    QSqlQuery query;
    query.prepare("SELECT * FROM ABONNEMENT_MEMBRE WHERE ID = ?");
    query.addBindValue(id);

    AbonnementMembre abonnementMembre;

    if (query.exec() && query.next()) {
        abonnementMembre.id = query.value("ID").toInt();
        abonnementMembre.membre.id = query.value("Membre_ID").toInt();
        abonnementMembre.abonnement.id = query.value("Abonnement_ID").toInt();
        abonnementMembre.debut = query.value("Debut").toDate();
        abonnementMembre.fin = query.value("Fin").toDate();
    } else {
        qDebug() << "Erreur lors de la récupération de l'abonnement du membre par ID : " << query.lastError().text();
    }

    return abonnementMembre;
}


QList<AbonnementMembre> AbonnementMembre::getAllAbonnementMembres() {
    QList<AbonnementMembre> listeAbonnementMembres;

    QSqlQuery query("SELECT * FROM AbonnementMembre");
    while (query.next()) {
        AbonnementMembre abonnementMembre;
        abonnementMembre.id = query.value("ID").toInt();
        abonnementMembre.membre.id = query.value("Membre_ID").toInt();
        abonnementMembre.abonnement.id = query.value("Abonnement_ID").toInt();
        abonnementMembre.debut = query.value("Debut").toDate();
        abonnementMembre.fin = query.value("Fin").toDate();
        listeAbonnementMembres.append(abonnementMembre);
    }

    return listeAbonnementMembres;
}

void AbonnementMembre::updateAbonnementMembre(const AbonnementMembre& abonnementMembre) {
    QSqlQuery query;
    query.prepare("UPDATE ABONNEMENT_MEMBRE SET Membre_ID = ?, Abonnement_ID = ?, Debut = ?, Fin = ? "
                  "WHERE ID = ?");
    query.addBindValue(abonnementMembre.membre.id);
    query.addBindValue(abonnementMembre.abonnement.id);
    query.addBindValue(abonnementMembre.debut.toString("yyyy-MM-dd"));
    query.addBindValue(abonnementMembre.fin.toString("yyyy-MM-dd"));
    query.addBindValue(abonnementMembre.id);

    if (!query.exec()) {
        qDebug() << "Erreur lors de la mise à jour de l'abonnement du membre : " << query.lastError().text();
    }
}

void AbonnementMembre::deleteAbonnementMembre(int abonnementMembreId) {
    QSqlQuery query;
    query.prepare("DELETE FROM ABONNEMENT_MEMBRE WHERE ID = ?");
    query.addBindValue(abonnementMembreId);

    if (!query.exec()) {
        qDebug() << "Erreur lors de la suppression de l'abonnement du membre : " << query.lastError().text();
    }
}

QList<AbonnementMembre> AbonnementMembre::getMembres() {
    QList<AbonnementMembre> result;
    QList<Membre> membres = Membre::getAllMembres();
    for(const Membre& membre : membres){
        AbonnementMembre abonnementMembre = getByMembreID(membre.id);
        if(abonnementMembre.id == 0){
            abonnementMembre.membre = membre;
        }
        result.append(abonnementMembre);
    }
    return result;
}

AbonnementMembre AbonnementMembre::getByMembreID(int membreId) {
    AbonnementMembre am;

    QSqlQuery maxDateQuery;
    maxDateQuery.prepare("SELECT MAX(fin) FROM ABONNEMENT_MEMBRE WHERE membre_id = ?");
    maxDateQuery.addBindValue(membreId);

    if (maxDateQuery.exec() && maxDateQuery.next()) {
        QDate maxFin = maxDateQuery.value(0).toDate();
        QSqlQuery query;
        query.prepare("SELECT * FROM ABONNEMENT_MEMBRE WHERE membre_id = ? AND fin = ?");
        query.addBindValue(membreId);
        query.addBindValue(maxFin);

        if (query.exec() && query.next()) {
            am.id = query.value("id").toInt();
            am.membre.id = query.value("membre_id").toInt();
            am.abonnement.id = query.value("abonnement_id").toInt();
            am.debut = query.value("debut").toDate();
            am.fin = query.value("fin").toDate();
            am.membre = Membre::getById(am.membre.id);
            am.abonnement = Abonnement::getById(am.abonnement.id);
        }
    }

    return am;
}

QList<AbonnementMembre> AbonnementMembre::getAbonnementMembreByMembreId(int membreId) {
    QList<AbonnementMembre> result;

    QSqlQuery query;
    query.prepare("SELECT * FROM ABONNEMENT_MEMBRE WHERE membre_id = ? ORDER BY ABONNEMENT_MEMBRE.fin DESC");
    query.addBindValue(membreId);

    if (query.exec()) {
        while (query.next()) {
            AbonnementMembre am;
            am.id = query.value("id").toInt();
            am.membre.id = query.value("membre_id").toInt();
            am.abonnement.id = query.value("abonnement_id").toInt();
            am.debut = query.value("debut").toDate();
            am.fin = query.value("fin").toDate();
            am.membre = Membre::getById(am.membre.id);
            am.abonnement = Abonnement::getById(am.abonnement.id);
            result.append(am);
        }
    } else {
        qDebug() << "Erreur lors de la récupération des abonnements membres :" << query.lastError().text();
    }

    return result;
}

