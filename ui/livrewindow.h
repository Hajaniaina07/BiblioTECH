#ifndef LIVREWINDOW_H
#define LIVREWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QDate>
#include "model/Categorie.h"
#include "model/Editeur.h"
#include "model/Langue.h"

namespace Ui {
class livrewindow;
}

class LivreWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit LivreWindow(const QString& additionalParameter, QWidget *parent = nullptr);
    ~LivreWindow();

private slots:
    void on_pushButton_clicked();
    void getList();
    void getListCategorie();
    void getListEditeur();
    void getListLangue();

private:
    Ui::livrewindow *ui;
    QString type;
    QList<Categorie> listeCategories;
    QList<Editeur> listeEditeurs;
    QList<Langue> listeLangues;
};

#endif // LIVREWINDOW_H
