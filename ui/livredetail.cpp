#include "livredetail.h"
#include "ui_livredetail.h"
#include "model/livre.h"
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

void LivreDetail::on_addLivreButton_clicked()
{
    int indexSelectedAuteur = getSelectedItem(ui->auteurComboBox);
    int indexSelectedCategorie = getSelectedItem(ui->genreComboBox);
    int indexSelectedEditeur = getSelectedItem(ui->editeurComboBox);
    int indexSelectedLangue = getSelectedItem(ui->langueComboBox);
    int page = ui->pageSpinBox->value();
    int quantite = ui->quantiteSpinBox->value();
    QString titre = ui->titreEdit->text();
    QString resume = ui->resumeTextEdit->toPlainText();
    QDate publication = ui->publicationDateEdit->date();
    Auteur auteur = listeAuteurs[indexSelectedAuteur];
    Categorie categorie = listeCategories[indexSelectedCategorie];
    Editeur editeur = listeEditeurs[indexSelectedEditeur];
    Langue langue = listeLangues[indexSelectedLangue];
    Livre livre = Livre(auteur, categorie, editeur, langue, titre, page, publication, resume, quantite);
    if(DatabaseManager::openConnection()){
        Livre::addLivre(livre);
        DatabaseManager::closeConnection();
    }
}

int LivreDetail::getSelectedItem(QComboBox* comboBox)
{
    int indexSelected = comboBox->currentIndex();
    if (indexSelected > 0)
    {
        return indexSelected - 1;
    }
    return -1;
}

