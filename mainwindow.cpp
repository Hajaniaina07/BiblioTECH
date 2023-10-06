#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
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

