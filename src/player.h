#pragma once
#include <string>
#include "room.h"
#include "json.hpp"
#include <fstream>
#include "world.h"

using nlohmann::json;

enum GameState {
    MENU,
    GAME
};

class Player {
    public:
    shared_ptr<Room> CurrentRoom;
    GameState State;
    World world;
};

void to_json(json& j, const Player& p);
void from_json(const json& j, Player& p);

bool SavePlayer(const Player& p, const std::string& filename);
bool LoadPlayer(Player& p, const std::string& filename);