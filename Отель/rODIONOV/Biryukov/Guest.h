#pragma once
#include <iostream>
#include <fstream>
using namespace std;

class Guest {
private:
	static int lastId;

	int id;
	string name;
	short age;
	string phone;
	int roomNumber = -1;

	void incrementId();
public:
	Guest(string, short, string);

	int getId();
	string getName();
	short getAge();
	string getPhone();
	int getRoomNumber();

	void setAge(short);
	void setPhone(string);
	void setName(string);
	void setRoomNumber(int);

	void showInfo();
	void save(ofstream&);
};

