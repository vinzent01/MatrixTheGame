#pragma once
#include <vector>
#include <memory>
#include "map"
#include "json.hpp"

using json = nlohmann::json;
using namespace std;

// forward declarations
class Object;
class Entity;
class Room;

class World{
    public:
    map<int, shared_ptr<Room>> rooms;

    World();
};

json to_json(const World& world);
World WorldFromJson(const json& j);