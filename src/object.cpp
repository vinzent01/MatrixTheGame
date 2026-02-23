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

 string Object::Type() const{
    return "Object";
}

void Object::Use(Player& player, Terminal& terminal){

}

Computer::Computer(){

}

Computer::Computer(std::string name, std::string description, std::string laying){
    this->Name = name;
    this->Description = description;
    this->count =1;
    this->laying = laying;
}

string Computer::Type() const{
    return "Computer";
}

void Computer::Use(Player& player, Terminal& terminal){
    terminal.AddEntry("Using computer...");
}

// object factory to enable polymorfism on Objects
std::shared_ptr<Object> ObjectFactory(const json& j) {
    std::string type = j.at("type").get<std::string>();
    
    if (type == "Computer") {
        auto obj = std::make_shared<Computer>();
        j.get_to(*obj);
        return obj;
    } 
    else {
        auto obj = std::make_shared<Object>();
        j.get_to(*obj);
        return obj;
    }
}

// JSON 
void to_json(json& j, const Object& o) {
    j = {
        {"name", o.Name},
        {"description", o.Description},
        {"laying", o.laying},
        {"count", o.count},
        {"type", o.Type()}

    };
};

void to_json(json& j, const Entity& e) {
    j = {
        {"name", e.Name},
        {"description", e.Description},
        {"type", typeid(e).name()}
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