#ifndef NEWMEMBREWINDOW_H
#define NEWMEMBREWINDOW_H

#include <QMainWindow>
#include "model/abonnement.h"
#include "model/Membre.h"

namespace Ui {
class NewMembreWindow;
}

class NewMembreWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit NewMembreWindow(QWidget *parent = nullptr);
    ~NewMembreWindow();
    void getList();

private slots:
    void on_pushButtonMembre_clicked();

private:
    Ui::NewMembreWindow *ui;
    QList<Abonnement> listeAbonnements;
    Membre membre;

protected:
    void closeEvent(QCloseEvent *event) override;

signals:
    void closeWindow();

};

#endif // NEWMEMBREWINDOW_H
