#include "newempruntwindow.h"
#include "ui_newempruntwindow.h"
#include "manager/DatabaseManager.h"

NewEmpruntWindow::NewEmpruntWindow(const int& page,Livre& livre,Membre& membre, QWidget *parent) :
    QMainWindow(parent),ui(new Ui::NewEmpruntWindow),livre(livre),membre(membre)
{
    setFixedSize(320,250);
    ui->setupUi(this);
    getList();
    setSelectedItems();
}

NewEmpruntWindow::~NewEmpruntWindow()
{
    delete ui;
}



void NewEmpruntWindow::getList(){
    ui->dateUmpruntEdit->setDate(QDate());
    if(DatabaseManager::openConnection()){
        listeLivres = Livre::getAllLivres();
        ui->livresComboBox->addItem("");
        for(const Livre &livre : listeLivres){
            QString nomComplet = QString("%1 | %2 %3").arg(livre.titre).arg(livre.auteur.prenom).arg(livre.auteur.nom);
            ui->livresComboBox->addItem(nomComplet);
        }

        listeMembres = Membre::getAllMembres();
        ui->membreComboBox->addItem("");
        for(const Membre &membre : listeMembres){
            QString nomComplet = QString("%1 %2").arg(membre.nom).arg(membre.prenom);
            ui->membreComboBox->addItem(nomComplet);
        }
        DatabaseManager::closeConnection();
    }
}

void NewEmpruntWindow::setSelectedItems(){
    if(livre.id > 0){
        for(int i = 0; i < listeLivres.length(); i++){
            if(listeLivres[i].id == livre.id){
                ui->livresComboBox->setCurrentIndex(i+1);
                ui->livresComboBox->setEditable(false);
                ui->livresComboBox->setEnabled(false);
                break;
            }
        }
    }
    if(membre.id > 0){
        for(int i = 0; i < listeMembres.length(); i++){
            if(listeMembres[i].id == membre.id){
                ui->membreComboBox->setCurrentIndex(i+1);
                ui->membreComboBox->setEditable(false);
                ui->membreComboBox->setEnabled(false);
                break;
            }
        }
    }
}

void NewEmpruntWindow::on_validateEmpruntButton_clicked()
{
    int indexSelectedLivre = Util::getSelectedItem(ui->livresComboBox);
    int indexSelectedMembre = Util::getSelectedItem(ui->membreComboBox);
    livre = listeLivres[indexSelectedLivre];
    membre = listeMembres[indexSelectedMembre];
    QDate dateEmprunt = ui->dateUmpruntEdit->date();
}

