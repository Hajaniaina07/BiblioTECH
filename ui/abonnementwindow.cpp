#include "ui/abonnementwindow.h"
#include "ui_abonnementwindow.h"
#include "manager/DatabaseManager.h"

AbonnementWindow::AbonnementWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AbonnementWindow)
{
    ui->setupUi(this);
    ui->maxDuree->setMaximum(9999);
    ui->duree->setMaximum(9999);
    ui->maxEmprunt->setMaximum(9999);
    getList();
}

AbonnementWindow::~AbonnementWindow()
{
    delete ui;
}

void AbonnementWindow::on_addNewButton_clicked()
{
    if(validate()){
        QString nom = ui->nomEdit->text();
        int duree = ui->duree->value();
        int max_emprunt_sim = ui->maxEmprunt->value();
        int max_duree_unit = ui->maxDuree->value();
        abonnement = Abonnement(nom, duree, max_emprunt_sim,max_duree_unit);
        if(DatabaseManager::openConnection()){
            Abonnement::addAbonnement(abonnement);
            DatabaseManager::closeConnection();
            getList();
        }
    }
}

void AbonnementWindow::getList(){
    abonnement = Abonnement();
    ui->nomEdit->clear();
    ui->duree->clear();
    ui->maxEmprunt->clear();
    ui->maxDuree->clear();

    ui->addNewButton->setEnabled(true);
    ui->cancelButton->setEnabled(false);
    ui->editButton->setEnabled(false);
    ui->deleteButton->setEnabled(false);

    ui->abonnementTableWidget->verticalHeader()->setVisible(false);
    ui->abonnementTableWidget->setColumnWidth(0, 250);
    ui->abonnementTableWidget->setColumnWidth(2, 150);
    ui->abonnementTableWidget->setRowCount(0);
    if(DatabaseManager::openConnection()){
        listeAbonnements = Abonnement::getAllAbonnements();
        int row = 0;
        for (const Abonnement& abonnement : listeAbonnements) {
            int row = ui->abonnementTableWidget->rowCount();
            ui->abonnementTableWidget->insertRow(row);

            QTableWidgetItem* itemNom = new QTableWidgetItem(abonnement.nom);
            itemNom->setTextAlignment(Qt::AlignCenter);
            ui->abonnementTableWidget->setItem(row, 0, itemNom);

            QTableWidgetItem* itemDuree = new QTableWidgetItem(QString::number(abonnement.duree));
            itemDuree->setTextAlignment(Qt::AlignCenter);
            ui->abonnementTableWidget->setItem(row, 1, itemDuree);

            QTableWidgetItem* itemMaxEmprunt = new QTableWidgetItem(QString::number(abonnement.maxEmpruntSimultane));
            itemMaxEmprunt->setTextAlignment(Qt::AlignCenter);
            ui->abonnementTableWidget->setItem(row, 2, itemMaxEmprunt);

            QTableWidgetItem* itemMaxDuree = new QTableWidgetItem(QString::number(abonnement.maxDureeEmpruntUnitaire));
            itemMaxDuree->setTextAlignment(Qt::AlignCenter);
            ui->abonnementTableWidget->setItem(row, 3, itemMaxDuree);

            row++;
        }

        DatabaseManager::closeConnection();
    }
    ui->abonnementTableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->abonnementTableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}


void AbonnementWindow::on_abonnementTableWidget_cellDoubleClicked(int row)
{
    abonnement = listeAbonnements[row];
    ui->nomEdit->setText(abonnement.nom);
    ui->duree->setValue(abonnement.duree);
    ui->maxEmprunt->setValue(abonnement.maxEmpruntSimultane);
    ui->maxDuree->setValue(abonnement.maxDureeEmpruntUnitaire);


    ui->addNewButton->setEnabled(false);
    ui->cancelButton->setEnabled(true);
    ui->editButton->setEnabled(true);
    ui->deleteButton->setEnabled(true);
}

void AbonnementWindow:: update(){
    if(validate()){
        abonnement.nom = ui->nomEdit->text();
        abonnement.duree = ui->duree->value();
        abonnement.maxEmpruntSimultane = ui->maxEmprunt->value();
        abonnement.maxDureeEmpruntUnitaire = ui->maxDuree->value();
        qDebug() << abonnement.id << abonnement.nom << abonnement.duree << abonnement.maxEmpruntSimultane << abonnement.maxDureeEmpruntUnitaire;
        if(DatabaseManager::openConnection()){
            Abonnement::updateAbonnement(abonnement);
            DatabaseManager::closeConnection();
            getList();
        }
    }
}


void AbonnementWindow::closeEvent(QCloseEvent *event){
    emit closeWindow();
    QMainWindow::closeEvent(event);
}

void AbonnementWindow::on_cancelButton_clicked()
{
    abonnement = Abonnement();
    getList();
}


void AbonnementWindow::on_editButton_clicked()
{
    update();
}


void AbonnementWindow::on_deleteButton_clicked()
{
    if(DatabaseManager::openConnection()){
        Abonnement::deleteAbonnement(abonnement.id);
        DatabaseManager::closeConnection();
        ui->nomEdit->clear();
        ui->duree->clear();
        ui->maxEmprunt->clear();
        ui->maxDuree->clear();
        abonnement = Abonnement();
        getList();
    }
}

bool AbonnementWindow:: validate(){
    return (ui->nomEdit && !ui->nomEdit->text().isEmpty() &&
            ui->duree && ui->duree->value() != 0 &&
            ui->maxEmprunt && ui->maxEmprunt->value() != 0 &&
            ui->maxDuree && ui->maxDuree->value() != 0);
}
