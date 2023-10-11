#include "membreabonnementwindow.h"
#include "ui_membreabonnementwindow.h"
#include "manager/DatabaseManager.h"
#include "util/util.h"

#include <QMessageBox>

MembreAbonnementWindow::MembreAbonnementWindow(AbonnementMembre& am, QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MembreAbonnementWindow),am(am)
{
    ui->setupUi(this);
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
    int indexSelectedAbonnement = Util::getSelectedItem(ui->abonnementComboBox);
    if(indexSelectedAbonnement >= 0){
        Abonnement abonnement = listeAbonnements[indexSelectedAbonnement];
        QDate debut =ui->dateDebutAbonnementEdit->date();
        QDate fin = debut.addDays(abonnement.duree);
        if(DatabaseManager::openConnection()){
            AbonnementMembre am = AbonnementMembre(membre, abonnement, debut, fin);
            AbonnementMembre::addAbonnementMembre(am);
            DatabaseManager::closeConnection();
            ui->abonnementComboBox->clear();
            getListAbonnements();
        }
    }
}


void MembreAbonnementWindow::on_editButton_clicked()
{
    ui->widgetDetail->setVisible(false);
    ui->newAbonnementWidget->setVisible(false);
    ui->widgetEdit->setVisible(true);
}


void MembreAbonnementWindow::on_confirmEditButton_clicked()
{
    membre.nom = ui->nomEdit->text();
    membre.prenom = ui->prenomEdit->text();
    membre.adresse = ui->adresseEdit->text();
    membre.contact = ui->contactEdit->text();
    membre.naissance = ui->dateNaissanceEdit->date();
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirmation", "Voulez-vous vraiment enregistrer cette modification? ", QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        if(DatabaseManager::openConnection()){
            Membre::updateMembre(membre);
            DatabaseManager::closeConnection();
            QMessageBox::information(this, "Succés", "Modification enregistré");
            getMembre();
        }
    }
}


void MembreAbonnementWindow::on_cancelEditButton_clicked()
{
    ui->widgetEdit->setVisible(false);
    ui->widgetDetail->setVisible(true);
    ui->newAbonnementWidget->setVisible(true);
}


void MembreAbonnementWindow::getMembre(){

    ui->widgetEdit->setVisible(false);

    if(DatabaseManager::openConnection()){
        membre = Membre::getById(am.membre.id);
        ui->nom_dl->setText(membre.nom);
        ui->prenom_dl->setText(membre.prenom);
        ui->contact_dl->setText(membre.contact);
        ui->adresse_dl->setText(membre.adresse);
        int day = membre.naissance.day();
        QString month = QLocale(QLocale::French).monthName(membre.naissance.month());
        int year = membre.naissance.year();
        QString formattedDate = QString("%1 %2 %3").arg(day).arg(month).arg(year);
        ui->naissance_dl->setText(formattedDate);
        DatabaseManager::closeConnection();
    }
}

void MembreAbonnementWindow::getListAbonnements(){
    ui->amTableWidget->setRowCount(0);
    ui->amTableWidget->verticalHeader()->setVisible(false);
    ui->amTableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    if(DatabaseManager::openConnection()){
        ams = AbonnementMembre::getAbonnementMembreByMembreId(membre.id);
        int row = 0;
        for(const AbonnementMembre& am : ams){
            ui->amTableWidget->insertRow(row);
            ui->amTableWidget->setItem(row, 0, new QTableWidgetItem(am.abonnement.nom));
            ui->amTableWidget->setItem(row, 1, new QTableWidgetItem(am.debut.toString("dd/MM/yyyy")));
            QTableWidgetItem *finItem = new QTableWidgetItem(am.fin.toString("dd/MM/yyyy"));
            QDate currentDate = QDate::currentDate();
            if(am.fin < currentDate){
                finItem->setForeground(QBrush(Qt::red));
            }else finItem->setForeground(QBrush(Qt::green));
            ui->amTableWidget->setItem(row, 2, finItem);


            ui->amTableWidget->item(row,0)->setTextAlignment(Qt::AlignCenter | Qt::AlignVCenter);
            ui->amTableWidget->item(row,1)->setTextAlignment(Qt::AlignCenter | Qt::AlignVCenter);
            ui->amTableWidget->item(row,2)->setTextAlignment(Qt::AlignCenter | Qt::AlignVCenter);

            row ++;
        }
        DatabaseManager::closeConnection();
    }
}

void MembreAbonnementWindow::setListAbonnement(){
    ui->dateDebutAbonnementEdit->setDate(QDate::currentDate());
    if(DatabaseManager::openConnection()){
        listeAbonnements = Abonnement::getAllAbonnements();
        ui->abonnementComboBox->addItem("");
        for(const Abonnement &abonnement : listeAbonnements){
            QString nomComplet = QString("%1 (%2J)").arg(abonnement.nom).arg(abonnement.duree);
            ui->abonnementComboBox->addItem(nomComplet);
        }
        DatabaseManager::closeConnection();
    }
}

void MembreAbonnementWindow::on_amTableWidget_cellDoubleClicked(int row)
{
    AbonnementMembre am = ams.at(row);
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirmation", "Voulez-vous supprimer cette ligne? ", QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        if(DatabaseManager::openConnection()){
            AbonnementMembre::deleteAbonnementMembre(am.id);
            DatabaseManager::closeConnection();
            QMessageBox::information(this, "Succés", "Abonnement supprimé");
            getListAbonnements();
        }
    }
}


void MembreAbonnementWindow::closeEvent(QCloseEvent *event){
    emit closeWindow();
    QMainWindow::closeEvent(event);
}
