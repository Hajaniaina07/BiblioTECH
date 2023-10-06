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
};


#endif // LIVRE_H
