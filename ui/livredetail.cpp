#include "livredetail.h"
#include "ui_livredetail.h"

LivreDetail::LivreDetail(const int& page, QWidget *parent) :
    QMainWindow(parent), ui(new Ui::LivreDetail), page(page)
{
    setFixedSize(640,480);
    ui->setupUi(this);
}

LivreDetail::~LivreDetail()
{
    delete ui;
}
