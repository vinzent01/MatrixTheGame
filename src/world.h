#include <vector>
#include <memory>
#include "map"
#include "room.h"
#include "json.hpp"

using json = nlohmann::json;
using namespace std;

class World{
    public:
    map<int, shared_ptr<Room>> rooms;

    World() {
        auto room1 = make_shared<Room>(1, "dungeon entrance", "an dungeon entrance");
        auto room2 = make_shared<Room>(2, "hall", "an old dusty dungeon hall");

        // Adiciona objetos
        room1->AddObject(Object("large dusty door", "an large old iron door"));
        room2->AddObject(Object("statue", "old marble statue of an knight"));

        // Conecta salas
        room1->Connect("north", room2);
        room2->Connect("south", room1);

        // Adiciona ao map
        rooms[1] = room1;
        rooms[2] = room2;
    }
};


json to_json(const World& world) {
    json j;
    j["rooms"] = json::array();

    // 1. Serializa cada sala em um objeto JSON
    for (const auto& [id, room] : world.rooms) {
        json roomJson;
        roomJson["id"] = id;
        roomJson["name"] = room->Name;
        roomJson["description"] = room->Description;
        roomJson["objects"] = room->Objects;
        roomJson["entities"] = room->Entities;

        // 2. Serializa as *conexões* por ID
        json exitsJson = json::object();
        for (const auto& [dir, otherRoom] : room->Exits) {
            exitsJson[dir] = otherRoom->Id; 
        }
        roomJson["exits"] = exitsJson;

        j["rooms"].push_back(roomJson);
    }

    return j;
}

World WorldFromJson(const json& j) {
    World world;
    world.rooms.clear();

    // 1) Cria todas as salas sem conexões ainda
    for (const auto& roomJson : j["rooms"]) {
        int id = roomJson["id"];
        auto roomPtr = std::make_shared<Room>(
            id,
            roomJson["name"].get<std::string>(),
            roomJson["description"].get<std::string>()
        );

        roomPtr->Objects = roomJson["objects"].get<std::vector<Object>>();
        roomPtr->Entities = roomJson["entities"].get<std::vector<Entity>>();

        world.rooms[id] = roomPtr;
    }

    // 2) Recria as conexões
    for (const auto& roomJson : j["rooms"]) {
        int id = roomJson["id"];
        auto roomPtr = world.rooms[id];

        for (auto& [dir, targetIdJson] : roomJson["exits"].items()) {
            int targetId = targetIdJson.get<int>();
            roomPtr->Connect(dir, world.rooms[targetId]);
        }
    }

    return world;
}