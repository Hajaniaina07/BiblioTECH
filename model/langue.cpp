#include "Langue.h"

Langue::Langue()
{
}

Langue::Langue(const QString& nom)
    : nom(nom)
{
}

Langue::Langue(int id, const QString& nom)
    : id(id), nom(nom)
{
}

void Langue::addLangue(const Langue& Langue) {
    QSqlQuery query;
    query.prepare("INSERT INTO Langue (nom) VALUES (?)");
    query.addBindValue(Langue.nom);

    if (query.exec()) {

    } else {
        qDebug("Erreur lors de l'ajout de l'Langue : %s", qPrintable(query.lastError().text()));
    }
}

Langue Langue::getById(int id) {
    Langue langue;
    QSqlQuery query;
    query.prepare("SELECT * FROM Langue WHERE id = ?");
    query.addBindValue(id);

    if (query.exec() && query.next()) {
        langue.id = query.value("id").toInt();
        langue.nom = query.value("nom").toString();
    }
    return langue;
}

QList<Langue> Langue::getAllLangues() {
    QList<Langue> Langues;
    QSqlQuery query("SELECT * FROM Langue order by NOM");

    while (query.next()) {
        Langue Langue;
        Langue.id = query.value("id").toInt();
        Langue.nom = query.value("nom").toString();

        Langues.append(Langue);
    }

    return Langues;
}

void Langue::updateLangue(const Langue& langue) {
    QSqlQuery query;
    query.prepare("UPDATE Langue SET nom=? where id =?");
    query.addBindValue(langue.nom);
    query.addBindValue(langue.id);
    if (query.exec()) {
        qDebug("Langue mis à jour avec succès.");
    } else {
        qDebug("Erreur lors de la mise à jour de l'Langue : %s", qPrintable(query.lastError().text()));
    }
}

void Langue::deleteLangue(int LangueId) {
    QSqlQuery query;
    query.prepare("DELETE FROM Langue WHERE id=?");
    query.addBindValue(LangueId);

    if (query.exec()) {
        qDebug("Langue supprimé avec succès.");
    } else {
        qDebug("Erreur lors de la suppression de l'Langue : %s", qPrintable(query.lastError().text()));
    }
}


bool Langue::operator==(const Langue& other) const {
    return (this->nom == other.nom);
}

bool Langue::operator!=(const Langue& other) const {
    return !(*this == other);
}
