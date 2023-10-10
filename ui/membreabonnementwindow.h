#ifndef MEMBREABONNEMENTWINDOW_H
#define MEMBREABONNEMENTWINDOW_H

#include "model/abonnementmembre.h"

#include <QMainWindow>

namespace Ui {
class MembreAbonnementWindow;
}

class MembreAbonnementWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MembreAbonnementWindow(AbonnementMembre& am, QWidget *parent = nullptr);
    ~MembreAbonnementWindow();
    void getMembre();
    void getListAbonnements();
    void setListAbonnement();

private slots:
    void on_newAbonnementButton_clicked();

    void on_editButton_clicked();

    void on_confirmEditButton_clicked();

    void on_cancelEditButton_clicked();

    void on_amTableWidget_cellDoubleClicked(int row, int column);

private:
    Ui::MembreAbonnementWindow *ui;
    AbonnementMembre am;
    Membre membre;
    QList<AbonnementMembre> ams;
    QList<Abonnement> listeAbonnements;
};

#endif // MEMBREABONNEMENTWINDOW_H
