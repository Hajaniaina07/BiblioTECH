#include "ui/livrewindow.h"
#include "ui_livrewindow.h"
#include "manager/DatabaseManager.h"

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

void LivreWindow::on_pushButton_clicked()
{
    QString nouveau = ui->newEdit->text();
    qDebug() << "Le texte du lineEdit est : " << nouveau;
}
void LivreWindow::getList()
{
    if (type == "categorie") {
        getListCategorie();
    } else if (type == "editeur") {
        getListEditeur();
    } else if (type == "langue") {
        getListLangue();
    }
}

void LivreWindow::getListCategorie(){
     ui->tableWidget->setRowCount(0);
     if(DatabaseManager::openConnection()){
        listeCategories = Categorie::getAllCategories();
        int row = 0;
        for (const Categorie& categorie : listeCategories) {
            ui->tableWidget->insertRow(row);
            ui->tableWidget->setItem(row, 0, new QTableWidgetItem(categorie.nom));
            row++;
        }
        DatabaseManager::closeConnection();
     }
}
void LivreWindow::getListEditeur(){
     ui->tableWidget->setRowCount(0);
     if(DatabaseManager::openConnection()){
        listeEditeurs = Editeur::getAllEditeurs();
        int row = 0;
        for (const Editeur& editeur : listeEditeurs) {
            ui->tableWidget->insertRow(row);
            ui->tableWidget->setItem(row, 0, new QTableWidgetItem(editeur.nom));
            row++;
        }
        DatabaseManager::closeConnection();
     }
}
void LivreWindow::getListLangue(){
     ui->tableWidget->setRowCount(0);
     if(DatabaseManager::openConnection()){
        listeLangues = Langue::getAllLangues();
        int row = 0;
        for (const Langue& langue : listeLangues) {
            ui->tableWidget->insertRow(row);
            ui->tableWidget->setItem(row, 0, new QTableWidgetItem(langue.nom));
            row++;
        }
        DatabaseManager::closeConnection();
     }
}

