#include "Auteur.h"

Auteur::Auteur()
{
}

Auteur::Auteur(const QString& nom, const QString& prenom, const QString& pseudo, const QDate& naissance)
    : nom(nom), prenom(prenom), pseudo(pseudo), naissance(naissance)
{
}

Auteur::Auteur(int id, const QString& nom, const QString& prenom, const QString& pseudo, const QDate& naissance)
    : id(id), nom(nom), prenom(prenom), pseudo(pseudo), naissance(naissance)
{
}

void Auteur::addAuteur(const Auteur& auteur) {
    QSqlQuery query;
    query.prepare("INSERT INTO Auteur (nom, prenom, pseudo, naissance) VALUES (?, ?, ?, ?)");
    query.addBindValue(auteur.nom);
    query.addBindValue(auteur.prenom);
    query.addBindValue(auteur.pseudo);
    query.addBindValue(auteur.naissance.toString("yyyy-MM-dd"));

    if (query.exec()) {
        qDebug("Auteur ajouté avec succès.");
    } else {
        qDebug("Erreur lors de l'ajout de l'Auteur : %s", qPrintable(query.lastError().text()));
    }
}


Auteur Auteur::getById(int id) {
    Auteur auteur;
    QSqlQuery query;
    query.prepare("SELECT * FROM Auteur WHERE id = ?");
    query.addBindValue(id);

    if (query.exec() && query.next()) {
        auteur.id = query.value("id").toInt();
        auteur.nom = query.value("nom").toString();
        auteur.prenom = query.value("prenom").toString();
        auteur.pseudo = query.value("pseudo").toString();
        auteur.naissance = query.value("naissance").toDateTime().date();
    }
    return auteur;
}

QList<Auteur> Auteur::getAllAuteurs() {
    QList<Auteur> auteurs;
    QSqlQuery query("SELECT * FROM Auteur");

    while (query.next()) {
        Auteur auteur;
        auteur.id = query.value("id").toInt();
        auteur.nom = query.value("nom").toString();
        auteur.prenom = query.value("prenom").toString();
        auteur.pseudo = query.value("pseudo").toString();
        auteur.naissance = query.value("naissance").toDateTime().date();

        auteurs.append(auteur);
    }

    return auteurs;
}

void Auteur::updateAuteur(const Auteur& auteur) {
    QSqlQuery query;
    query.prepare("UPDATE Auteur SET nom=?, prenom=?, pseudo=?, naissance=? WHERE id=?");
    query.addBindValue(auteur.nom);
    query.addBindValue(auteur.prenom);
    query.addBindValue(auteur.pseudo);
    query.addBindValue(auteur.naissance.toString("yyyy-MM-dd"));
    query.addBindValue(auteur.id);
    if (query.exec()) {
        qDebug("Auteur mis à jour avec succès.");
    } else {
        qDebug("Erreur lors de la mise à jour de l'Auteur : %s", qPrintable(query.lastError().text()));
    }
}

void Auteur::deleteAuteur(int auteurId) {
    QSqlQuery query;
    query.prepare("DELETE FROM Auteur WHERE id=?");
    query.addBindValue(auteurId);

    if (query.exec()) {
        qDebug("Auteur supprimé avec succès.");
    } else {
        qDebug("Erreur lors de la suppression de l'Auteur : %s", qPrintable(query.lastError().text()));
    }
}


bool Auteur::operator==(const Auteur& other) const {
    return (this->nom == other.nom &&
            this->prenom == other.prenom &&
            this->pseudo == other.pseudo &&
            this->naissance == other.naissance);
}

bool Auteur::operator!=(const Auteur& other) const {
    return !(*this == other);
}
