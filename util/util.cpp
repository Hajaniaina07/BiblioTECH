#include "util.h"

Util::Util()
{

}

int Util::getSelectedItem(QComboBox* comboBox)
{
    int indexSelected = comboBox->currentIndex();
    if (indexSelected > 0)
    {
        return indexSelected - 1;
    }
    return -1;
}

QBrush Util::couleurPourNote(float note) {
    QColor couleur;
    if (note >= 0 && note < 3) {
        couleur = Qt::red;
    } else if (note >= 3 && note < 5) {
        couleur = Qt::yellow;
    } else if (note >= 5 && note <= 10) {
        couleur = Qt::green;
    } else {
        couleur = Qt::gray;
    }
    return QBrush(couleur);
}

/*QBrush Util::couleurPourNote(float note) {
    QColor start = Qt::red;
    QColor end = Qt::green;

    qreal noteNormalisee = (note - 0) / (10 - 0);

    QColor couleurInterpolee = start.rgb() * (1 - noteNormalisee) + end.rgb() * noteNormalisee;

    return QBrush(couleurInterpolee);
}*/
