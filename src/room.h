#pragma once
#include <string>
#include <vector>
#include <map>
#include <memory>

using namespace std;

class Entity {
    public :
    string Name;
    string Description;

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

    Object(string name, string description, string laying="", int count=1){
        this->Name = name;
        this->Description = description;
        this->laying = laying;
        this->count = count;
    }
};

class Room{
    public:
    string Name;
    string Description;
    vector<Object> Objects;
    vector<Entity> Entities;
    map<string, shared_ptr<Room>> Exits;

    Room(string name, string description){
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

shared_ptr<Room> CreateWorld(){

    auto dungeon_entrance = make_shared<Room>("dungeon entrane", "an dungeon entrance");
    auto hall = make_shared<Room>("hall","an old dusty dungeon hall");

    dungeon_entrance->AddObject(
        Object("large dusty door", "an large old iron door")
    );
    
    hall->AddObject(
        Object("statue", "old marble statue of an knight", "on the center", 1)
    );

    dungeon_entrance->Connect("north", hall);
    hall->Connect("south", dungeon_entrance);


    return dungeon_entrance;
}