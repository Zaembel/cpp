#pragma once
#include "BaseRoom.h"
#include "Constants.h"

class PremiumRoom : public BaseRoom {
public:
	PremiumRoom(int, HOTEL_ROOM_TYPES, string, int, double);
};

