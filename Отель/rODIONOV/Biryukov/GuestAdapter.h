#pragma once
#include "Guest.h"
#include "Str.h"
class GuestAdapter {
public:
	static Guest* getGuest(Str data);
};

