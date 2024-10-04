#pragma once
#include <iostream>
using namespace std;

class full_room : public exception {
public:
	full_room() : exception("This room is full.") {}
};

class value_not_set : public exception {
public:
	value_not_set(string name) : exception(string("Value " + name + " was not set.").c_str()) {}
};

class no_such_room : public exception {
public:
	no_such_room() : exception("There is no rooms with these arguments in this hotel.") {}
};

class not_rented : public exception {
public:
	not_rented() : exception("This guest did not rent any rooms.") {}
};

class room_not_rented : public exception {
public:
	room_not_rented() : exception("This room is not rented.") {}
};

class number_exists : public exception {
public:
	number_exists() : exception("A room with this number already exists.") {}
};