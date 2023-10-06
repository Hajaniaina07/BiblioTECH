#include "ui/livrewindow.h"
#include "ui_livrewindow.h"
#include "manager/DatabaseManager.h"
#include <QMessageBox>

LivreWindow::LivreWindow(const QString& type, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::livrewindow), type(type)
{
    setFixedSize(250,300);
    ui->setupUi(this);
    getList();
}

LivreWindow::~LivreWindow()
{
    delete ui;
}

void LivreWindow::getList() {
    baseModels.clear();
    baseModel = BaseModel();
    if (type == "categorie") {
        getListCategorie();
    } else if (type == "editeur") {
        getListEditeur();
    } else if (type == "langue") {
        getListLangue();
    }

    ui->tableWidget->setColumnCount(1);
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->horizontalHeader()->setVisible(false);
    ui->tableWidget->verticalHeader()->setVisible(false);

    int row = 0;
    for (const BaseModel& bm : baseModels) {
        ui->tableWidget->insertRow(row);
        ui->tableWidget->setItem(row, 0, new QTableWidgetItem(bm.nom));
        row++;
    }
    ui->tableWidget->setColumnWidth(0, ui->tableWidget->width());
}


void LivreWindow::getListCategorie(){
     if(DatabaseManager::openConnection()){
        listeCategories = Categorie::getAllCategories();
        for (const Categorie& categorie : listeCategories) {
            baseModels.append(BaseModel(categorie.id,categorie.nom));
        }
        DatabaseManager::closeConnection();
     }
}
void LivreWindow::getListEditeur(){
     if(DatabaseManager::openConnection()){
        listeEditeurs = Editeur::getAllEditeurs();
        for (const Editeur& editeur : listeEditeurs) {
            baseModels.append(BaseModel(editeur.id,editeur.nom));
        }

        DatabaseManager::closeConnection();
     }
}
void LivreWindow::getListLangue(){
     if(DatabaseManager::openConnection()){
        listeLangues = Langue::getAllLangues();
        for (const Langue& langue : listeLangues) {
            baseModels.append(BaseModel(langue.id,langue.nom));
        }
        DatabaseManager::closeConnection();
     }
}


void LivreWindow::on_addButton_clicked()
{
     QString nouveau = ui->newEdit->text();
     if(!nouveau.isEmpty()){
        bool exist = nomExist(nouveau,baseModels);
        if(!exist){
            addNew(nouveau);
        }
    }
}

void LivreWindow::addNew(QString nouveau){
    if (DatabaseManager::openConnection()) {
        if (type == "categorie") {
            Categorie::addCategorie(Categorie(nouveau));
        } else if (type == "editeur") {
            Editeur::addEditeur(Editeur(nouveau));
        } else if (type == "langue") {
            Langue::addLangue(Langue(nouveau));
        }
        DatabaseManager::closeConnection();
        getList();
    }
}

void LivreWindow::updateData(){
    if (DatabaseManager::openConnection()) {
        if (type == "categorie") {
            Categorie::updateCategorie(Categorie(baseModel.id,baseModel.nom));
        } else if (type == "editeur") {
            Editeur::updateEditeur(Editeur(baseModel.id,baseModel.nom));
        } else if (type == "langue") {
            Langue::updateLangue(Langue(baseModel.id,baseModel.nom));
        }
        DatabaseManager::closeConnection();
        getList();
    }
}

void LivreWindow::deleteData(){
    if (DatabaseManager::openConnection()) {
        if (type == "categorie") {
            Categorie::deleteCategorie(baseModel.id);
        } else if (type == "editeur") {
            Editeur::deleteEditeur(baseModel.id);
        } else if (type == "langue") {
            Langue::deleteLangue(baseModel.id);
        }
        DatabaseManager::closeConnection();
        getList();
    }
}

void LivreWindow::on_editButton_clicked()
{
    int row;
    for(int i =0 ; i < baseModels.size();i++){
        if(baseModels[i].id == baseModel.id){
            row = i;
            break;
        }
    }
    QString nom = ui->tableWidget->item(row, 0)->data(Qt::DisplayRole).toString();
    if(baseModel.nom != nom){
        bool exist = nomExist(nom,baseModels);
        if(!exist){
            QMessageBox::StandardButton reply;
            reply = QMessageBox::question(this, "Confirmation", "Voulez-vous vraiment modifier " + baseModel.nom +"? ", QMessageBox::Yes|QMessageBox::No);
            if (reply == QMessageBox::Yes) {
                updateData();
            }
        }else{
            QMessageBox::information(nullptr, "Information", "\""+nom+"\" est déjà enregistré");
        }
    }
}


void LivreWindow::on_deleteButton_clicked()
{
    if(baseModel.id != 0){
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Confirmation", "Voulez-vous vraiment supprimer " + baseModel.nom +"? ", QMessageBox::Yes|QMessageBox::No);

        if (reply == QMessageBox::Yes) {
            deleteData();
        }
    }

}


void LivreWindow::on_tableWidget_cellClicked(int row)
{
    baseModel = baseModels.at(row);
}

bool  LivreWindow::nomExist(QString nom, QList<BaseModel> baseModels){
    bool exist = false;
    for (const BaseModel& baseModel : baseModels) {
        if (baseModel.nom == nom) {
            exist = true;
        }
    }
    return exist;
}
