#include "model/emprunt.h"
#include "model/abonnementmembre.h"
#include <QSqlQuery>
#include <QSqlRecord>
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
        emprunt.note = query.value("evaluation").toDouble();
        emprunt.membre = Membre::getById(emprunt.membre.id);
        emprunt.livre= Livre::findLivreById(emprunt.livre.id);
        listeEmprunts.append(emprunt);
    }

    return listeEmprunts;
}

QList<Emprunt> Emprunt::getTopLatest(int idMembre) {
    QList<Emprunt> listeEmprunts;

    QSqlQuery query;
    query.prepare("SELECT * FROM Emprunt WHERE membre_id = ? ORDER BY date_emprunt DESC");
    query.addBindValue(idMembre);

    if (query.exec()) {
        while (query.next()) {
            Emprunt emprunt;
            emprunt.id = query.value("id").toInt();
            emprunt.livre.id = query.value("livre_id").toInt();
            emprunt.membre.id = query.value("membre_id").toInt();
            emprunt.dateEmprunt = query.value("date_emprunt").toDate();
            emprunt.dateMax = query.value("date_max").toDate();
            emprunt.dateRendue = query.value("date_rendue").toDate();
            emprunt.note = query.value("evaluation").toDouble();
            emprunt.livre = Livre::findLivreById(emprunt.livre.id);
            listeEmprunts.append(emprunt);
        }
    } else {
        qDebug() << "Erreur SQL:" << query.lastError().text();
    }

    return listeEmprunts;
}


void Emprunt::updateEmprunt(const Emprunt& emprunt) {
    QSqlQuery query;
    query.prepare("UPDATE Emprunt SET livre_id = ?, membre_id = ?, date_emprunt = ?, date_max = ?, date_rendue = ?, evaluation = ? "
                  "WHERE id = ?");

    query.addBindValue(emprunt.livre.id);
    query.addBindValue(emprunt.membre.id);
    query.addBindValue(emprunt.dateEmprunt.toString("yyyy-MM-dd"));
    query.addBindValue(emprunt.dateMax.toString("yyyy-MM-dd"));
    query.addBindValue(emprunt.dateRendue.toString("yyyy-MM-dd"));
    query.addBindValue(emprunt.note);
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

int Emprunt::countNonRendue(int livre_id) {
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM emprunt WHERE livre_id = ? "
                  "AND (date_rendue IS NULL OR date_rendue = '' OR date_rendue = 'Invalid')");
    query.addBindValue(livre_id);

    if (query.exec() && query.next()) {
        return query.value(0).toInt();
    } else {
        qDebug() << "Erreur SQL:" << query.lastError().text();
        return -1; // Valeur d'erreur, ajustez selon votre besoin
    }
}


BoolResult Emprunt::validateEmprunt(Emprunt  &emprunt){
    BoolResult res;
    Membre membre = Membre::getById(emprunt.membre.id);
    AbonnementMembre am = AbonnementMembre::getByMembreID(membre.id);
    if(am.id != 0){
        QDate now = QDate::currentDate();
        if(am.fin > now){
            Abonnement abonnement = am.abonnement;
            QList<Emprunt> listEmprunts = getTopLatest(membre.id);
            int nonRendue = 0;
            for (Emprunt &em: listEmprunts) {
                if(!em.dateRendue.isValid()){
                    nonRendue ++;
                    if(em.dateMax < now){
                        res.message = QString("Veuillez rendre le livre intitulé \"%1\" de %2 %3 afin de pouvoir emprunter de nouveau.")
                        .arg(em.livre.titre).arg(em.livre.auteur.prenom).arg(em.livre.auteur.nom);
                        return res;
                    }
                }
            }
            if(nonRendue >= abonnement.maxEmpruntSimultane){
                res.message = QString("%1 %2 a atteint le nombre maximum \n d'emprunts simultanés de %3 livres")
                .arg(membre.nom).arg(membre.prenom).arg(abonnement.maxEmpruntSimultane);
            }else {
                emprunt.dateMax = emprunt.dateEmprunt.addDays(abonnement.maxDureeEmpruntUnitaire);
                res.validate = true;
            }
        }else {
            res.message = "Abonnement expiré";
        }
    }else {
        res.message = QString("%1 %2 n'est souscrit à aucun abonnement").arg(membre.nom).arg(membre.prenom);
    }
    int totalNonRendue = countNonRendue(emprunt.livre.id);
    int totalLivre = emprunt.livre.quantite;
    if(totalNonRendue >= totalLivre){
        res.message = QString("Le livre intitulé \"%1\" de %2 %3 est indisponible")
        .arg(emprunt.livre.titre).arg(emprunt.livre.auteur.prenom).arg(emprunt.livre.auteur.nom);
        res.validate = false;
    }

    qDebug() << "Livre:" << totalNonRendue << totalLivre;
    return res;
}
