#include "BaseRoom.h"

int BaseRoom::lastId = -1;

void BaseRoom::incrementId() {
	lastId++;
	this->id = lastId;
}

int BaseRoom::getId() {
	return this->id;
}

int BaseRoom::getNumber() {
	return this->number;
}

HOTEL_ROOM_TYPES BaseRoom::getType() {
	return this->type;
}

string BaseRoom::getTitle() {
	return this->title;
}

int BaseRoom::getBeds() {
	return this->beds;
}

bool BaseRoom::getStatus() {
	return this->status;
}

double BaseRoom::getPrice() {
	return this->price;
}

vector<Guest*> BaseRoom::getGuests() {
	return this->guests;
}

Guest* BaseRoom::getOwner() {
	return this->guests.front();
}

void BaseRoom::setNumber(int number) {
	this->number = number;
}

void BaseRoom::setTitle(string title) {
	this->title = title;
}

void BaseRoom::setStatus(bool status) {
	this->status = status;
}

void BaseRoom::setPrice(double price) {
	this->price = price;
}

void BaseRoom::addGuest(Guest* guest) {
	if (this->beds == this->guests.size())
		throw full_room();

	this->guests.push_back(guest);
}

void BaseRoom::addGuest(Guest* guest, BaseRoom* room) {
	if (this->beds == this->guests.size())
		throw full_room();

	this->guests.push_back(guest);
}

void BaseRoom::save(ofstream& out) {
	out << this->number << ';' \
		<< this->type << ';' \
		<< this->title << ';' \
		<< this->beds << ';' \
		<< this->price << ';' \
		<< ((this->jacuzzi) ? "1" : "0") << ';' \
		<< ((this->minibar) ? "1" : "0") << ';' \
		<< ((this->TV) ? "1" : "0") << ';' \
		<< ((this->wifi) ? "1" : "0") << ';' \
		<< ((this->status) ? "1" : "0") << endl;
}

void BaseRoom::showInfo() {
	cout << "ID: " << this->id << endl \
		<< "Number: " << this->number << endl;
	switch (this->type) {
	case 0:
		cout << "Type: Standart" << endl;
		break;
	case 1:
		cout << "Type: VIP" << endl;
		break;
	case 2:
		cout << "Type: Premium" << endl;
		break;
	case 3:
		cout << "Type: Lux" << endl;
		break;
	default:
		throw logic_error("Unknown room type");
	}
	cout << "Title: " << this->title << endl \
		<< "Beds: " << this->beds << endl \
		<< "Jacuzzi: " << ((this->jacuzzi) ? "Yes" : "No") << endl \
		<< "Minibar: " << ((this->minibar) ? "Yes" : "No") << endl \
		<< "TV: " << ((this->TV) ? "Yes" : "No") << endl \
		<< "Wifi: " << ((this->wifi) ? "Yes" : "No") << endl \
		<< "Status: " << ((this->status) ? "Free" : "Occupied") << endl \
		<< "Price: " << this->price << endl \
		<< "Guests: " << endl;

	for (auto guest : this->guests) {
		cout << endl;
		guest->showInfo();
		cout << endl;
	}
	cout << endl;
}

void BaseRoom::checkOut() {
	this->status = true;
	this->guests.clear();
}

BaseRoom* BaseRoom::provideJacuzzi(bool is = true) {
	this->jacuzzi = is;
	return this;
}

BaseRoom* BaseRoom::provideMinibar(bool is = true) {
	this->minibar = is;
	return this;
}

BaseRoom* BaseRoom::provideTV(bool is = true) {
	this->TV = is;
	return this;
}

BaseRoom* BaseRoom::provideWifi(bool is = true) {
	this->wifi = is;
	return this;
}
