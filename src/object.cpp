#include "object.h"
#include "terminal.h"
#include "player.h"

using nlohmann::json;
using namespace std;

// Forward declaration

Entity::Entity(string name, string description){
    this->Name = name;
    this->Description = description;
}

Object::Object(string name, string description, string laying, int count){
    this->Name = name;
    this->Description = description;
    this->laying = laying;
    this->count = count;
};

void Object::Use(Player& player, Terminal& terminal){

}

Computer::Computer(std::string user_name, std::string description, std::string laying){
    this->Name = user_name + " Personal Computer";
    this->Description = description;
    this->count =1;
    this->laying = laying;
}

void Computer::Use(Player& player, Terminal& terminal){
    terminal.AddEntry("Using computer...");
}

// JSON 

void to_json(json& j, const Object& o) {
    j = {
        {"name", o.Name},
        {"description", o.Description}
    };
};

void to_json(json& j, const Entity& e) {
    j = {
        {"name", e.Name},
        {"description", e.Description}
    };
};

void from_json(const json& j, Object& o) {
    j.at("name").get_to(o.Name);
    j.at("description").get_to(o.Description);
};

void from_json(const json& j, Entity& e) {
    j.at("name").get_to(e.Name);
    j.at("description").get_to(e.Description);
};