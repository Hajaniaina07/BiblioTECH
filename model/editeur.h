#ifndef EDITEUR_H
#define EDITEUR_H

#include <QString>
#include <QDate>
#include <QSqlQuery>
#include <QSqlError>

class Editeur {
public:
    int id;
    QString nom;
    
    Editeur();
    Editeur(const QString& nom);
    Editeur(int id, const QString& nom);
    
    static void addEditeur(const Editeur& Editeur);
    static QList<Editeur> getAllEditeurs();
    static void updateEditeur(const Editeur& Editeur);
    static void deleteEditeur(int EditeurId);
    bool operator==(const Editeur& other) const;
    bool operator!=(const Editeur& other) const;
};


#endif // EDITEUR_H
