#ifndef LIVREWINDOW_H
#define LIVREWINDOW_H

#include <QMainWindow>
#include <QDebug>

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

private:
    Ui::livrewindow *ui;
};

#endif // LIVREWINDOW_H
