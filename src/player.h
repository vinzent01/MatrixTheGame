#pragma once
#include <string>
#include "room.h"

enum GameState {
    MENU,
    GAME
};

class Player {
    public:
    string Name;
    shared_ptr<Room> CurrentRoom;
    GameState State;
};

