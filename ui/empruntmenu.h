#ifndef EMPRUNTMENU_H
#define EMPRUNTMENU_H

#include "model/emprunt.h"

#include <QMainWindow>

namespace Ui {
class EmpruntMenu;
}

class EmpruntMenu : public QMainWindow
{
    Q_OBJECT

public:
    explicit EmpruntMenu(Emprunt emprunt,QWidget *parent = nullptr);
    ~EmpruntMenu();
    void setMenu();

private slots:
    void on_rendreButton_clicked();

    void on_editDateButton_clicked();

    void on_deleteButton_clicked();

    void on_validateRendreButton_clicked();

    void on_cancelButton_clicked();

private:
    Ui::EmpruntMenu *ui;
    Emprunt emprunt;

protected:
    void closeEvent(QCloseEvent *event) override;

signals:
    void closeWindow();
};

#endif // EMPRUNTMENU_H
