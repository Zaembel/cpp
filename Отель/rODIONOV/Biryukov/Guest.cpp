#include "Guest.h"
int Guest::lastId = -1;

void Guest::incrementId() {
	lastId++;
	this->id = lastId;
}

Guest::Guest(string name, short age, string phone) {
	this->name = name;
	this->age = age;
	this->phone = phone;
	incrementId();
}

int Guest::getId() {
	return this->id;
}

string Guest::getName()
{
	return this->name;
}

short Guest::getAge() {
	return this->age;
}

string Guest::getPhone() {
	return this->phone;
}

int Guest::getRoomNumber() {
	return this->roomNumber;
}

void Guest::setAge(short age) {
	this->age = age;
}

void Guest::setPhone(string phone) {
	this->phone = phone;
}

void Guest::setName(string name) {
	this->name = name;
}

void Guest::setRoomNumber(int roomNumber) {
	this->roomNumber = roomNumber;
}

void Guest::showInfo() {
	cout << "ID: " << this->id << endl \
		<< "Name: " << this->name << endl \
		<< "Age: " << this->age << endl \
		<< "Phone: " << this->phone << endl \
		<< "RoomNumber: " << this->roomNumber << endl;
}

void Guest::save(ofstream& out) {
	out << this->name << ';' \
		<< this->age << ';' \
		<< this->phone << ';' \
		<< this->roomNumber << endl;
}
