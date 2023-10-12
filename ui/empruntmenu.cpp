#include "empruntmenu.h"
#include "ui_empruntmenu.h"
#include "manager/DatabaseManager.h"
#include "newempruntwindow.h"

#include<QMessageBox>

EmpruntMenu::EmpruntMenu(Emprunt emprunt, QWidget *parent) :
    QMainWindow(parent),ui(new Ui::EmpruntMenu),emprunt(emprunt)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentWidget(0);
    setMenu();
    ui->noteSpinBox->setMaximum(10);
    ui->dateRemiseEdit->setDate(QDate::currentDate());
}

EmpruntMenu::~EmpruntMenu()
{
    delete ui;
}

void EmpruntMenu::on_rendreButton_clicked()
{
    if(emprunt.dateRendue.isValid()){
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Confirmation", "Voulez-vous vraiment annuler la remise?", QMessageBox::Yes|QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            emprunt.dateRendue = QDate();
            emprunt.note = 0;
            if(DatabaseManager::openConnection()){
                Emprunt::updateEmprunt(emprunt);
                DatabaseManager::closeConnection();
                QMessageBox::information(this, "Succès", "Remise annulé");
                this->close();
            }
        }
    }else{
        ui->stackedWidget->setCurrentIndex(1);
    }
}


void EmpruntMenu::on_editDateButton_clicked()
{
    NewEmpruntWindow *w  = new NewEmpruntWindow(emprunt,this);
    w->setWindowTitle("Emprunt");
    w->setAttribute(Qt::WA_DeleteOnClose);
    w->show();
}


void EmpruntMenu::on_deleteButton_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirmation", "Voulez-vous vraiment supprimer cet emprunt?", QMessageBox::Yes|QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        if(DatabaseManager::openConnection()){
            Emprunt::deleteEmprunt(emprunt.id);
            DatabaseManager::closeConnection();
            QMessageBox::information(this, "Succès", "Emprunt supprimé.");
            this->close();
        }
    }
}


void EmpruntMenu::on_validateRendreButton_clicked()
{
    double note = ui->noteSpinBox->value();
    emprunt.dateRendue = ui->dateRemiseEdit->date();
    emprunt.note = note;
    qDebug() << emprunt.note << emprunt.dateRendue;
    if(DatabaseManager::openConnection()){
        Emprunt::updateEmprunt(emprunt);
        DatabaseManager::closeConnection();
        QMessageBox::information(this, "Succès", "Modification enregistré !");
        this->close();
    }
}


void EmpruntMenu::on_cancelButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    setMenu();
}

void EmpruntMenu::setMenu()
{
    if(emprunt.dateRendue.isValid()){
        ui->rendreButton->setText("Annuler la remise");
        ui->editDateButton->setEnabled(false);
    }else {
        ui->rendreButton->setText("Rendre");
        ui->editDateButton->setEnabled(true);
    }
}

void EmpruntMenu::closeEvent(QCloseEvent *event){
    emit closeWindow();
    QMainWindow::closeEvent(event);
}

