#ifndef LIVREWINDOW_H
#define LIVREWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QDate>
#include "model/Categorie.h"
#include "model/Editeur.h"
#include "model/Langue.h"
#include "model/baseModel.h"

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
    void getList();
    void getListCategorie();
    void getListEditeur();
    void getListLangue();
    void addNew(QString nouveau);
    void updateData();
    void deleteData();
    bool nomExist(QString nom, QList<BaseModel> baseModels);

    void on_addButton_clicked();

    void on_editButton_clicked();

    void on_deleteButton_clicked();

    void on_tableWidget_cellClicked(int row);

private:
    Ui::livrewindow *ui;
    QString type;
    QList<Categorie> listeCategories;
    QList<Editeur> listeEditeurs;
    QList<Langue> listeLangues;
    QList<BaseModel> baseModels;
    BaseModel baseModel;
    int selectedRow = -1;
};

#endif // LIVREWINDOW_H
