#pragma once
#include <iostream>
#include <ctime>
#include <chrono>
#include "Errors.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <format>
using namespace std;
using namespace std::chrono;

class Bill {
private:
	static int lastId;

	int id;
	int guestId;
	int roomId;
	double roomPrice;
	double amount;

	string formattedCheckInDate;
	string formattedCheckOutDate;

	void incrementId();
	void countAmount();
	system_clock::time_point parseTimePoint(const string&);
	string formatTimePoint(const system_clock::time_point&);
public:
	Bill(int, int, double, system_clock::time_point, system_clock::time_point);
	Bill(int, int, double, string, string);

	int getGuestId();
	int getRoomId();
	system_clock::time_point getCheckInDate();
	system_clock::time_point getCheckOutDate();
	double getAmount();

	void showInfo();
	void save(ofstream&);
};

