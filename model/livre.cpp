#include "Livre.h"
#include "emprunt.h"


Livre::Livre()
{
}

Livre::Livre(int id, const Auteur& auteur, const Categorie& categorie, const Editeur& editeur, const Langue& langue,
const QString& titre, int page, const QDate& publication, const QString& resume, int quantite)
:id(id),auteur(auteur), categorie(categorie), editeur(editeur), langue(langue), titre(titre), page(page),
publication(publication), resume(resume), quantite(quantite)
{
}

Livre::Livre(const Auteur& auteur, const Categorie& categorie, const Editeur& editeur, const Langue& langue,
const QString& titre, int page, const QDate& publication, const QString& resume, int quantite)
:auteur(auteur), categorie(categorie), editeur(editeur), langue(langue), titre(titre), page(page),
publication(publication), resume(resume), quantite(quantite)
{
}

void Livre::addLivre(const Livre& livre) {
    QSqlQuery query;
    query.prepare("INSERT INTO Livre (AUTEUR_ID, CATEGORIE_ID, EDITEUR_ID, LANGUE_ID, titre, page, publication, resume, quantite) "
                  "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?)");
    query.addBindValue(livre.auteur.id);
    query.addBindValue(livre.categorie.id);
    query.addBindValue(livre.editeur.id);
    query.addBindValue(livre.langue.id);
    query.addBindValue(livre.titre);
    query.addBindValue(livre.page);
    query.addBindValue(livre.publication.toString("yyyy-MM-dd"));
    query.value("publication").toDateTime().date();
    query.addBindValue(livre.resume);
    query.addBindValue(livre.quantite);

    if (query.exec()) {
        qDebug("Livre ajouté avec succès.");
    } else {
        qDebug("Erreur lors de l'ajout du Livre : %s", qPrintable(query.lastError().text()));
    }
}

QList<Livre> Livre::getAllLivres() {
    QList<Livre> livres;
    QSqlQuery query("SELECT * FROM Livre");

    while (query.next()) {
        Livre livre;
        livre.id = query.value("id").toInt();
        livre.auteur.id = query.value("AUTEUR_ID").toInt();
        livre.categorie.id = query.value("CATEGORIE_ID").toInt();
        livre.editeur.id = query.value("EDITEUR_ID").toInt();
        livre.langue.id = query.value("LANGUE_ID").toInt();
        livre.titre = query.value("titre").toString();
        livre.page = query.value("page").toInt();
        livre.quantite = query.value("quantite").toInt();
        livre.publication = query.value("publication").toDateTime().date();
        livre.resume = query.value("resume").toString();

        livres.append(setDetail(livre));
    }

    return livres;
}

void Livre::updateLivre(const Livre& livre) {
    QSqlQuery query;
    query.prepare("UPDATE Livre SET AUTEUR_ID=?, CATEGORIE_ID=?, EDITEUR_ID=?, LANGUE_ID=?, "
                  "titre=?, page=?, publication=?, resume=?, quantite=? WHERE id=?");
    query.addBindValue(livre.auteur.id);
    query.addBindValue(livre.categorie.id);
    query.addBindValue(livre.editeur.id);
    query.addBindValue(livre.langue.id);
    query.addBindValue(livre.titre);
    query.addBindValue(livre.page);
    query.addBindValue(livre.publication.toString("yyyy-MM-dd"));
    query.addBindValue(livre.resume);
    query.addBindValue(livre.quantite);
    query.addBindValue(livre.id);

    if (query.exec()) {
        qDebug("Livre mis à jour avec succès.");
    } else {
        qDebug("Erreur lors de la mise à jour du Livre : %s", qPrintable(query.lastError().text()));
    }
}

void Livre::deleteLivre(int livreId) {
    QSqlQuery query;
    query.prepare("DELETE FROM Livre WHERE id=?");
    query.addBindValue(livreId);

    if (query.exec()) {
        qDebug("Livre supprimé avec succès.");
    } else {
        qDebug("Erreur lors de la suppression du Livre : %s", qPrintable(query.lastError().text()));
    }
}

Livre Livre::findLivreById(int livreId) {
    Livre livre;

    QSqlQuery query;
    query.prepare("SELECT * FROM Livre WHERE id = ?");
    query.addBindValue(livreId);

    if (query.exec() && query.next()) {
        livre.id = query.value("id").toInt();
        livre.auteur.id = query.value("AUTEUR_ID").toInt();
        livre.categorie.id = query.value("CATEGORIE_ID").toInt();
        livre.editeur.id = query.value("EDITEUR_ID").toInt();
        livre.langue.id = query.value("LANGUE_ID").toInt();
        livre.titre = query.value("titre").toString();
        livre.page = query.value("page").toInt();
        livre.quantite = query.value("quantite").toInt();
        livre.publication = query.value("publication").toDateTime().date();
        livre.resume = query.value("resume").toString();
    }
    return setDetail(livre);
}

Livre Livre::setDetail(Livre livre) {
    livre.auteur = Auteur::getById(livre.auteur.id);
    livre.categorie = Categorie::getById(livre.categorie.id);
    livre.editeur = Editeur::getById(livre.editeur.id);
    livre.langue = Langue::getById(livre.langue.id);
    livre.non_dispo = Emprunt::countNonRendue(livre.id);
    std::pair<int, double> result = Emprunt::totalNavgNote(livre.id);
    livre.vote = result.first;
    livre.note = result.second;
    livre.vues = Emprunt::nbEmprunt(livre.id);
    return livre;
}
