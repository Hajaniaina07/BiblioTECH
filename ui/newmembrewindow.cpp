#include "newmembrewindow.h"
#include "ui_newmembrewindow.h"
#include "manager/DatabaseManager.h"
#include "model/abonnementmembre.h"
#include "util/util.h"

NewMembreWindow::NewMembreWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::NewMembreWindow)
{
    ui->setupUi(this);
    getList();
}

NewMembreWindow::~NewMembreWindow()
{
    delete ui;
}


void NewMembreWindow::getList(){
    if(DatabaseManager::openConnection()){
        listeAbonnements = Abonnement::getAllAbonnements();

        ui->abonnementMembrecomboBox->addItem("");
        for(const Abonnement &abonnement : listeAbonnements){
            QString nomComplet = QString("%1 (%3)J").arg(abonnement.nom).arg(abonnement.duree);
            ui->abonnementMembrecomboBox->addItem(nomComplet);
        }
        DatabaseManager::closeConnection();
    }
}

void NewMembreWindow::on_pushButtonMembre_clicked()
{
    QString nom = ui->nomMembre->text();
    QString prenom = ui->prenomMem->text();
    QString adresse = ui->adresseMembre->text();
    QString contact = ui->contactMembre->text();
    QDate naissance = ui->naissanceMembre->date();
    membre = Membre(nom, prenom, naissance, adresse, contact);
    int indexSelectedAbonnement = Util::getSelectedItem(ui->abonnementMembrecomboBox);
    Abonnement abonnement = listeAbonnements[indexSelectedAbonnement];
    QDate debut = QDate::currentDate();
    QDate fin = debut.addDays(abonnement.duree);
    if(DatabaseManager::openConnection()){
        int idMembre = Membre::addMembre(membre);
        membre.id = idMembre;
        DatabaseManager::closeConnection();
        if(DatabaseManager::openConnection()){
            AbonnementMembre am = AbonnementMembre(membre, abonnement, debut, fin);
            AbonnementMembre::addAbonnementMembre(am);
            DatabaseManager::closeConnection();
        }
    }
}
