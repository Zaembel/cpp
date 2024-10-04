#pragma once
#include "HotelManagement.h"
#include "Bill.h"
#include "HotelRooms.h"
#include <fstream>
#include "GuestAdapter.h"
#include "RoomAdapter.h"
#include "BillAdapter.h"
#include <string>

class HotelManagementAdapter {
public:
	static HotelManagement* getHotelManagement();
};

