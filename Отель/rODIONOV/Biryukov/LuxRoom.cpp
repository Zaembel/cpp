#include "LuxRoom.h"

LuxRoom::LuxRoom(int number, HOTEL_ROOM_TYPES type, string title, int beds, double price) {
	this->number = number;
	this->type = type;
	this->title = title;
	this->beds = beds;
	this->price = price;
	incrementId();
}