#include "model/emprunt.h"
#include <QSqlQuery>
#include <QSqlError>


Emprunt::Emprunt() {
}

Emprunt::Emprunt(const Livre& livre, const Membre& membre, const QDate& dateEmprunt)
    : id(0), livre(livre), membre(membre), dateEmprunt(dateEmprunt) {
}

void Emprunt::addEmprunt(const Emprunt& emprunt) {
    QSqlQuery query;
    query.prepare("INSERT INTO Emprunt (livre_id, membre_id, date_emprunt, date_max, date_rendue) "
                  "VALUES (?, ?, ?, ?, ?)");

    query.addBindValue(emprunt.livre.id);
    query.addBindValue(emprunt.membre.id);
    query.addBindValue(emprunt.dateEmprunt.toString("yyyy-MM-dd"));
    query.addBindValue(emprunt.dateMax.toString("yyyy-MM-dd"));

    if (emprunt.dateRendue.isValid()) {
        query.addBindValue(emprunt.dateRendue.toString("yyyy-MM-dd"));
    } else {
        query.addBindValue(QVariant());
    }

    if (!query.exec()) {
        qDebug() << "Erreur lors de l'ajout de l'emprunt:" << query.lastError().text();
    }
}

QList<Emprunt> Emprunt::getAllEmprunts() {
    QList<Emprunt> listeEmprunts;

    QSqlQuery query("SELECT * FROM Emprunt order by date_emprunt desc");
    while (query.next()) {
        Emprunt emprunt;
        emprunt.id = query.value("id").toInt();
        emprunt.livre.id = query.value("livre_id").toInt();
        emprunt.membre.id = query.value("membre_id").toInt();
        emprunt.dateEmprunt = query.value("date_emprunt").toDate();
        emprunt.dateMax = query.value("date_max").toDate();
        emprunt.dateRendue = query.value("date_rendue").toDate();
        emprunt.membre = Membre::getById(emprunt.membre.id);
        emprunt.livre= Livre::findLivreById(emprunt.livre.id);
        listeEmprunts.append(emprunt);
    }

    return listeEmprunts;
}

void Emprunt::updateEmprunt(const Emprunt& emprunt) {
    QSqlQuery query;
    query.prepare("UPDATE Emprunt SET livre_id = ?, membre_id = ?, date_emprunt = ?, date_max = ?, date_rendue = ? "
                  "WHERE id = ?");
    query.addBindValue(emprunt.livre.id);
    query.addBindValue(emprunt.membre.id);
    query.addBindValue(emprunt.dateEmprunt.toString("yyyy-MM-dd"));
    query.addBindValue(emprunt.dateMax.toString("yyyy-MM-dd"));
    query.addBindValue(emprunt.dateRendue.toString("yyyy-MM-dd"));
    query.addBindValue(emprunt.id);

    if (!query.exec()) {
        qDebug() << "Erreur lors de la mise à jour de l'emprunt:" << query.lastError().text();
    }
}

void Emprunt::deleteEmprunt(int empruntId) {
    QSqlQuery query;
    query.prepare("DELETE FROM Emprunt WHERE id = ?");
    query.addBindValue(empruntId);

    if (!query.exec()) {
        qDebug() << "Erreur lors de la suppression de l'emprunt:" << query.lastError().text();
    }
}


BoolResult Emprunt::validateEmprunt(const Emprunt& emprunt){
    BoolResult res;
    return res;
}
