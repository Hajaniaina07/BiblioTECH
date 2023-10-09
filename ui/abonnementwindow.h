#ifndef ABONNEMENTWINDOW_H
#define ABONNEMENTWINDOW_H
#include "model/abonnement.h"

#include <QMainWindow>

namespace Ui {
class AbonnementWindow;
}

class AbonnementWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AbonnementWindow(QWidget *parent = nullptr);
    ~AbonnementWindow();

    void getList();

private slots:
    void on_addNewButton_clicked();

    void on_abonnementTableWidget_cellDoubleClicked(int row, int column);

    void update();

private:
    Ui::AbonnementWindow *ui;
    QList<Abonnement> listeAbonnements;
    Abonnement abonnement;
};

#endif // ABONNEMENTWINDOW_H
