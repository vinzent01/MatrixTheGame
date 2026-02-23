#pragma once
#include <string>
#include <vector>
#include <map>
#include <memory>
#include "json.hpp"

using nlohmann::json;
using namespace std;

class Entity {
    public :
    string Name;
    string Description;

    Entity() = default;

    Entity(string name, string description){
        this->Name = name;
        this->Description = description;
    }
};

class Object {
    public:
    string Name;
    string Description;
    string laying;
    int count;

    Object() =default;

    Object(string name, string description, string laying="", int count=1){
        this->Name = name;
        this->Description = description;
        this->laying = laying;
        this->count = count;
    };
};

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

class Room{
    public:
    int Id;
    string Name;
    string Description;
    vector<Object> Objects;
    vector<Entity> Entities;
    map<string, shared_ptr<Room>> Exits;

    Room(){

    }

    Room(int id, string name, string description){
        this->Id = id;
        this->Name = name;
        this->Description = description;
    }

    string GetDescription(){
        string fullDescription = "";
        fullDescription += "You are in a " + Description + "\n";
        
        if (Objects.size() > 0){
            for (auto& obj : Objects){
                fullDescription += "with a " + obj.Description;
            }

            fullDescription += "\n";
        }

        if (Entities.size() > 0){
            for (auto& entity : Entities){
                fullDescription += "with a " + entity.Description;
            }
    
            fullDescription += "\n";
        }


        if (Exits.size() > 0){
            fullDescription += "Exits : ";
            std::vector<std::string> exits_str;

            for (const auto& [key, value] : Exits) {
                exits_str.push_back(key);
            }
            
            size_t i = 0;
            for (auto& exit : exits_str){
                fullDescription += exit;

                if (i != exits_str.size()-1){
                    fullDescription += ", ";
                }

                i++;
            }
        }
        return fullDescription;
    }

    void AddObject(Object obj){
        Objects.push_back(obj);
    }

    void AddEntity(Entity entity){
        Entities.push_back(entity);
    }

    void Connect(string exit, shared_ptr<Room> room){
        Exits[exit] = room;
    }
};

void to_json(json& j, const Room& r) {
    j = {
        {"name", r.Name},
        {"description", r.Description},
        {"Objects", r.Objects},
        {"Entities", r.Entities}
    };
};

void from_json(const json& j, Room& r){
    j.at("id").get_to(r.Id);
    j.at("name").get_to(r.Name);
    j.at("description").get_to(r.Description);
    j.at("Objects").get_to(r.Objects);
    j.at("Entities").get_to(r.Entities);
}