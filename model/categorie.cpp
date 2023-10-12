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

Categorie Categorie::getById(int id) {
    Categorie categorie;
    QSqlQuery query;
    query.prepare("SELECT * FROM Categorie WHERE id = ?");
    query.addBindValue(id);

    if (query.exec() && query.next()) {
        categorie.id = query.value("id").toInt();
        categorie.nom = query.value("nom").toString();
    }
    return categorie;
}

QList<Categorie> Categorie::getAllCategories() {
    QList<Categorie> Categories;
    QSqlQuery query("SELECT * FROM Categorie order by NOM");

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
    query.prepare("UPDATE Categorie SET nom=? where id=?");
    query.addBindValue(Categorie.nom);
    query.addBindValue(Categorie.id);
    if (query.exec()) {

    } else {
        qDebug("Erreur lors de la mise à jour de l'Categorie : %s", qPrintable(query.lastError().text()));
    }
}

void Categorie::deleteCategorie(int CategorieId) {
    QSqlQuery query;
    query.prepare("DELETE FROM Categorie WHERE id=?");
    query.addBindValue(CategorieId);

    if (query.exec()) {

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
