#include "ui/livrewindow.h"
#include "ui_livrewindow.h"


LivreWindow::LivreWindow(const QString& additionalParameter, QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::livrewindow)
{
    setFixedSize(250,300);
    ui->setupUi(this);
}

LivreWindow::~LivreWindow()
{
    delete ui;
}

void LivreWindow::on_pushButton_clicked()
{
    QString nouveau = ui->newEdit->text();
    qDebug() << "Le texte du lineEdit est : " << nouveau;
}

