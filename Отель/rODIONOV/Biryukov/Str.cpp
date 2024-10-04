#include "Str.h"

Str* Str::split(const char Ch) {
    int amt = 1;

    for (int i = 0; i < this->size(); i++) {
        if (this[0][i] == Ch)
            amt++;
    }

    if (amt == 1) {
        return this;
    }

    Str* strings = new Str[amt];

    for (int i = 0, k = 0; i < this->size(); i++) {
        if (this[0][i] == Ch) {
            k++;
            continue;
        }
        strings[k] += this[0][i];
    }

    return strings;
}
