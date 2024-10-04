#include "HotelManagement.h"

HotelManagement::HotelManagement() {}

void HotelManagement::addGuest(string name, short age, string phone) {
	this->guests.push_back(new Guest(name, age, phone));
}
void HotelManagement::addGuest(Guest* guest) {
	this->guests.push_back(guest);
}

BaseRoom* HotelManagement::addRoom(BaseRoom* room) {
	this->rooms.push_back(room);
	return this->rooms.back();
}

BaseRoom* HotelManagement::addRoom(int number, HOTEL_ROOM_TYPES type, string title, int beds, double price) {
	for (auto room : this->rooms) {
		if (room->getNumber() == number) {
			throw number_exists();
		}
	}
	switch (type) {
	case 0:
		this->rooms.push_back(new StandartRoom(number, type, title, beds, price));
		break;
	case 1:
		this->rooms.push_back(new VIPRoom(number, type, title, beds, price));
		break;
	case 2:
		this->rooms.push_back(new PremiumRoom(number, type, title, beds, price));
		break;
	case 3:
		this->rooms.push_back(new LuxRoom(number, type, title, beds, price));
		break;
	}
	return this->rooms.back();
}

vector<BaseRoom*> HotelManagement::findFreeRooms(int beds, HOTEL_ROOM_TYPES type) {
	vector<BaseRoom*> rooms;
	for (auto room : this->rooms) {
		if (room->getBeds() >= beds && room->getType() == type) {
			rooms.push_back(room);
		}
	}
	if(rooms.size() == 0)
		throw no_such_room();
	return rooms;
}

void HotelManagement::checkIn(int guestId, int beds, HOTEL_ROOM_TYPES type, system_clock::time_point* checkOutDate) {
	vector<BaseRoom*> rooms = findFreeRooms(beds, type);

	for (int i = 0; i < rooms.size(); i++) {
		cout << "Комната " << i + 1 << ": " << endl;
		rooms[i]->showInfo();
		cout << endl;
	}

	int choose = -1;
	while (choose < 1 || choose > rooms.size()) {
		cout << "Выберите номер, который вам нужен: ";
		cin >> choose;
		if (choose >= 1 && choose <= rooms.size())
			continue;
		cout << "Ты не можешь это выбрать." << endl;
	}

	this->bills.push_back(new Bill(guestId, rooms[choose - 1]->getId(), rooms[choose - 1]->getPrice(), system_clock::now(), *checkOutDate));

	for (auto guest : this->guests) {
		if (guest->getId() == guestId) {
			guest->setRoomNumber(rooms[choose - 1]->getNumber());
			rooms[choose - 1]->addGuest(guest, rooms[choose - 1]);
			continue;
		}
	}

	rooms[choose - 1]->setStatus(false);
}

void HotelManagement::addGuest(int guestId, int roomId) {
	for (auto room : this->rooms) {
		if (room->getId() == roomId) {
			if (room->getStatus()) {
				throw room_not_rented();
			}
			for (auto guest : guests) {
				if (guest->getId() == guestId) {
					room->addGuest(guest);
				}
			}
		}
	}
}

double HotelManagement::checkOut(int guestId) {
	double amount = 0;
	for (auto bill : bills) {
		if (bill->getGuestId() == guestId) {
			amount = bill->getAmount();
		}
	}

	if (amount == 0) {
		throw not_rented();
	}

	for (auto guest : this->guests) {
		if (guest->getId() == guestId) {
			for (auto room : this->rooms) {
				if (room->getNumber() == guest->getRoomNumber()) {
					room->checkOut();
					continue;
				}
			}
			guest->setRoomNumber(-1);
			continue;
		}
	}

	return amount;
}

void HotelManagement::showRooms() {
	for (auto room : this->rooms) {
		room->showInfo();
		cout << endl;
	}
}

void HotelManagement::showGuests() {
	for (auto guest : this->guests) {
		guest->showInfo();
		cout << endl;
	}
}

void HotelManagement::showBills() {
	for (auto bill : this->bills) {
		bill->showInfo();
		cout << endl;
	}
}

void HotelManagement::save() {
	ofstream out("Hotel.txt");

	if (out.is_open()) {
		out << "гости" << endl;
		for (auto guest : this->guests) {
			guest->save(out);
		}
		out << "комнаты" << endl;
		for (auto room : this->rooms) {
			room->save(out);
		}
		out << "счета" << endl;
		for (auto bill : this->bills) {
			bill->save(out);
		}
	}
}

void HotelManagement::addBill(Bill* bill) {
	this->bills.push_back(bill);
}

system_clock::time_point HotelManagement::parseTimePoint(const string& timeStr) {
	istringstream iss(timeStr);
	tm t = {};
	iss >> get_time(&t, "%Y-%m-%d %H:%M:%S");
	time_t time = mktime(&t);
	return system_clock::from_time_t(time);
}

string HotelManagement::formatTimePoint(const system_clock::time_point& tp) {
	time_t time = system_clock::to_time_t(tp);
	tm local_tm;
	localtime_s(&local_tm, &time);
	ostringstream oss;
	oss << put_time(&local_tm, "%Y-%m-%d %H:%M:%S");
	return oss.str();
}

void HotelManagement::syncBills() {
	for (auto bill : this->bills) {
		if (bill->getCheckOutDate() > system_clock::now()) {
			for (auto guest : this->guests) {
				if (guest->getId() == bill->getGuestId()) {
					for (auto room : this->rooms) {
						if (room->getId() == bill->getRoomId()) {
							room->addGuest(guest);
							guest->setRoomNumber(room->getNumber());
						}
					}
				}
			}
		}
	}
}

HotelManagement::~HotelManagement() {
	for (auto guest : this->guests) {
		delete guest;
	}
	for (auto room : this->rooms) {
		delete room;
	}
	for (auto bill : this->bills) {
		delete bill;
	}
}
