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
    QColor start = Qt::red;
    QColor end = Qt::green;

    qreal noteNormalisee = (note - 0) / (10 - 0);

    QColor couleurInterpolee = start.rgb() * (1 - noteNormalisee) + end.rgb() * noteNormalisee;

    return QBrush(couleurInterpolee);
}
