#include "world.h"
#include "object.h"
#include "room.h"

World::World() {
    auto room1 = make_shared<Room>(1, "neo room", "An a room full of electronic devices with a PC");

    // Adiciona objetos
    room1->AddObject(make_shared<Computer>("pc", "neo's personal computer"));
    room1->AddObject(make_shared<Object>("Calculator", "Old Calculator"));

    // Adiciona ao map
    rooms[1] = room1;
}

json to_json(const World& world) {
    json j;
    j["rooms"] = json::array();

    // Serializa cada sala chamando o to_json de Room
    for (const auto& [id, roomPtr] : world.rooms) {
        json roomJson;
        
        to_json(roomJson, *roomPtr);  // chama o to_json já definido para Room

        j["rooms"].push_back(roomJson);
    }

    return j;
}

World WorldFromJson(const json& j) {
    World world;
    world.rooms.clear();

    // 1) Cria todas as salas vazias e popula basicamente os campos via from_json(Room)
    for (const auto& roomJson : j["rooms"]) {
        int id = roomJson["id"];
        auto roomPtr = std::make_shared<Room>();
        from_json(roomJson, *roomPtr);  // usa a função já existente
        world.rooms[id] = roomPtr;
    }

    // 2) Recria as conexões (Exits) usando IDs
    for (const auto& roomJson : j["rooms"]) {
        int id = roomJson["id"];
        auto roomPtr = world.rooms[id];

        for (auto& [dir, targetIdJson] : roomJson["Exits"].items()) {
            int targetId = targetIdJson.get<int>();
            roomPtr->Connect(dir, world.rooms[targetId]);
        }
    }

    return world;
}