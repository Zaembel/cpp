#pragma once
#include "Guest.h"
#include "Constants.h"
#include <iostream>
#include <vector>
#include "Errors.h"
#include <fstream>
using namespace std;

class BaseRoom
{
protected:
	static int lastId;

	int id;
	int number;
	HOTEL_ROOM_TYPES type;
	string title;
	int beds;
	bool status = true;
	double price;
	vector<Guest*> guests;

	bool jacuzzi = false;
	bool minibar = false;
	bool TV = false;
	bool wifi = false;

	void incrementId();
public:
	int getId();
	int getNumber();
	HOTEL_ROOM_TYPES getType();
	string getTitle();
	int getBeds();
	bool getStatus();
	double getPrice();
	vector<Guest*> getGuests();
	Guest* getOwner();

	void setNumber(int);
	void setTitle(string);
	void setStatus(bool);
	void setPrice(double);

	void addGuest(Guest*);
	void showInfo();

	void checkOut();

	BaseRoom* provideJacuzzi(bool);
	BaseRoom* provideMinibar(bool);
	BaseRoom* provideTV(bool);
	BaseRoom* provideWifi(bool);

	void addGuest(Guest* guest, BaseRoom* room);
	void save(ofstream& out);
};

