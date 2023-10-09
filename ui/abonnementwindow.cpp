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
    QString nom = ui->nomEdit->text();
    int duree = ui->duree->value();
    int max_emprunt_sim = ui->maxEmprunt->value();
    int max_duree_unit = ui->maxDuree->value();
    Abonnement abonnement = Abonnement(nom, duree, max_emprunt_sim,max_duree_unit);
    if(DatabaseManager::openConnection()){
        Abonnement::addAbonnement(abonnement);
        DatabaseManager::closeConnection();
        ui->nomEdit->clear();
        ui->duree->clear();
        ui->maxEmprunt->clear();
        ui->maxDuree->clear();
        getList();
    }
}

void AbonnementWindow::getList(){
    ui->abonnementTableWidget->verticalHeader()->setVisible(false);
    ui->abonnementTableWidget->setColumnWidth(0, 250);
    ui->abonnementTableWidget->setColumnWidth(2, 150);
    ui->abonnementTableWidget->setRowCount(0);
    if(DatabaseManager::openConnection()){
        listeAbonnements = Abonnement::getAllAbonnements();
        int row = 0;
        for (const Abonnement& abonnement : listeAbonnements) {
            ui->abonnementTableWidget->insertRow(row);
            ui->abonnementTableWidget->setItem(row, 0, new QTableWidgetItem(abonnement.nom));
            ui->abonnementTableWidget->setItem(row, 1, new QTableWidgetItem(QString::number(abonnement.duree)));
            ui->abonnementTableWidget->setItem(row, 2, new QTableWidgetItem(QString::number(abonnement.maxEmpruntSimultane)));
            ui->abonnementTableWidget->setItem(row, 3, new QTableWidgetItem(QString::number(abonnement.maxDureeEmpruntUnitaire)));
            row++;
        }
        DatabaseManager::closeConnection();
    }
    ui->abonnementTableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->abonnementTableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}


void AbonnementWindow::on_abonnementTableWidget_cellDoubleClicked(int row, int column)
{
    Abonnement abonnement = listeAbonnements[row];
    ui->nomEdit->setText(abonnement.nom);
    ui->duree->setValue(abonnement.duree);
    ui->maxEmprunt->setValue(abonnement.maxEmpruntSimultane);
    ui->maxDuree->setValue(abonnement.maxDureeEmpruntUnitaire);
    ui->addNewButton->setText("Modifier");
    connect(ui->addNewButton, &QPushButton::clicked, this, &AbonnementWindow::update);
}

void AbonnementWindow:: update(){
    abonnement.nom = ui->nomEdit->text();
    abonnement.duree = ui->duree->value();
    abonnement.maxDureeEmpruntUnitaire = ui->maxEmprunt->value();
    abonnement.maxEmpruntSimultane = ui->maxDuree->value();
    if(DatabaseManager::openConnection()){
        Abonnement::updateAbonnement(abonnement);
        DatabaseManager::closeConnection();
        ui->nomEdit->clear();
        ui->duree->clear();
        ui->maxEmprunt->clear();
        ui->maxDuree->clear();
        ui->addNewButton->setText("Ajouer un nouveau type d'abonnement");
        connect(ui->addNewButton, &QPushButton::clicked, this, &AbonnementWindow::on_addNewButton_clicked);
        getList();
    }
}
