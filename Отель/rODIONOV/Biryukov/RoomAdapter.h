#pragma once
#include "HotelRooms.h"
#include "Str.h"
#include "Constants.h"

class RoomAdapter {
public:
	static BaseRoom* getRoom(Str);
};

