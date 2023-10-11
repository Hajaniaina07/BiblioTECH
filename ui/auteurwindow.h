#ifndef AUTEURWINDOW_H
#define AUTEURWINDOW_H

#include <QMainWindow>
#include <QDate>
#include "model/Auteur.h"

QT_BEGIN_NAMESPACE
namespace Ui { class AuteurWindow; }
QT_END_NAMESPACE

class AuteurWindow : public QMainWindow
{
    Q_OBJECT

public:
    AuteurWindow(QWidget *parent = nullptr);
    ~AuteurWindow();

private slots:
    void on_addButton_clicked();
    void addAuteur(const Auteur& auteur);
    void removeAuteur(const Auteur& auteur);
    void getList();

    void on_tableWidget_cellClicked(int row);

    void on_editButton_clicked();

    void on_deleteButton_clicked();

private:
    Ui::AuteurWindow *ui;
    QList<Auteur> listeAuteurs;
    Auteur auteur;
    void setupTable();

protected:
    void closeEvent(QCloseEvent *event) override;

signals:
    void closeWindow();
};

#endif
