#include "newmembrewindow.h"
#include "ui_newmembrewindow.h"
#include "manager/DatabaseManager.h"

#include <QMessageBox>

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
    /*if(DatabaseManager::openConnection()){
        listeAbonnements = Abonnement::getAllAbonnements();

        ui->abonnementMembrecomboBox->addItem("");
        for(const Abonnement &abonnement : listeAbonnements){
            QString nomComplet = QString("%1 (%3)J").arg(abonnement.nom).arg(abonnement.duree);
            ui->abonnementMembrecomboBox->addItem(nomComplet);
        }
        DatabaseManager::closeConnection();
    }*/
}

void NewMembreWindow::on_pushButtonMembre_clicked()
{
    QString nom = ui->nomMembre->text();
    QString prenom = ui->prenomMem->text();
    QString adresse = ui->adresseMembre->text();
    QString contact = ui->contactMembre->text();
    QDate naissance = ui->naissanceMembre->date();
    membre = Membre(nom, prenom, naissance, adresse, contact);
    if(DatabaseManager::openConnection()){
        Membre::addMembre(membre);
        DatabaseManager::closeConnection();
        QMessageBox::information(this, "Succès", "Membre enregistré !");
        this->close();
    }
}


void NewMembreWindow::closeEvent(QCloseEvent *event){
    emit closeWindow();
    QMainWindow::closeEvent(event);
}
