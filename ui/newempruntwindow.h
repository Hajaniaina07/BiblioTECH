#ifndef NEWEMPRUNTWINDOW_H
#define NEWEMPRUNTWINDOW_H

#include "model/Livre.h"
#include "model/membre.h"
#include <QMainWindow>

namespace Ui {
class NewEmpruntWindow;
}

class NewEmpruntWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit NewEmpruntWindow(const int& page,Livre& livre,Membre& membre,QWidget *parent = nullptr);
    ~NewEmpruntWindow();
    void getList();
    void setSelectedItems();

private slots:
    void on_validateEmpruntButton_clicked();

private:
    Ui::NewEmpruntWindow *ui;
    Livre livre;
    Membre membre;
    QList<Livre> listeLivres;
    QList<Membre> listeMembres;
};

#endif // NEWEMPRUNTWINDOW_H
