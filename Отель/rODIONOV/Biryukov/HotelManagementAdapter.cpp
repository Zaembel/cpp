#include "HotelManagementAdapter.h"

HotelManagement* HotelManagementAdapter::getHotelManagement() {
    HotelManagement* hotel = new HotelManagement;
    ifstream in("Hotel.txt");
    string data;
    int recoveryType = 0;

    if (in.is_open()) {
        while (getline(in, data)) {
            switch (recoveryType) {
            case 0:
                recoveryType = 1;
                break;
            case 1:
                if (data == "комнаты") {
                    recoveryType = 2;
                    break;
                }
                hotel->addGuest(GuestAdapter::getGuest(data.c_str()));
                break;
            case 2:
                if (data == "счета") {
                    recoveryType = 3;
                    break;
                }
                hotel->addRoom(RoomAdapter::getRoom(data.c_str()));
                break;
            case 3:
                hotel->addBill(BillAdapter::getBill(data.c_str()));
            }
        }
    }

    hotel->syncBills();

    return hotel;
}
