#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QSqlError>
#include <QDebug>
#include "ui/livredetail.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

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

private:
    Ui::MainWindow *ui;
    QSqlDatabase db;
    QSqlTableModel *model;
};
#endif // MAINWINDOW_H
