#ifndef LIVREDETAIL_H
#define LIVREDETAIL_H

#include <QMainWindow>
#include <QDate>
#include <QComboBox>
#include "model/Auteur.h"
#include "model/categorie.h"
#include "model/editeur.h"
#include "model/langue.h"
#include "model/livre.h"

namespace Ui {
class LivreDetail;
}

class LivreDetail : public QMainWindow
{
    Q_OBJECT

public:
    explicit LivreDetail(const int& page,Livre& livre,QWidget *parent = nullptr);
    ~LivreDetail();

    int getSelectedItem(QComboBox* comboBox);
    void setDetailLivre();

private slots:
    void getList();
    void getLivre(Livre livre);

    void on_addLivreButton_clicked();

private:
    Ui::LivreDetail *ui;
    int page;
    Livre livre;
    QList<Auteur> listeAuteurs;
    QList<Categorie> listeCategories;
    QList<Editeur> listeEditeurs;
    QList<Langue> listeLangues;
};

#endif // LIVREDETAIL_H
