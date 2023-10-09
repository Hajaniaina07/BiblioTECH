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

    if (query.exec()) {
        // Récupérer l'ID après l'insertion
        QSqlQuery queryId("SELECT @@IDENTITY");
        if (queryId.exec() && queryId.next()) {
            int nouvelId = queryId.value(0).toInt();
            qDebug() << "Nouvel ID de l'abonnement du membre ajouté : " << nouvelId;
        } else {
            qDebug() << "Erreur lors de la récupération de l'ID : " << queryId.lastError().text();
        }
    } else {
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
