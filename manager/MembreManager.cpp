#include "MembreManager.h"

void MembreManager::addMembre(const Membre& membre) {
QSqlQuery query;
    query.prepare("INSERT INTO Membre (nom, prenom, naissance, adresse, contact) VALUES (?, ?, ?, ?, ?)");
    query.addBindValue(membre.nom);
    query.addBindValue(membre.prenom);
    query.addBindValue(membre.naissance.toString("yyyy-MM-dd"));  // Format de date adapté à la base de données
    query.addBindValue(membre.adresse);
    query.addBindValue(membre.contact);

    if (query.exec()) {
        qDebug("Membre ajouté avec succès.");
    } else {
        qDebug("Erreur lors de l'ajout du membre : %s", qPrintable(query.lastError().text()));
    }
}

QList<Membre> MembreManager::getAllMembres() {
    QList<Membre> membres;
    QSqlQuery query("SELECT * FROM Membre");

    while (query.next()) {
        Membre membre;
        membre.id = query.value("id").toInt();
        membre.nom = query.value("nom").toString();
        membre.prenom = query.value("prenom").toString();
        membre.naissance = QDate::fromString(query.value("naissance").toString(), "yyyy-MM-dd");
        membre.adresse = query.value("adresse").toString();
        membre.contact = query.value("contact").toString();

        membres.append(membre);
    }

    return membres;
}

void MembreManager::updateMembre(const Membre& membre) {
    QSqlQuery query;
    query.prepare("UPDATE Membre SET nom=?, prenom=?, naissance=?, adresse=?, contact=? WHERE id=?");
    query.addBindValue(membre.nom);
    query.addBindValue(membre.prenom);
    query.addBindValue(membre.naissance.toString("yyyy-MM-dd"));
    query.addBindValue(membre.adresse);
    query.addBindValue(membre.contact);
    query.addBindValue(membre.id);

    if (query.exec()) {
        qDebug("Membre mis à jour avec succès.");
    } else {
        qDebug("Erreur lors de la mise à jour du membre : %s", qPrintable(query.lastError().text()));
    }
}

void MembreManager::deleteMembre(int memberId) {
    QSqlQuery query;
    query.prepare("DELETE FROM Membre WHERE id=?");
    query.addBindValue(memberId);

    if (query.exec()) {
        qDebug("Membre supprimé avec succès.");
    } else {
        qDebug("Erreur lors de la suppression du membre : %s", qPrintable(query.lastError().text()));
    }
}
