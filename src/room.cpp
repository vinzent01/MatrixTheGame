#include "room.h"
#include "object.h"

using nlohmann::json;
using namespace std;

Room::Room(){

}

Room::Room(int id, string name, string description){
    this->Id = id;
    this->Name = name;
    this->Description = description;
}

string Room::GetDescription(){
    string fullDescription = "";
    fullDescription += "You are in a " + Description + "\n";
    
    if (Objects.size() > 0){
        for (auto& obj : Objects){
            fullDescription += "with a " + obj->Description;
        }

        fullDescription += "\n";
    }

    if (Entities.size() > 0){
        for (auto& entity : Entities){
            fullDescription += "with a " + entity->Description;
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

void Room::AddObject(shared_ptr<Object> obj){
    Objects.push_back(obj);
}

void Room::AddEntity(shared_ptr<Entity> entity){
    Entities.push_back(entity);
}

void Room::Connect(string exit, shared_ptr<Room> room){
    Exits[exit] = room;
}

void to_json(json& j, const Room& r) {
    j = {
        {"id", r.Id},
        {"name", r.Name},
        {"description", r.Description}
    };

    // Objects
    j["Objects"] = json::array();
    for (auto& objPtr : r.Objects) {
        j["Objects"].push_back(*objPtr); // usa o to_json de Object
    }

    // Entities
    j["Entities"] = json::array();
    for (auto& entPtr : r.Entities) {
        j["Entities"].push_back(*entPtr);
    }

    // Exits: só IDs das salas
    json exitsJson = json::object();
    for (auto& [dir, roomPtr] : r.Exits) {
        exitsJson[dir] = roomPtr->Id;
    }
    j["Exits"] = exitsJson;
}

void from_json(const json& j, Room& r) {
    j.at("id").get_to(r.Id);
    j.at("name").get_to(r.Name);
    j.at("description").get_to(r.Description);

    r.Objects.clear();
    for (auto& objJson : j.at("Objects")) {
        r.Objects.push_back(ObjectFactory(objJson));
    }

    r.Entities.clear();
    for (auto& entJson : j.at("Entities")) {
        auto ent = std::make_shared<Entity>();
        entJson.get_to(*ent);
        r.Entities.push_back(ent);
    }

    // Exits: liga depois usando IDs
}