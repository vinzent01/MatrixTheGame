#pragma once
#include <string>
#include <vector>
#include <map>
#include <memory>
#include "json.hpp"

// Forward declarations
class Object;
class Entity;

using nlohmann::json;
using namespace std;

class Room{
    public:
    int Id;
    string Name;
    string Description;
    vector<Object> Objects;
    vector<Entity> Entities;
    map<string, shared_ptr<Room>> Exits;

    Room();

    Room(int id, string name, string description);

    string GetDescription();

    void AddObject(Object obj);

    void AddEntity(Entity entity);

    void Connect(string exit, shared_ptr<Room> room);
};

void to_json(json& j, const Room& r);
void from_json(const json& j, Room& r);