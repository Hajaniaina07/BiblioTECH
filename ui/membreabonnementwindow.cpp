#include "membreabonnementwindow.h"
#include "ui_membreabonnementwindow.h"
#include "manager/DatabaseManager.h"

MembreAbonnementWindow::MembreAbonnementWindow(AbonnementMembre& am, QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MembreAbonnementWindow),am(am)
{
    ui->setupUi(this);
    ui->widgetEdit->setVisible(false);
    getMembre();
    setListAbonnement();
    getListAbonnements();
}

MembreAbonnementWindow::~MembreAbonnementWindow()
{
    delete ui;
}

void MembreAbonnementWindow::on_newAbonnementButton_clicked()
{

}


void MembreAbonnementWindow::on_editButton_clicked()
{
    ui->widgetDetail->setVisible(false);
    ui->newAbonnementWidget->setVisible(false);
    ui->widgetEdit->setVisible(true);
}


void MembreAbonnementWindow::on_confirmEditButton_clicked()
{

}


void MembreAbonnementWindow::on_cancelEditButton_clicked()
{
    ui->widgetEdit->setVisible(false);
    ui->widgetDetail->setVisible(true);
    ui->newAbonnementWidget->setVisible(true);
}


void MembreAbonnementWindow::getMembre(){
    if(DatabaseManager::openConnection()){
        membre = Membre::getById(am.membre.id);
        ui->nom_dl->setText(membre.nom);
        ui->prenom_dl->setText(membre.prenom);
        ui->contact_dl->setText(membre.contact);
        ui->adresse_dl->setText(membre.adresse);
        int day = membre.naissance.day();
        QString month = membre.naissance.toString("MMMM");
        int year = membre.naissance.year();
        QString formattedDate = QString("%1 %2 %3").arg(day).arg(month).arg(year);
        ui->naissance_dl->setText(formattedDate);
        DatabaseManager::closeConnection();
    }
}

void MembreAbonnementWindow::getListAbonnements(){
    ui->amTableWidget->setRowCount(0);
    ui->amTableWidget->verticalHeader()->setVisible(false);
    if(DatabaseManager::openConnection()){
        ams = AbonnementMembre::getAbonnementMembreByMembreId(am.membre.id);
        int row = 0;
        for(const AbonnementMembre& am : ams){
            ui->amTableWidget->setItem(row, 0, new QTableWidgetItem(am.abonnement.nom));
            ui->amTableWidget->setItem(row, 1, new QTableWidgetItem(am.debut.toString("dd/MM/yyyy")));
            QTableWidgetItem *finItem = new QTableWidgetItem(am.fin.toString("dd/MM/yyyy"));
            QDate currentDate = QDate::currentDate();
            if(am.fin < currentDate){
                finItem->setForeground(QBrush(Qt::red));
            }else finItem->setForeground(QBrush(Qt::green));
            ui->amTableWidget->setItem(row, 2, finItem);
            row ++;
        }
        DatabaseManager::closeConnection();
    }
}

void MembreAbonnementWindow::setListAbonnement(){
    if(DatabaseManager::openConnection()){
        listeAbonnements = Abonnement::getAllAbonnements();
        ui->abonnementComboBox->addItem("");
        for(const Abonnement &abonnement : listeAbonnements){
            QString nomComplet = QString("%1 (%3)J").arg(abonnement.nom).arg(abonnement.duree);
            ui->abonnementComboBox->addItem(nomComplet);
        }
        DatabaseManager::closeConnection();
    }
}
