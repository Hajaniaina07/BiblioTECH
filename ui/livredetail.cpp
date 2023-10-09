#include "livredetail.h"
#include "ui_livredetail.h"
#include "model/livre.h"
#include "manager/DatabaseManager.h"

LivreDetail::LivreDetail(const int& page,Livre& livre, QWidget *parent) :
    QMainWindow(parent), ui(new Ui::LivreDetail), page(page),livre(livre)
{
    setFixedSize(640,480);
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(page);

    switch (page) {
    case 0:
        break;
    case 1:
        setDetailLivre();
        break;
    default:
        break;
    }
    ui->pageSpinBox->setMaximum(9999);
    ui->quantiteSpinBox->setMaximum(9999);
    getList();
    getLivre(livre);
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

void LivreDetail::setDetailLivre(){
    ui->titleLAbel->setText(livre.titre);
    ui->pageLabel->setText(QString("%1 %2").arg(livre.page).arg("Pages"));
    QString auteur = QString("%1 %2").arg(livre.auteur.prenom).arg(livre.auteur.nom);
    if(!livre.auteur.pseudo.isNull() && !livre.auteur.pseudo.isEmpty())
        auteur += QString(" (%1)").arg(livre.auteur.pseudo);
    ui->auteurLabel->setText(auteur);
    ui->editeurLabel->setText(livre.editeur.nom);
    ui->genreLabel->setText(livre.categorie.nom);
    ui->quantiteLabel->setText(QString("%1/%2").arg(livre.quantite).arg(livre.quantite));
    ui->langueLabel->setText(livre.langue.nom);
    ui->synopsisEdit->setPlainText(livre.resume);

    int day = livre.publication.day();
    QString month = livre.publication.toString("MMMM");
    int year = livre.publication.year();

    QString formattedDate = QString("%1 %2 %3").arg(day).arg(month).arg(year);

    ui->publicationLabel->setText(formattedDate);
}



void LivreDetail::getLivre(Livre livre)
{
    if(livre.titre.isEmpty() || livre.titre.isEmpty())
        if(livre.id != 0){
        if(DatabaseManager::openConnection()){
                livre = Livre::findLivreById(livre.id);
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
        this->close();
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

