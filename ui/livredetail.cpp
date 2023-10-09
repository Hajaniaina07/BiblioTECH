#include "livredetail.h"
#include "ui_livredetail.h"
#include "model/livre.h"
#include "manager/DatabaseManager.h"
#include <QMessageBox>

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
        ui->auteurComboBox_2->addItem("");
        for(const Auteur auteur : listeAuteurs){
            QString nomComplet = QString("%1 %2 (%3)").arg(auteur.nom).arg(auteur.prenom).arg(auteur.pseudo);
            ui->auteurComboBox->addItem(nomComplet);
            ui->auteurComboBox_2->addItem(nomComplet);
        }
        ui->genreComboBox->addItem("");
        ui->genreComboBox_2->addItem("");
        listeCategories = Categorie::getAllCategories();
        for(const Categorie categorie : listeCategories){
            ui->genreComboBox->addItem(QString("%1").arg(categorie.nom));
            ui->genreComboBox_2->addItem(QString("%1").arg(categorie.nom));
        }
        ui->editeurComboBox->addItem("");
        ui->editeurComboBox_2->addItem("");
        listeEditeurs = Editeur::getAllEditeurs();
        for(const Editeur editeur : listeEditeurs){
            ui->editeurComboBox->addItem(QString("%1").arg(editeur.nom));
            ui->editeurComboBox_2->addItem(QString("%1").arg(editeur.nom));
        }
        ui->langueComboBox->addItem("");
        ui->langueComboBox_2->addItem("");
        listeLangues = Langue::getAllLangues();
        for(const Langue langue : listeLangues){
            ui->langueComboBox->addItem(QString("%1").arg(langue.nom));
            ui->langueComboBox_2->addItem(QString("%1").arg(langue.nom));
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


void LivreDetail::on_editLivreButton_clicked()
{
    int indexSelectedAuteur = getIndex(livre.auteur.id, listeAuteurs)+1;
    int indexSelectedCategorie = getIndex(livre.categorie.id, listeCategories)+1;
    int indexSelectedEditeur = getIndex(livre.editeur.id, listeEditeurs)+1;
    int indexSelectedLangue = getIndex(livre.langue.id, listeLangues)+1;
    ui->stackedWidget->setCurrentIndex(2);
    ui->auteurComboBox_2->setCurrentIndex(indexSelectedAuteur);
    ui->genreComboBox_2->setCurrentIndex(indexSelectedCategorie);
    ui->editeurComboBox_2->setCurrentIndex(indexSelectedEditeur);
    ui->langueComboBox_2->setCurrentIndex(indexSelectedLangue);
    ui->pageSpinBox_2->setValue(livre.page);
    ui->quantiteSpinBox_2->setValue(livre.quantite);
    ui->titreEdit_2->setText(livre.titre);
    ui->resumeTextEdit_2->setPlainText(livre.resume);
    ui->publicationDateEdit_2->setDate(livre.publication);
}

template<typename T>
int LivreDetail::getIndex(int id, const QList<T>& list) {
    for (int i = 0; i < list.size(); ++i) {
        if (list[i].id == id) {
        return i;
        }
    }
    return -1;
}


void LivreDetail::on_cancelButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}


void LivreDetail::on_saveEditButton_clicked()
{
    QMessageBox::StandardButton msgBox;
    msgBox = QMessageBox::question(this, "Confirmation", "Voulez-vous vraiment enregistrer les modifications?", QMessageBox::Yes|QMessageBox::No);
    if (msgBox  == QMessageBox::Yes) {
        int indexSelectedAuteur = getSelectedItem(ui->auteurComboBox_2);
        int indexSelectedCategorie = getSelectedItem(ui->genreComboBox_2);
        int indexSelectedEditeur = getSelectedItem(ui->editeurComboBox_2);
        int indexSelectedLangue = getSelectedItem(ui->langueComboBox_2);
        int page = ui->pageSpinBox_2->value();
        int quantite = ui->quantiteSpinBox_2->value();
        QString titre = ui->titreEdit_2->text();
        QString resume = ui->resumeTextEdit_2->toPlainText();
        QDate publication = ui->publicationDateEdit_2->date();
        Auteur auteur = listeAuteurs[indexSelectedAuteur];
        Categorie categorie = listeCategories[indexSelectedCategorie];
        Editeur editeur = listeEditeurs[indexSelectedEditeur];
        Langue langue = listeLangues[indexSelectedLangue];
        livre = Livre(livre.id, auteur, categorie, editeur, langue, titre, page, publication, resume, quantite);
        if(DatabaseManager::openConnection()){
            Livre::updateLivre(livre);
            DatabaseManager::closeConnection();
            setDetailLivre();
            QMessageBox::information(this, "Succès", "Modification enregistré !");
            ui->stackedWidget->setCurrentIndex(1);
        }
    }else{
        ui->stackedWidget->setCurrentIndex(1);
    }


}

