#ifndef BOOLRESULT_H
#define BOOLRESULT_H
#include <QString>

class BoolResult {
public:
    bool validate = false;
    QString message;

    BoolResult();
    BoolResult(bool res, const QString& message);
};

#endif // BOOLRESULT_H
