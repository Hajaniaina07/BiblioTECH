#ifndef LIVRE_H
#define LIVRE_H

#include <QString>
#include "auteur.h"
#include "categorie.h"
#include "editeur.h"
#include "langue.h"

class Livre {
public:
    int id;
    Auteur auteur;
    Categorie categorie;
    Editeur editeur;
    Langue langue;
    QString titre;
    int page;
    QDate publication;
    QString resume;
    int quantite;
    int non_dispo;
    double note;
    int vues;
    int vote;

    Livre();
    Livre(int id, const Auteur& auteur, const Categorie& categorie, const Editeur& editeur, const Langue& langue,
          const QString& titre, int page, const QDate& publication, const QString& resume, int quantite);
    Livre(const Auteur& auteur, const Categorie& categorie, const Editeur& editeur, const Langue& langue,
          const QString& titre, int page, const QDate& publication, const QString& resume, int quantite);


    static void addLivre(const Livre& livre);
    static QList<Livre> getAllLivres();
    static void updateLivre(const Livre& livre);
    static void deleteLivre(int livreId);
    static Livre findLivreById(int livreId);
    static Livre setDetail(Livre livre);
};


#endif // LIVRE_H
