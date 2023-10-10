#include "Editeur.h"

Editeur::Editeur()
{
}

Editeur::Editeur(const QString& nom)
    : nom(nom)
{
}

Editeur::Editeur(int id, const QString& nom)
    : id(id), nom(nom)
{
}

void Editeur::addEditeur(const Editeur& Editeur) {
    QSqlQuery query;
    query.prepare("INSERT INTO Editeur (nom) VALUES (?)");
    query.addBindValue(Editeur.nom);

    if (query.exec()) {

    } else {
        qDebug("Erreur lors de l'ajout de l'Editeur : %s", qPrintable(query.lastError().text()));
    }
}

Editeur Editeur::getById(int id) {
    Editeur editeur;
    QSqlQuery query;
    query.prepare("SELECT * FROM Editeur WHERE id = ?");
    query.addBindValue(id);

    if (query.exec() && query.next()) {
        editeur.id = query.value("id").toInt();
        editeur.nom = query.value("nom").toString();
    }
    return editeur;
}

QList<Editeur> Editeur::getAllEditeurs() {
    QList<Editeur> Editeurs;
    QSqlQuery query("SELECT * FROM Editeur");

    while (query.next()) {
        Editeur Editeur;
        Editeur.id = query.value("id").toInt();
        Editeur.nom = query.value("nom").toString();

        Editeurs.append(Editeur);
    }

    return Editeurs;
}

void Editeur::updateEditeur(const Editeur& Editeur) {
    QSqlQuery query;
    query.prepare("UPDATE Editeur SET nom=? where id=?");
    query.addBindValue(Editeur.nom);
    query.addBindValue(Editeur.id);
    if (query.exec()) {
        qDebug("Editeur mis à jour avec succès.");
    } else {
        qDebug("Erreur lors de la mise à jour de l'Editeur : %s", qPrintable(query.lastError().text()));
    }
}

void Editeur::deleteEditeur(int EditeurId) {
    QSqlQuery query;
    query.prepare("DELETE FROM Editeur WHERE id=?");
    query.addBindValue(EditeurId);

    if (query.exec()) {
        qDebug("Editeur supprimé avec succès.");
    } else {
        qDebug("Erreur lors de la suppression de l'Editeur : %s", qPrintable(query.lastError().text()));
    }
}


bool Editeur::operator==(const Editeur& other) const {
    return (this->nom == other.nom);
}

bool Editeur::operator!=(const Editeur& other) const {
    return !(*this == other);
}
