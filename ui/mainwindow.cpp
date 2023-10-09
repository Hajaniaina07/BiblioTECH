#include "ui/mainwindow.h"
#include "ui_mainwindow.h"
#include "ui/livrewindow.h"
#include "ui/auteurwindow.h"
#include "model/utilisateur.h"
#include "manager/DatabaseManager.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    setFixedSize(950,550);
    ui->setupUi(this);
    getListLivre();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_livre_btn_clicked()
{
    ui->principal->setCurrentIndex(2);
}


void MainWindow::on_membre_btn_clicked()
{
    ui->principal->setCurrentIndex(3);
}


void MainWindow::on_emprunt_btn_clicked()
{
    ui->principal->setCurrentIndex(4);
}


void MainWindow::on_lb_accueil_clicked()
{
//    ui->principal->setCurrentIndex(1);
}


void MainWindow::on_lb_categorie_clicked()
{
    LivreWindow *w = new LivreWindow("categorie",this);
    w->setWindowTitle("Catégories");
    w->setAttribute(Qt::WA_DeleteOnClose);
    w->show();
}


void MainWindow::on_lb_auteur_clicked()
{
    AuteurWindow *w = new AuteurWindow(this);
    w->setAttribute(Qt::WA_DeleteOnClose);
    w->show();
}


void MainWindow::on_lb_editeur_clicked()
{
    LivreWindow *w = new LivreWindow("editeur",this);
    w->setWindowTitle("Editeurs");
    w->setAttribute(Qt::WA_DeleteOnClose);
    w->show();
}


void MainWindow::on_lb_langue_clicked()
{
    LivreWindow *w = new LivreWindow("langue",this);
    w->setWindowTitle("Langues");
    w->setAttribute(Qt::WA_DeleteOnClose);
    w->show();
}


void MainWindow::on_pushButton_clicked()
{
    QString login = ui->loginEdit->text();
    QString mdp = ui->mdpEdit->text();
    Utilisateur utilisateur = Utilisateur(login,mdp);
    if(utilisateur.isConnected()){
        ui->principal->setCurrentIndex(2);
    }else{
        QMessageBox::critical(this, "Erreur de connection", "Login ou mot de passe incorrect");
    }
}



void MainWindow::on_lb_ajouter_clicked()
{
    Livre livre = Livre();
    LivreDetail *w  = new LivreDetail(0,livre,this);
    w->setWindowTitle("Nouveau livre");
    w->setAttribute(Qt::WA_DeleteOnClose);
    w->show();
}

void  MainWindow::getListLivre()
{
    ui->livreTableWidget->setRowCount(0);

    ui->livreTableWidget->verticalHeader()->setVisible(false);
    ui->livreTableWidget->setColumnWidth(0, 250);
    ui->livreTableWidget->setColumnWidth(2, 150);

    if (DatabaseManager::openConnection()) {
        listeLivres = Livre::getAllLivres();
        int row = 0;
        for (Livre livre : listeLivres) {
            ui->livreTableWidget->insertRow(row);
            QTableWidgetItem *titleItem = new QTableWidgetItem(livre.titre);
            QFont font = titleItem->font();
            font.setBold(true);
            titleItem->setFont(font);

            QTableWidgetItem *genreItem = new QTableWidgetItem(livre.categorie.nom);
            genreItem->setTextAlignment(Qt::AlignCenter);

            QTableWidgetItem *pageItem = new QTableWidgetItem(QString::number(livre.page));
            pageItem->setTextAlignment(Qt::AlignCenter);

            QTableWidgetItem *publicationItem = new QTableWidgetItem(livre.publication.toString("dd/MM/yyyy"));
            publicationItem->setTextAlignment(Qt::AlignCenter);

            ui->livreTableWidget->setItem(row, 0, titleItem);
            ui->livreTableWidget->setItem(row, 1, genreItem);
            ui->livreTableWidget->setItem(row, 2, new QTableWidgetItem(livre.auteur.prenom + " " +livre.auteur.nom));
            ui->livreTableWidget->setItem(row, 3, pageItem);
            ui->livreTableWidget->setItem(row, 6, publicationItem);

            row++;
        }
        DatabaseManager::closeConnection();
    }
}

void MainWindow::on_livreTableWidget_cellDoubleClicked(int row, int column)
{
    Livre livre = listeLivres.at(row);
    LivreDetail *w  = new LivreDetail(1,livre,this);
    w->setWindowTitle("Détail du livre");
    w->setAttribute(Qt::WA_DeleteOnClose);
    w->show();
}

