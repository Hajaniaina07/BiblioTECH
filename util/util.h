#ifndef UTIL_H
#define UTIL_H

#include <QComboBox>


class Util
{
public:
    Util();
    static int getSelectedItem(QComboBox* comboBox);
};

#endif // UTIL_H
