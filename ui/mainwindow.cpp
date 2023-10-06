#include "ui/mainwindow.h"
#include "ui_mainwindow.h"
#include "ui/livrewindow.h"
#include "ui/auteurwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    setFixedSize(950,550);
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_livre_btn_clicked()
{
    ui->principal->setCurrentIndex(1);
}


void MainWindow::on_membre_btn_clicked()
{
    ui->principal->setCurrentIndex(2);
}


void MainWindow::on_emprunt_btn_clicked()
{
    ui->principal->setCurrentIndex(3);
}


void MainWindow::on_lb_accueil_clicked()
{
    ui->principal->setCurrentIndex(0);
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

