#ifndef LIVREDETAIL_H
#define LIVREDETAIL_H

#include <QMainWindow>

namespace Ui {
class LivreDetail;
}

class LivreDetail : public QMainWindow
{
    Q_OBJECT

public:
    explicit LivreDetail(const int& additionalParameter,QWidget *parent = nullptr);
    ~LivreDetail();

private:
    Ui::LivreDetail *ui;
    int page;
};

#endif // LIVREDETAIL_H
