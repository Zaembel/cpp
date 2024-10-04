#include "PremiumRoom.h"

PremiumRoom::PremiumRoom(int number, HOTEL_ROOM_TYPES type, string title, int beds, double price) {
	this->number = number;
	this->type = type;
	this->title = title;
	this->beds = beds;
	this->price = price;
	incrementId();
}