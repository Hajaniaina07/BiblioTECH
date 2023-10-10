#include "model/abonnement.h"
#include <QSqlQuery>
#include <QSqlError>

Abonnement::Abonnement() : id(0) {
}

Abonnement::Abonnement(const QString& nom, int duree, int maxEmpruntSimultane, int maxDureeEmpruntUnitaire)
    : id(0), nom(nom), duree(duree), maxEmpruntSimultane(maxEmpruntSimultane), maxDureeEmpruntUnitaire(maxDureeEmpruntUnitaire) {
}

void Abonnement::addAbonnement(const Abonnement& abonnement) {
    QSqlQuery query;
    query.prepare("INSERT INTO Abonnement (nom, duree, max_emprunt_simultanee, max_duree_emprunt_unitaire) "
                  "VALUES (?, ?, ?, ?)");

    query.addBindValue(abonnement.nom);
    query.addBindValue(abonnement.duree);
    query.addBindValue(abonnement.maxEmpruntSimultane);
    query.addBindValue(abonnement.maxDureeEmpruntUnitaire);

    if (!query.exec()) {
        qDebug() << "Erreur lors de l'ajout de l'abonnement:" << query.lastError().text();
    }
}

Abonnement Abonnement::getById(int id) {
    Abonnement abonnement;
    QSqlQuery query;
    query.prepare("SELECT * FROM Abonnement WHERE id = ?");
    query.addBindValue(id);
    if (query.exec() && query.next()) {
        abonnement.id = query.value("id").toInt();
        abonnement.nom = query.value("nom").toString();
        abonnement.duree = query.value("duree").toInt();
        abonnement.maxEmpruntSimultane = query.value("max_emprunt_simultanee").toInt();
        abonnement.maxDureeEmpruntUnitaire = query.value("max_duree_emprunt_unitaire").toInt();
    }
    return abonnement;
}

QList<Abonnement> Abonnement::getAllAbonnements() {
    QList<Abonnement> listeAbonnements;

    QSqlQuery query("SELECT * FROM Abonnement");
    while (query.next()) {
        Abonnement abonnement;
        abonnement.id = query.value("id").toInt();
        abonnement.nom = query.value("nom").toString();
        abonnement.duree = query.value("duree").toInt();
        abonnement.maxEmpruntSimultane = query.value("max_emprunt_simultanee").toInt();
        abonnement.maxDureeEmpruntUnitaire = query.value("max_duree_emprunt_unitaire").toInt();
        listeAbonnements.append(abonnement);
    }

    return listeAbonnements;
}

void Abonnement::updateAbonnement(const Abonnement& abonnement) {
    QSqlQuery query;
    query.prepare("UPDATE Abonnement SET nom = ?, duree = ?, max_emprunt_simultanee = ?, max_duree_emprunt_unitaire = ? "
                  "WHERE id = ?");
    query.addBindValue(abonnement.nom);
    query.addBindValue(abonnement.duree);
    query.addBindValue(abonnement.maxEmpruntSimultane);
    query.addBindValue(abonnement.maxDureeEmpruntUnitaire);
    query.addBindValue(abonnement.id);

    if (!query.exec()) {
        qDebug() << "Erreur lors de la mise à jour de l'abonnement:" << query.lastError().text();
    }
}

void Abonnement::deleteAbonnement(int abonnementId) {
    QSqlQuery query;
    query.prepare("DELETE FROM Abonnement WHERE id = ?");
    query.addBindValue(abonnementId);

    if (!query.exec()) {
        qDebug() << "Erreur lors de la suppression de l'abonnement:" << query.lastError().text();
    }
}
