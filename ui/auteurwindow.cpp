#include "auteurwindow.h"
#include "ui_auteurwindow.h"
#include "model/Auteur.h"
#include "manager/DatabaseManager.h"
#include <QMessageBox>

AuteurWindow::AuteurWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AuteurWindow)
{
    ui->setupUi(this);
    getList();
}

AuteurWindow::~AuteurWindow()
{
    delete ui;
}

void AuteurWindow::on_addButton_clicked()
{
    QString nom = ui->nomEdit->text();
    QString prenom = ui->prenomEdit->text();
    QDate date = ui->naissanceEdit->date();
    addAuteur(Auteur(nom, prenom, date));
    getList();
}

void AuteurWindow::addAuteur(const Auteur& auteur)
{
    if (DatabaseManager::openConnection()) {
        Auteur::addAuteur(auteur);
        ui->nomEdit->clear();
        ui->prenomEdit->clear();
        ui->naissanceEdit->clear();
        DatabaseManager::closeConnection();
    }
}

void AuteurWindow::removeAuteur(const Auteur& auteur)
{
    if (DatabaseManager::openConnection()) {
        Auteur::deleteAuteur(auteur.id);
        DatabaseManager::closeConnection();
    }
}

void  AuteurWindow::getList()
{
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->verticalHeader()->setVisible(false);
    setupTable();

    if (DatabaseManager::openConnection()) {
        listeAuteurs = Auteur::getAllAuteurs();

        int row = 0;
        for (const Auteur& auteur : listeAuteurs) {
            ui->tableWidget->insertRow(row);
            ui->tableWidget->setItem(row, 0, new QTableWidgetItem(auteur.nom));
            ui->tableWidget->setItem(row, 1, new QTableWidgetItem(auteur.prenom));
            QTableWidgetItem *naissanceItem = new QTableWidgetItem(auteur.naissance.toString("dd/MM/yyyy"));
            naissanceItem->setTextAlignment(Qt::AlignCenter | Qt::AlignVCenter);
            ui->tableWidget->setItem(row, 2, naissanceItem);
            row++;
        }
        DatabaseManager::closeConnection();
    }
}

void AuteurWindow::setupTable()
{
    int numberOfColumns = 3;
    int columnWidth = ui->tableWidget->width() / numberOfColumns;

    for (int column = 0; column < numberOfColumns; ++column) {
        ui->tableWidget->setColumnWidth(column, columnWidth);
    }
}


void AuteurWindow::on_tableWidget_cellClicked(int row)
{
    auteur = listeAuteurs.at(row);
}


void AuteurWindow::on_editButton_clicked()
{
    if(auteur.id != 0){
        int row = listeAuteurs.indexOf(auteur);
        QString nom = ui->tableWidget->item(row, 0)->data(Qt::DisplayRole).toString();
        QString prenom = ui->tableWidget->item(row, 1)->data(Qt::DisplayRole).toString();
        QString naissance = ui->tableWidget->item(row, 2)->data(Qt::DisplayRole).toString();

        bool edited = (auteur.nom!=nom || auteur.prenom!=prenom
                       || auteur.naissance.toString("dd/MM/yyyy") != naissance);

        if(edited){
            QDate date = QDate::fromString(naissance, "dd/MM/yyyy");
            if (date.isValid()) {
                QMessageBox::StandardButton reply;
                reply = QMessageBox::question(this, "Confirmation", "Voulez-vous vraiment modifier " + auteur.nom +" "+ auteur.prenom, QMessageBox::Yes|QMessageBox::No);
                if (reply == QMessageBox::Yes) {
                    auteur.nom=nom; auteur.prenom=prenom ;
                    auteur.naissance = date;
                    if (DatabaseManager::openConnection()) {
                        Auteur::updateAuteur(auteur);
                        DatabaseManager::closeConnection();
                    }
                }
            } else {
                QMessageBox::information(nullptr, "Information", "Date de naissance invalide.");
            }
        }



    }
}


void AuteurWindow::on_deleteButton_clicked()
{
    if(auteur.id != 0){
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Confirmation", "Voulez-vous vraiment supprimer " + auteur.nom +" "+ auteur.prenom, QMessageBox::Yes|QMessageBox::No);

        if (reply == QMessageBox::Yes) {
            removeAuteur(auteur);
            auteur = Auteur();
            getList();
        }
    }
}

void AuteurWindow::closeEvent(QCloseEvent *event){
    emit closeWindow();
    QMainWindow::closeEvent(event);
}
