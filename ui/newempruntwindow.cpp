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


NewEmpruntWindow::NewEmpruntWindow(Emprunt& emprunt, QWidget *parent) :
    QMainWindow(parent),ui(new Ui::NewEmpruntWindow),emprunt(emprunt)
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
            QString nomComplet = QString("%1 | %2 %3").arg(livre.titre).arg(livre.auteur.prenom).arg(emprunt.livre.auteur.nom);
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
    if(emprunt.livre.id > 0){
        for(int i = 0; i < listeLivres.length(); i++){
            if(listeLivres[i].id == emprunt.livre.id){
                ui->livresComboBox->setCurrentIndex(i+1);
                ui->livresComboBox->setEditable(false);
                ui->livresComboBox->setEnabled(false);
                break;
            }
        }
    }
    if(emprunt.membre.id > 0){
        for(int i = 0; i < listeMembres.length(); i++){
            if(listeMembres[i].id == emprunt.membre.id){
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
    if(emprunt.id != 0){
        int maxDay = emprunt.dateEmprunt.daysTo(emprunt.dateMax);
        emprunt.dateEmprunt = ui->dateUmpruntEdit->date();
        emprunt.dateMax = emprunt.dateEmprunt.addDays(maxDay);
        if(DatabaseManager::openConnection()){
            Emprunt::updateEmprunt(emprunt);
            QMessageBox::information(this, "Succès", "Date emprunt modifiié !");
            DatabaseManager::closeConnection();
            this->close();
        }
    }else{
        int indexSelectedLivre = Util::getSelectedItem(ui->livresComboBox);
        int indexSelectedMembre = Util::getSelectedItem(ui->membreComboBox);

        emprunt.dateEmprunt = ui->dateUmpruntEdit->date();
        if(indexSelectedMembre > -1 && indexSelectedLivre > -1){
            emprunt.livre = listeLivres[indexSelectedLivre];
            emprunt.membre = listeMembres[indexSelectedMembre];
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

}


void NewEmpruntWindow::closeEvent(QCloseEvent *event){
    emit closeWindow();
    QMainWindow::closeEvent(event);
}
