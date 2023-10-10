#include "util/boolResult.h"

BoolResult::BoolResult()
{

}


BoolResult::BoolResult(bool res, const QString& message):
    validate(res),message(message)
{

}
