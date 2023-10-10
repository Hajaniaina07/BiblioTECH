#include "newempruntwindow.h"
#include "ui_newempruntwindow.h"
#include "manager/DatabaseManager.h"
#include "model/emprunt.h"
#include "util/util.h"
#include "util/boolResult.h"
#include <QMessageBox>
#include <QStandardItemModel>
#include <QCompleter>
#include <QSortFilterProxyModel>
#include <QLineEdit>


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
    ui->dateUmpruntEdit->setDate(QDate::currentDate());

    if(DatabaseManager::openConnection()){
        listeLivres = Livre::getAllLivres();
        ui->livresComboBox->setEditable(true);

        QStandardItemModel *model = new QStandardItemModel(this);
        model->appendRow(new QStandardItem(""));  // Ajoutez une ligne vide

        for (const Livre &livre : listeLivres) {
            QString nomComplet = QString("%1 | %2 %3").arg(livre.titre).arg(livre.auteur.prenom).arg(livre.auteur.nom);
            QStandardItem *item = new QStandardItem(nomComplet);
            model->appendRow(item);
        }

        QSortFilterProxyModel *proxyModel = new QSortFilterProxyModel(this);
        proxyModel->setSourceModel(model);
        proxyModel->setFilterCaseSensitivity(Qt::CaseInsensitive);

        QCompleter *completer = new QCompleter(proxyModel, this);
        completer->setCaseSensitivity(Qt::CaseInsensitive);


         ui->livresComboBox->setModel(proxyModel);
         ui->livresComboBox->setCompleter(completer);

        listeMembres = Membre::getAllMembres();
        ui->membreComboBox->setEditable(true);

        QStandardItemModel *modelM = new QStandardItemModel(this);
        modelM->appendRow(new QStandardItem(""));

        for(const Membre &membre : listeMembres){
            QString nomComplet = QString("%1 %2").arg(membre.nom).arg(membre.prenom);
            QStandardItem *item = new QStandardItem(nomComplet);
            modelM->appendRow(item);
        }

        QSortFilterProxyModel *proxyModelM = new QSortFilterProxyModel(this);
        proxyModelM->setSourceModel(modelM);
        proxyModelM->setFilterCaseSensitivity(Qt::CaseInsensitive);

        QCompleter *completerM = new QCompleter(proxyModelM, this);
        completerM->setCaseSensitivity(Qt::CaseInsensitive);


         ui->membreComboBox->setModel(proxyModelM);
         ui->membreComboBox->setCompleter(completerM);


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

    if(indexSelectedMembre > -1 && indexSelectedLivre > -1){
        livre = listeLivres[indexSelectedLivre];
        membre = listeMembres[indexSelectedMembre];
        QDate dateEmprunt = ui->dateUmpruntEdit->date();
        Emprunt emprunt = Emprunt(livre,membre,dateEmprunt);
        if(DatabaseManager::openConnection()){
            BoolResult validation = Emprunt::validateEmprunt(emprunt);
            if(validation.validate){
                Emprunt::addEmprunt(emprunt);
                QMessageBox::information(this, "Succès", "Emprunt enregistré !");
                DatabaseManager::closeConnection();
                this->close();
            }else{
                QMessageBox::critical(this, "Emprunt non autorisé", validation.message);
                DatabaseManager::closeConnection();
            }
        }
    }

}

