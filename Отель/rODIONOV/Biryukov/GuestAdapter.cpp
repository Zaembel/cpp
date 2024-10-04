#include "GuestAdapter.h"

Guest* GuestAdapter::getGuest(Str data) {
    Str* params = data.split(';');

    return new Guest(params[0], stoi(params[1]), params[2]);
}
