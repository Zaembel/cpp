#include "Bill.h"

int Bill::lastId = -1;

void Bill::incrementId() {
	lastId++;
	this->id = lastId;
}

system_clock::time_point Bill::parseTimePoint(const string& timeStr) {
	istringstream iss(timeStr);
	tm t = {};
	iss >> get_time(&t, "%Y-%m-%d %H:%M:%S");
	time_t time = mktime(&t);
	return system_clock::from_time_t(time);
}

string Bill::formatTimePoint(const system_clock::time_point& tp) {
	time_t time = system_clock::to_time_t(tp);
	tm local_tm;
	localtime_s(&local_tm, &time);
	ostringstream oss;
	oss << put_time(&local_tm, "%Y-%m-%d %H:%M:%S");
	return oss.str();
}

Bill::Bill(int guestId, int roomId, double roomPrice, system_clock::time_point checkInDate, system_clock::time_point checkOutDate) {
	this->guestId = guestId;
	this->roomId = roomId;
	this->formattedCheckInDate = formatTimePoint(checkInDate);
	this->formattedCheckOutDate = formatTimePoint(checkOutDate);
	this->countAmount();
	incrementId();
}
Bill::Bill(int guestId, int roomId, double roomPrice, string checkInDate, string checkOutDate) {
	this->guestId = guestId;
	this->roomId = roomId;
	this->formattedCheckInDate = checkInDate;
	this->formattedCheckOutDate = checkOutDate;
	this->countAmount();
	incrementId();
}

void Bill::countAmount() {
	duration<double> diff = parseTimePoint(this->formattedCheckOutDate) - parseTimePoint(this->formattedCheckInDate);
	this->amount = this->roomPrice * ((diff.count() / 3600) / 24) + 1;
}

int Bill::getGuestId() {
	return this->guestId;
}

int Bill::getRoomId() {
	return this->roomId;
}

system_clock::time_point Bill::getCheckInDate() {
	return parseTimePoint(this->formattedCheckInDate);
}

system_clock::time_point Bill::getCheckOutDate() {
	if (this->formattedCheckOutDate.empty())
		throw value_not_set("checkOutDate");

	return parseTimePoint(this->formattedCheckOutDate);
}

double Bill::getAmount() {
	return this->amount;
}

void Bill::showInfo() {
	cout << "ID: " << this->id << endl \
		<< "Guest ID: " << this->guestId << endl \
		<< "Room ID: " << this->roomId << endl \
		<< "Amount: " << getAmount() << endl \
		<< "Check in Date: " << this->formattedCheckInDate << endl \
		<< "Check out Date: " << this->formattedCheckOutDate << endl;
}

void Bill::save(ofstream& out) {
	out << this->guestId << ';' \
		<< this->roomId << ';' \
		<< this->roomPrice << ';' \
		<< this->formattedCheckInDate << ';' \
		<< this->formattedCheckOutDate << endl;
}
