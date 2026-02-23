#include "player.h"

using nlohmann::json;

void to_json(json& j, const Player& p) {
    j = json{
        {"state", p.State},
        {"current_room_id", p.CurrentRoom ? p.CurrentRoom->Id : -1},
        {"world", to_json(p.world)}
    };
}

void from_json(const json& j, Player& p) {
    j.at("state").get_to(p.State);

    // Carrega o mundo primeiro
    p.world = WorldFromJson(j.at("world"));

    // Agora liga a sala atual por ID
    int room_id;
    j.at("current_room_id").get_to(room_id);
    if (room_id >= 0) {
        p.CurrentRoom = p.world.rooms[room_id];
    } else {
        p.CurrentRoom.reset();
    }
}


bool SavePlayer(const Player& p, const std::string& filename) {
    // cria o JSON do player
    json j = p;

    // abre arquivo para escrita
    std::ofstream file(filename);
    if (!file.is_open()) {
        return false;
    }

    // grava com indentação
    file << j.dump(4);
    return true;
}

bool LoadPlayer(Player& p, const std::string& filename) {
    // abre arquivo para leitura
    std::ifstream file(filename);
    if (!file.is_open()) {
        return false;
    }

    // cria um json a partir do arquivo
    json j;
    file >> j;

    // preenche o player com o conteúdo do json
    p = j.get<Player>();

    return true;
}