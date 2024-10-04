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
		if (data == "гости") {
			cout << "Нашли сохранение, хотите загрузить или сбросить? (1 – загрузить, 2 – выбросить): ";
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
		cout << "1 - Добавить нового гостя" << endl \
			<< "2 - Добавить новую комнату" << endl \
			<< "3 - Зарегистрируйтесь в качестве гостя" << endl \
			<< "4 - Добавить гостя в номер" << endl \
			<< "5 - Выезд гостя" << endl \
			<< "6 - Проверить список номеров" << endl \
			<< "7 - Проверить список гостей" << endl \
			<< "8 - Проверить список счетов" << endl \
			<< "9 - Сохранить и выйти" << endl \
			<< "Выберите, что делать: ";
		cin >> choose;

		switch (choose) {
		case 1:
			cout << "Введите имя и телефон: ";
			cin >> name >> phone;
			cout << "Введите возраст: ";
			cin >> age;
			manager.addGuest(name, age, phone);
			break;
		case 2:
			cout << "Введите номер комнаты и количество спальных мест: ";
			cin >> number >> beds;
			cout << "Введите тип номера (1 - Стандарт, 2 - VIP, 3 - Премиум, 4 - Люкс): ";
			cin >> type;
			type--;
			cout << "Введите стоимость номера: ";
			cin >> price;
			cout << "Введите название комнаты: ";
			cin >> title;
			cout << "Предоставить джакузи, мини-бар, телевизор, Wi-Fi? (1 – Предоставлять, 2 – Не предоставлять): ";
			cin >> isJacuzzi >> isMinibar >> isTV >> isWifi;

			manager.addRoom(number, HOTEL_ROOM_TYPES(type), title, beds, price)
				->provideJacuzzi(isJacuzzi)
				->provideMinibar(isMinibar)
				->provideTV(isTV)
				->provideWifi(isWifi);
			break;
		case 3:
			manager.showGuests();
			cout << "Введите идентификатор гостя, чтобы зарегистрироваться: ";
			cin >> guestId;
			cout << "Введите тип номера (1 - Стандарт, 2 - VIP, 3 - Премиум, 4 - Люкс): ";
			cin >> type;
			type--;
			cout << "Входные кровати: ";
			cin >> beds;
			cout << "Как долго в днях: ";
			cin >> days;

			out = system_clock::now() + hours(24 * days);

			manager.checkIn(guestId, beds, HOTEL_ROOM_TYPES(type), &out);
			break;
		case 4:
			manager.showGuests();
			cout << "Введите идентификатор гостя, который нужно добавить: ";
			cin >> guestId;
			manager.showRooms();
			cout << "Введите идентификатор комнаты, которую нужно добавить: ";
			cin >> roomId;

			manager.addGuest(guestId, roomId);
			break;
		case 5:
			manager.showGuests();
			cout << "Введите идентификатор гостя, чтобы оформить заказ: ";
			cin >> guestId;
			cout << "Гостю придется заплатить: " << manager.checkOut(guestId) << endl;
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
			cout << "Неизвестная операция." << endl;
		}
	}

	return 0;
}