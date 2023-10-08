#include "livredetail.h"
#include "ui_livredetail.h"
#include "manager/DatabaseManager.h"

LivreDetail::LivreDetail(const int& page,const int& livreID, QWidget *parent) :
    QMainWindow(parent), ui(new Ui::LivreDetail), page(page)
{
    setFixedSize(640,480);
    ui->setupUi(this);
    getList();
    getLivre(livreID);
}

LivreDetail::~LivreDetail()
{
    delete ui;
}

void LivreDetail::getList()
{
    if(DatabaseManager::openConnection()){
        listeAuteurs = Auteur::getAllAuteurs();
        ui->auteurComboBox->addItem("");
        for(const Auteur auteur : listeAuteurs){
            QString nomComplet = QString("%1 %2 (%3)").arg(auteur.nom).arg(auteur.prenom).arg(auteur.pseudo);
            ui->auteurComboBox->addItem(nomComplet);
        }
        ui->genreComboBox->addItem("");
        listeCategories = Categorie::getAllCategories();
        for(const Categorie categorie : listeCategories){
            ui->genreComboBox->addItem(QString("%1").arg(categorie.nom));
        }
        ui->editeurComboBox->addItem("");
        listeEditeurs = Editeur::getAllEditeurs();
        for(const Editeur editeur : listeEditeurs){
            ui->editeurComboBox->addItem(QString("%1").arg(editeur.nom));
        }
        ui->langueComboBox->addItem("");
        listeLangues = Langue::getAllLangues();
        for(const Langue langue : listeLangues){
            ui->langueComboBox->addItem(QString("%1").arg(langue.nom));
        }
        DatabaseManager::closeConnection();
    }
}



void LivreDetail::getLivre(int livreId)
{
    if(livreId != 0){
        if(DatabaseManager::openConnection()){
            DatabaseManager::closeConnection();
        }
    }
}
