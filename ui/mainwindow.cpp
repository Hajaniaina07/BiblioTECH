#include "ui/mainwindow.h"
#include "ui_mainwindow.h"
#include "ui/livrewindow.h"
#include "ui/auteurwindow.h"
#include "ui/livredetail.h"
#include "ui/abonnementwindow.h"
#include "ui/newmembrewindow.h"
#include "ui/membreabonnementwindow.h"
#include "ui/newempruntwindow.h"
#include "model/utilisateur.h"
#include "model/utilisateur.h"
#include "manager/DatabaseManager.h"
#include "util/util.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    setFixedSize(950,550);
    ui->setupUi(this);
    ui->principal->setCurrentIndex(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_livre_btn_clicked()
{
    ui->principal->setCurrentIndex(2);
    getListLivre();
}


void MainWindow::on_membre_btn_clicked()
{
    ui->principal->setCurrentIndex(3);
    getListMembre();
}


void MainWindow::on_emprunt_btn_clicked()
{
    ui->principal->setCurrentIndex(4);
}


void MainWindow::on_lb_accueil_clicked()
{
    on_livre_btn_clicked();
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
        on_livre_btn_clicked();
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
    ui->livreTableWidget->setColumnWidth(2, 178);

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
            genreItem->setTextAlignment(Qt::AlignCenter | Qt::AlignVCenter);

            QTableWidgetItem *pageItem = new QTableWidgetItem(QString::number(livre.page));
            pageItem->setTextAlignment(Qt::AlignCenter | Qt::AlignVCenter);

            QTableWidgetItem *publicationItem = new QTableWidgetItem(livre.publication.toString("dd/MM/yyyy"));
            publicationItem->setTextAlignment(Qt::AlignCenter | Qt::AlignVCenter);

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

void MainWindow::getListMembre(){
    ui->membreTableWidget->setRowCount(0);
    ui->membreTableWidget->verticalHeader()->setVisible(false);

    ui->membreTableWidget->setColumnWidth(0, 189);
    ui->membreTableWidget->setColumnWidth(1, 190);
    ui->membreTableWidget->setColumnWidth(4, 150);

    if (DatabaseManager::openConnection()) {
        listeMembres = AbonnementMembre::getMembres();
        int row = 0;
        for(const AbonnementMembre& am : listeMembres){
            ui->membreTableWidget->insertRow(row);
            ui->membreTableWidget->setItem(row, 0, new QTableWidgetItem(am.membre.nom));
            ui->membreTableWidget->setItem(row, 1, new QTableWidgetItem(am.membre.prenom));
            ui->membreTableWidget->setItem(row, 2, new QTableWidgetItem(am.membre.naissance.toString("dd/MM/yyyy")));
            ui->membreTableWidget->setItem(row, 3, new QTableWidgetItem(am.membre.contact));
            if(am.id != 0){
                ui->membreTableWidget->setItem(row, 4, new QTableWidgetItem(am.abonnement.nom));
                ui->membreTableWidget->setItem(row, 5, new QTableWidgetItem(am.debut.toString("dd/MM/yyyy")));
                QTableWidgetItem *finItem = new QTableWidgetItem(am.fin.toString("dd/MM/yyyy"));
                QDate currentDate = QDate::currentDate();
                if(am.fin < currentDate){
                    finItem->setForeground(QBrush(Qt::red));
                }else finItem->setForeground(QBrush(Qt::green));
                ui->membreTableWidget->setItem(row, 6, finItem);
            }else{
                ui->membreTableWidget->setItem(row, 4, new QTableWidgetItem("-"));
                ui->membreTableWidget->setItem(row, 5, new QTableWidgetItem("-"));
                ui->membreTableWidget->setItem(row, 6, new QTableWidgetItem("-"));
            }

            ui->membreTableWidget->item(row,2)->setTextAlignment(Qt::AlignCenter | Qt::AlignVCenter);
            ui->membreTableWidget->item(row,3)->setTextAlignment(Qt::AlignCenter | Qt::AlignVCenter);
            ui->membreTableWidget->item(row,4)->setTextAlignment(Qt::AlignCenter | Qt::AlignVCenter);
            ui->membreTableWidget->item(row,5)->setTextAlignment(Qt::AlignCenter | Qt::AlignVCenter);
            ui->membreTableWidget->item(row,6)->setTextAlignment(Qt::AlignCenter | Qt::AlignVCenter);

            row++;
        }
        DatabaseManager::closeConnection();
    }
}

void MainWindow::getListEmprunts(){
    ui->empruntTableWidget->setRowCount(0);
    ui->empruntTableWidget->verticalHeader()->setVisible(false);

    ui->empruntTableWidget->setColumnWidth(0, 170);
    ui->empruntTableWidget->setColumnWidth(1, 120);
    ui->empruntTableWidget->setColumnWidth(2, 230);

    if(DatabaseManager::openConnection()){
        listeEmprunts = Emprunt::getAllEmprunts();
        int row = 0;
        for(Emprunt& emprunt : listeEmprunts){
            ui->empruntTableWidget->insertRow(row);

            QTableWidgetItem *titleItem = new QTableWidgetItem(emprunt.livre.titre);
            QFont font = titleItem->font();
            font.setBold(true);
            titleItem->setFont(font);

            ui->empruntTableWidget->setItem(row, 0, titleItem);
            ui->empruntTableWidget->setItem(row, 1, new QTableWidgetItem(emprunt.livre.categorie.nom));
            ui->empruntTableWidget->setItem(row, 2, new QTableWidgetItem(QString("%1 %2").arg(emprunt.membre.nom).arg(emprunt.membre.prenom)));
            ui->empruntTableWidget->setItem(row, 3, new QTableWidgetItem(emprunt.dateEmprunt.toString("dd/MM/yyyy")));
            ui->empruntTableWidget->setItem(row, 4, new QTableWidgetItem(emprunt.dateMax.toString("dd/MM/yyyy")));
            if(!emprunt.dateRendue.isValid()){
                QDate now = QDate::currentDate();
                if(emprunt.dateMax < now){
                    ui->empruntTableWidget->item(row,4)->setForeground(QBrush(Qt::red));
                }
                ui->empruntTableWidget->setItem(row, 6, new QTableWidgetItem("-"));
            }else{
                ui->empruntTableWidget->setItem(row, 5, new QTableWidgetItem(emprunt.dateRendue.toString("dd/MM/yyyy")));
                if(emprunt.dateRendue <= emprunt.dateMax){
                    ui->empruntTableWidget->item(row,5)->setForeground(QBrush(Qt::green));
                }else ui->empruntTableWidget->item(row,5)->setForeground(QBrush(Qt::red));
                ui->empruntTableWidget->setItem(row, 6, new QTableWidgetItem(QString("%1").arg(emprunt.note)));
                QBrush brush = Util::couleurPourNote(emprunt.note);
                ui->empruntTableWidget->item(row,6)->setForeground(brush);
            }

            row ++;
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


void MainWindow::on_lb_accueil_2_clicked()
{
    on_livre_btn_clicked();
}


void MainWindow::on_membreButton_clicked()
{
    ui->principal->setCurrentIndex(3);
    getListMembre();
}


void MainWindow::on_abonnementButton_clicked()
{
    AbonnementWindow *w  = new AbonnementWindow(this);
    w->setWindowTitle("Abonnement");
        w->setAttribute(Qt::WA_DeleteOnClose);
    w->show();
}


void MainWindow::on_newMembreButton_clicked()
{
    NewMembreWindow *w  = new NewMembreWindow(this);
    w->setWindowTitle("Nouveau membre");
    w->setAttribute(Qt::WA_DeleteOnClose);
    w->show();
}


void MainWindow::on_membreTableWidget_cellDoubleClicked(int row, int column)
{
    AbonnementMembre am = listeMembres[row];
    MembreAbonnementWindow *w  = new MembreAbonnementWindow(am, this);
    w->setWindowTitle("Fiche du membre");
    w->setAttribute(Qt::WA_DeleteOnClose);
    w->show();
}


void MainWindow::on_lb_accueil_3_clicked()
{
    on_livre_btn_clicked();
}


void MainWindow::on_newEmpruntButton_clicked()
{
    Membre membre = Membre();
    Livre livre = Livre();
    NewEmpruntWindow *w  = new NewEmpruntWindow(0,livre, membre,this);
    w->setWindowTitle("Emprunt");
    w->setAttribute(Qt::WA_DeleteOnClose);
    w->show();
}


void MainWindow::on_empruntButton_clicked()
{
    ui->principal->setCurrentIndex(4);
    getListEmprunts();
}

