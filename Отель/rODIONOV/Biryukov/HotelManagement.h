#pragma once
#include <iostream>
#include <vector>
#include "HotelRooms.h"
#include "Guest.h"
#include "Bill.h"
#include "Constants.h"
#include "Errors.h"
#include <chrono>
#include <sstream>
#include <iomanip>
#include <fstream>
using namespace std;

class HotelManagement {
private:
	vector<Guest*> guests;
	vector<BaseRoom*> rooms;
	vector<Bill*> bills;

	system_clock::time_point parseTimePoint(const string&);
	string formatTimePoint(const system_clock::time_point&);
public:
	HotelManagement();

	void addGuest(string, short, string);
	void addGuest(Guest*);
	BaseRoom* addRoom(BaseRoom*);
	BaseRoom* addRoom(int, HOTEL_ROOM_TYPES, string, int, double);

	vector<BaseRoom*> findFreeRooms(int, HOTEL_ROOM_TYPES);

	void checkIn(int, int, HOTEL_ROOM_TYPES, system_clock::time_point*);
	void addGuest(int, int);
	double checkOut(int);
	void showRooms();
	void showGuests();
	void showBills();
	void save();

	void addBill(Bill*);
	void syncBills();

	~HotelManagement();
};