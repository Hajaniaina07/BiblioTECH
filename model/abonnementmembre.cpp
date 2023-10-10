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
    AbonnementMembre abonnementMembre;

    QSqlQuery query("SELECT Membre.id AS MembreId, Membre.nom AS NomMembre, Membre.prenom AS PrenomMembre, Membre.naissance AS NaissanceMembre, Membre.contact AS ContactMembre, Membre.adresse AS AdresseMembre, Abonnement.id AS AbonnementId, Abonnement.nom AS NomAbonnement, AbonnementMembre.id AS AbonnementMembreId, AbonnementMembre.debut AS DebutAbonnement, AbonnementMembre.fin AS FinAbonnement FROM Membre LEFT JOIN AbonnementMembre ON Membre.id = AbonnementMembre.membre_id LEFT JOIN Abonnement AS Abonnement ON Abonnement.id = AbonnementMembre.abonnement_id WHERE Membre.id = :membreId AND (AbonnementMembre.membre_id IS NULL OR AbonnementMembre.fin = (SELECT MAX(fin) FROM AbonnementMembre WHERE membre_id = :membreId))");

    query.bindValue(":membreId", membreId);

    if (query.next()) {
        abonnementMembre.id = query.value("AbonnementMembreId").toInt();
        abonnementMembre.membre.id = query.value("MembreId").toInt();
        abonnementMembre.membre.nom = query.value("NomMembre").toString();
        abonnementMembre.membre.prenom = query.value("PrenomMembre").toString();
        abonnementMembre.membre.naissance = query.value("NaissanceMembre").toDate();
        abonnementMembre.membre.contact = query.value("ContactMembre").toString();
        abonnementMembre.membre.adresse = query.value("AdresseMembre").toString();
        abonnementMembre.abonnement.id = query.value("AbonnementId").toInt();
        abonnementMembre.abonnement.nom = query.value("NomAbonnement").toString();
        abonnementMembre.debut = query.value("DebutAbonnement").toDate();
        abonnementMembre.fin = query.value("FinAbonnement").toDate();
    }

    return abonnementMembre;
}

QList<AbonnementMembre> AbonnementMembre::getAbonnementMembreByMembreId(int membreId) {
    QList<AbonnementMembre> result;

    QSqlQuery query;
    query.prepare("SELECT AbonnementMembre.id, Membre.id AS membre_id, Membre.nom, Membre.prenom, Membre.naissance, Membre.adresse, Membre.contact, Abonnement.id AS abonnement_id, Abonnement.nom AS abonnement_nom, Abonnement.duree, Abonnement.maxEmpruntSimultane, Abonnement.maxDureeEmpruntUnitaire, AbonnementMembre.debut, AbonnementMembre.fin "
                  "FROM AbonnementMembre "
                  "JOIN Membre ON AbonnementMembre.membre_id = Membre.id "
                  "JOIN Abonnement ON AbonnementMembre.abonnement_id = Abonnement.id "
                  "WHERE Membre.id = ?");
    query.addBindValue(membreId);

    if (query.exec()) {
        while (query.next()) {
            AbonnementMembre abonnementMembre;
            abonnementMembre.id = query.value("id").toInt();

            abonnementMembre.membre.id = query.value("membre_id").toInt();
            abonnementMembre.membre.nom = query.value("nom").toString();
            abonnementMembre.membre.prenom = query.value("prenom").toString();
            abonnementMembre.membre.naissance = query.value("naissance").toDate();
            abonnementMembre.membre.adresse = query.value("adresse").toString();
            abonnementMembre.membre.contact = query.value("contact").toString();

            abonnementMembre.abonnement.id = query.value("abonnement_id").toInt();
            abonnementMembre.abonnement.nom = query.value("abonnement_nom").toString();
            abonnementMembre.abonnement.duree = query.value("duree").toInt();
            abonnementMembre.abonnement.maxEmpruntSimultane = query.value("maxEmpruntSimultane").toInt();
            abonnementMembre.abonnement.maxDureeEmpruntUnitaire = query.value("maxDureeEmpruntUnitaire").toInt();

            abonnementMembre.debut = query.value("debut").toDate();
            abonnementMembre.fin = query.value("fin").toDate();

            result.append(abonnementMembre);
        }
    } else {
        qDebug() << "Erreur lors de la récupération des abonnements membres :" << query.lastError().text();
    }

    return result;
}




