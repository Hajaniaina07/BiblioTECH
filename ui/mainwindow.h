#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QSqlError>
#include <QDebug>
#include "model/livre.h"
#include "model/abonnementmembre.h"
#include "model/emprunt.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void getListLivre();
    void getListMembre();
    void getListEmprunts();

private slots:
    void on_livre_btn_clicked();

    void on_membre_btn_clicked();

    void on_emprunt_btn_clicked();

    void on_lb_accueil_clicked();

    void on_lb_categorie_clicked();

    void on_lb_auteur_clicked();

    void on_lb_editeur_clicked();

    void on_lb_langue_clicked();

    void on_pushButton_clicked();

    void on_lb_ajouter_clicked();

    void on_livreTableWidget_cellDoubleClicked(int row);

    void on_lb_accueil_2_clicked();

    void on_membreButton_clicked();

    void on_abonnementButton_clicked();

    void on_newMembreButton_clicked();

    void on_membreTableWidget_cellDoubleClicked(int row);

    void on_lb_accueil_3_clicked();

    void on_newEmpruntButton_clicked();

    void on_empruntButton_clicked();

    void on_empruntTableWidget_cellDoubleClicked(int row);

private:
    Ui::MainWindow *ui;
    QSqlDatabase db;
    QSqlTableModel *model;
    QList<Livre> listeLivres;
    QList<AbonnementMembre> listeMembres;
    QList<Emprunt> listeEmprunts;

};
#endif // MAINWINDOW_H
