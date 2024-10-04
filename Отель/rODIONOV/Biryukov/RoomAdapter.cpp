#include "RoomAdapter.h"

BaseRoom* RoomAdapter::getRoom(Str data) {
    Str* params = data.split(';');
    BaseRoom* room = nullptr;

    if (params[1] == "0") {
        room = new StandartRoom(stoi(params[0]), HOTEL_ROOM_TYPES(stoi(params[1])), params[2], stoi(params[3]), stod(params[4]));
    }
    else if (params[1] == "1") {
        room = new VIPRoom(stoi(params[0]), HOTEL_ROOM_TYPES(stoi(params[1])), params[2], stoi(params[3]), stod(params[4]));
    }
    else if (params[1] == "2") {
        room = new PremiumRoom(stoi(params[0]), HOTEL_ROOM_TYPES(stoi(params[1])), params[2], stoi(params[3]), stod(params[4]));
    }
    else if (params[1] == "3") {
        room = new LuxRoom(stoi(params[0]), HOTEL_ROOM_TYPES(stoi(params[1])), params[2], stoi(params[3]), stod(params[4]));
    }

    room->provideJacuzzi(stoi(params[5]))
        ->provideMinibar(stoi(params[6]))
        ->provideTV(stoi(params[7]))
        ->provideWifi(stoi(params[8]))
        ->setStatus(stoi(params[9]));

    return room;
}
