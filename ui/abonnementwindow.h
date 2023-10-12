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
    bool validate();

private slots:
    void on_addNewButton_clicked();

    void on_abonnementTableWidget_cellDoubleClicked(int row);

    void update();

    void on_cancelButton_clicked();

    void on_editButton_clicked();

    void on_deleteButton_clicked();

private:
    Ui::AbonnementWindow *ui;
    QList<Abonnement> listeAbonnements;
    Abonnement abonnement;

protected:
    void closeEvent(QCloseEvent *event) override;

signals:
    void closeWindow();
};

#endif // ABONNEMENTWINDOW_H
