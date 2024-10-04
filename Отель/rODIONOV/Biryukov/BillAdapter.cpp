#include "BillAdapter.h"

Bill* BillAdapter::getBill(Str data) {
    Str* params = data.split(';');

    return new Bill(stoi(params[0]), stoi(params[1]), stod(params[2]), params[3], params[4]);
}
