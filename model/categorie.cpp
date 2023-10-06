#include "Categorie.h"

Categorie::Categorie()
{
}

Categorie::Categorie(const QString& nom)
    : nom(nom)
{
}

Categorie::Categorie(int id, const QString& nom)
    : id(id), nom(nom)
{
}

void Categorie::addCategorie(const Categorie& Categorie) {
    QSqlQuery query;
    query.prepare("INSERT INTO Categorie (nom) VALUES (?)");
    query.addBindValue(Categorie.nom);

    if (query.exec()) {
        qDebug("Categorie ajouté avec succès.");
    } else {
        qDebug("Erreur lors de l'ajout de l'Categorie : %s", qPrintable(query.lastError().text()));
    }
}

QList<Categorie> Categorie::getAllCategories() {
    QList<Categorie> Categories;
    QSqlQuery query("SELECT * FROM Categorie");

    while (query.next()) {
        Categorie Categorie;
        Categorie.id = query.value("id").toInt();
        Categorie.nom = query.value("nom").toString();

        Categories.append(Categorie);
    }

    return Categories;
}

void Categorie::updateCategorie(const Categorie& Categorie) {
    QSqlQuery query;
    query.prepare("UPDATE Categorie SET nom=?");
    query.addBindValue(Categorie.nom);
    if (query.exec()) {
        qDebug("Categorie mis à jour avec succès.");
    } else {
        qDebug("Erreur lors de la mise à jour de l'Categorie : %s", qPrintable(query.lastError().text()));
    }
}

void Categorie::deleteCategorie(int CategorieId) {
    QSqlQuery query;
    query.prepare("DELETE FROM Categorie WHERE id=?");
    query.addBindValue(CategorieId);

    if (query.exec()) {
        qDebug("Categorie supprimé avec succès.");
    } else {
        qDebug("Erreur lors de la suppression de l'Categorie : %s", qPrintable(query.lastError().text()));
    }
}


bool Categorie::operator==(const Categorie& other) const {
    return (this->nom == other.nom);
}

bool Categorie::operator!=(const Categorie& other) const {
    return !(*this == other);
}
