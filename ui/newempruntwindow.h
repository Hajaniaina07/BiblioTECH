#ifndef NEWEMPRUNTWINDOW_H
#define NEWEMPRUNTWINDOW_H

#include "model/emprunt.h"
#include <QMainWindow>

namespace Ui {
class NewEmpruntWindow;
}

class NewEmpruntWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit NewEmpruntWindow(Emprunt& emprunt,QWidget *parent = nullptr);
    ~NewEmpruntWindow();
    void getList();
    void setSelectedItems();

private slots:
    void on_validateEmpruntButton_clicked();

private:
    Ui::NewEmpruntWindow *ui;
    Emprunt emprunt;
    QList<Livre> listeLivres;
    QList<Membre> listeMembres;

protected:
    void closeEvent(QCloseEvent *event) override;

signals:
    void closeWindow();
};

#endif // NEWEMPRUNTWINDOW_H
