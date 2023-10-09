#include "Membre.h"

Membre::Membre()
{
}

Membre::Membre(const QString& nom, const QString& prenom, const QDate& naissance, const QString& adresse, const QString& contact)
    : nom(nom), prenom(prenom), naissance(naissance), adresse(adresse), contact(contact)
{
}

Membre::Membre(int id, const QString& nom, const QString& prenom, const QDate& naissance, const QString& adresse, const QString& contact)
    : id(id), nom(nom), prenom(prenom), naissance(naissance), adresse(adresse), contact(contact)
{
}

int Membre::addMembre(const Membre& membre) {
    QSqlQuery query;
    query.prepare("INSERT INTO Membre (nom, prenom, naissance, adresse, contact) "
                  "VALUES (?, ?, ?, ?, ?)");

    query.addBindValue(membre.nom);
    query.addBindValue(membre.prenom);
    query.addBindValue(membre.naissance.toString("yyyy-MM-dd"));
    query.addBindValue(membre.adresse);
    query.addBindValue(membre.contact);

    if (query.exec()) {
        QSqlQuery queryId("SELECT @@IDENTITY");
        if (queryId.exec() && queryId.next()) {
            int nouvelId = queryId.value(0).toInt();
            qDebug() << "Nouvel ID du membre ajouté : " << nouvelId;
            return nouvelId;
        } else {
            qDebug() << "Erreur lors de la récupération de l'ID : " << queryId.lastError().text();
        }
    } else {
        qDebug() << "Erreur lors de l'ajout du membre : " << query.lastError().text();
        qDebug() << "Requête : " << query.lastQuery();
    }

    return -1;
}



Membre Membre::getById(int id) {
    Membre membre;
    QSqlQuery query;
    query.prepare("SELECT * FROM Membre WHERE id = ?");
    query.addBindValue(id);

    if (query.exec() && query.next()) {
        membre.id = query.value("id").toInt();
        membre.nom = query.value("nom").toString();
        membre.prenom = query.value("prenom").toString();
        membre.naissance = query.value("naissance").toDateTime().date();
        membre.adresse = query.value("adresse").toString();
        membre.contact = query.value("contact").toString();
    }
    return membre;
}

QList<Membre> Membre::getAllMembres() {
    QList<Membre> membres;
    QSqlQuery query("SELECT * FROM Membre");

    while (query.next()) {
        Membre membre;
        membre.id = query.value("id").toInt();
        membre.nom = query.value("nom").toString();
        membre.prenom = query.value("prenom").toString();
        membre.naissance = query.value("naissance").toDateTime().date();
        membre.adresse = query.value("adresse").toString();
        membre.contact = query.value("contact").toString();

        membres.append(membre);
    }

    return membres;
}

void Membre::updateMembre(const Membre& membre) {
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
        qDebug("Erreur lors de la mise à jour de l'Membre : %s", qPrintable(query.lastError().text()));
    }
}

void Membre::deleteMembre(int membreId) {
    QSqlQuery query;
    query.prepare("DELETE FROM Membre WHERE id=?");
    query.addBindValue(membreId);

    if (query.exec()) {
        qDebug("Membre supprimé avec succès.");
    } else {
        qDebug("Erreur lors de la suppression de l'Membre : %s", qPrintable(query.lastError().text()));
    }
}
