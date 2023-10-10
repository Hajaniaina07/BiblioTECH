#include "util/boolResult.h"

BoolResult::BoolResult()
{

}


BoolResult::BoolResult(bool res, const QString& message):
    result(res),message(message)
{

}
