#pragma once
#include <string>
#include <vector>
#include <map>
#include <memory>
#include "json.hpp"

using nlohmann::json;
using namespace std;

// Forward declaration
class Player;    
class Terminal;

class Entity {
    public :
    string Name;
    string Description;

    Entity() = default;
    Entity(string name, string description);
};

class Object {
    public:
    string Name;
    string Description;
    string laying;
    int count;

    Object() =default;
    Object(string name, string description, string laying="", int count=1);

    virtual void Use(Player& player, Terminal& terminal);
};

class Computer : public Object {
    Computer(std::string user_name, std::string description, std::string laying);
    void Use(Player& player, Terminal& terminal) override;
};

// JSON 

void to_json(json& j, const Object& o);
void to_json(json& j, const Entity& e);

void from_json(const json& j, Object& o);
void from_json(const json& j, Entity& e);