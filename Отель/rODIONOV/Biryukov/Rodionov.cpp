#include <iostream>
#include "HotelManagement.h"
#include "Constants.h"
#include <ctime>
#include <chrono>
#include "HotelManagementAdapter.h"
#include <fstream>
#include <string>
using namespace std;
using namespace std::chrono;

int main()


{	
	setlocale(LC_ALL, "Russian");
	HotelManagement manager;
	int choose;

	ifstream in("Hotel.txt");

	if (in.is_open()) {
		string data;
		getline(in, data);
		if (data == "�����") {
			cout << "����� ����������, ������ ��������� ��� ��������? (1 � ���������, 2 � ���������): ";
			int load;
			cin >> load;
			if (load == 1) {
				manager = *HotelManagementAdapter::getHotelManagement();
			}
			in.close();
		}
	}

	// Guest creation variables
	string name, phone;
	short age;

	//room
	int number, beds, type;
	string title;
	double price;

	bool isJacuzzi, isMinibar, isTV, isWifi;

	//guest
	int guestId, days, roomId;
	system_clock::time_point now, out;

	bool flag = true;

	while(flag) {
		cout << "1 - �������� ������ �����" << endl \
			<< "2 - �������� ����� �������" << endl \
			<< "3 - ����������������� � �������� �����" << endl \
			<< "4 - �������� ����� � �����" << endl \
			<< "5 - ����� �����" << endl \
			<< "6 - ��������� ������ �������" << endl \
			<< "7 - ��������� ������ ������" << endl \
			<< "8 - ��������� ������ ������" << endl \
			<< "9 - ��������� � �����" << endl \
			<< "��������, ��� ������: ";
		cin >> choose;

		switch (choose) {
		case 1:
			cout << "������� ��� � �������: ";
			cin >> name >> phone;
			cout << "������� �������: ";
			cin >> age;
			manager.addGuest(name, age, phone);
			break;
		case 2:
			cout << "������� ����� ������� � ���������� �������� ����: ";
			cin >> number >> beds;
			cout << "������� ��� ������ (1 - ��������, 2 - VIP, 3 - �������, 4 - ����): ";
			cin >> type;
			type--;
			cout << "������� ��������� ������: ";
			cin >> price;
			cout << "������� �������� �������: ";
			cin >> title;
			cout << "������������ �������, ����-���, ���������, Wi-Fi? (1 � �������������, 2 � �� �������������): ";
			cin >> isJacuzzi >> isMinibar >> isTV >> isWifi;

			manager.addRoom(number, HOTEL_ROOM_TYPES(type), title, beds, price)
				->provideJacuzzi(isJacuzzi)
				->provideMinibar(isMinibar)
				->provideTV(isTV)
				->provideWifi(isWifi);
			break;
		case 3:
			manager.showGuests();
			cout << "������� ������������� �����, ����� ������������������: ";
			cin >> guestId;
			cout << "������� ��� ������ (1 - ��������, 2 - VIP, 3 - �������, 4 - ����): ";
			cin >> type;
			type--;
			cout << "������� �������: ";
			cin >> beds;
			cout << "��� ����� � ����: ";
			cin >> days;

			out = system_clock::now() + hours(24 * days);

			manager.checkIn(guestId, beds, HOTEL_ROOM_TYPES(type), &out);
			break;
		case 4:
			manager.showGuests();
			cout << "������� ������������� �����, ������� ����� ��������: ";
			cin >> guestId;
			manager.showRooms();
			cout << "������� ������������� �������, ������� ����� ��������: ";
			cin >> roomId;

			manager.addGuest(guestId, roomId);
			break;
		case 5:
			manager.showGuests();
			cout << "������� ������������� �����, ����� �������� �����: ";
			cin >> guestId;
			cout << "����� �������� ���������: " << manager.checkOut(guestId) << endl;
			break;
		case 6:
			manager.showRooms();
			break;
		case 7:
			manager.showGuests();
			break;
		case 8:
			manager.showBills();
			break;
		case 9:
			manager.save();
			flag = false;
			break;
		default:
			cout << "����������� ��������." << endl;
		}
	}

	return 0;
}