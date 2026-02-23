#include "actions.h"
#include "player.h"
#include "object.h"
#include "terminal.h"

using namespace std;

Action::Action(vector<string> aliases, std::string description){
    this->Aliases = aliases;
    this->Description = description;
}

void Action::Execute(Player& player, Terminal& terminal, vector<string> args){

}

LookAction::LookAction() : Action({"look", "see"}, "look room arround"){

}

void LookAction::Execute(Player& player, Terminal& terminal, vector<string> args)  {
    string description = player.CurrentRoom->GetDescription();
    terminal.AddEntry(description);
}

ExitAction::ExitAction() : Action({"exit","quit"}, "exit the game"){

}

void ExitAction::Execute(Player& player, Terminal& terminal, vector<string> args)  {
    exit(0);
}

ClearAction::ClearAction() : Action({"clear"}, "clear the terminal"){

}

void ClearAction::Execute(Player& player, Terminal& terminal, vector<string> args)  {
    terminal.Clear();
}

MoveAction::MoveAction() : Action({"move", "go"}, "move to an exit room"){

}

void MoveAction::Execute(Player& player, Terminal& terminal, vector<string> args)  {

    if (args.size() < 1){
        terminal.AddEntry("where?");
        return;
    }

    auto& nextRoom = args[0];
    if (player.CurrentRoom->Exits.count(nextRoom) > 0){
        player.CurrentRoom = player.CurrentRoom->Exits[nextRoom];
        terminal.AddEntry(
            player.CurrentRoom->GetDescription()
        );
    }
}



HelpAction::HelpAction() : Action({"help"}, "shows all available commands"){

}

void HelpAction::Execute(Player& player, Terminal& terminal, vector<string> args) {
    for (auto& action : GetAllActions()){

        string aliasesStr = "";

        for (size_t i =0; i< action->Aliases.size(); i++){
            aliasesStr += action->Aliases[i];

            if (i < action->Aliases.size()-1){
                aliasesStr += ", ";
            }
        }

        terminal.AddEntry(
            aliasesStr + " - "+ action->Description
        );
    }
}

HelpMenuAction::HelpMenuAction() : Action({"help"}, "shows all available commands on the menu"){
    
}

void HelpMenuAction::Execute(Player& player, Terminal& terminal, vector<string> args) {
    for (auto& action : GetAllMenuActions()){

        string aliasesStr = "";

        for (size_t i =0; i< action->Aliases.size(); i++){
            aliasesStr += action->Aliases[i];

            if (i < action->Aliases.size()-1){
                aliasesStr += ", ";
            }
        }

        terminal.AddEntry(
            aliasesStr + " - "+ action->Description
        );
    }
}

StartNewGameAction::StartNewGameAction() : Action({"start"}, "start an game"){

};

void StartNewGameAction::Execute(Player& player, Terminal& terminal, vector<string> args){
    player.State = GAME;
    player.world = World();
    player.CurrentRoom = player.world.rooms[1];
}

SaveGameAction::SaveGameAction() : Action({"save"}, "save the game"){

}

void SaveGameAction::Execute(Player& player, Terminal& terminal, vector<string> args) {
    SavePlayer(player, "./saves/01.json");
}

LoadGameAction::LoadGameAction() : Action({"load"}, "load the game"){

}

void LoadGameAction::Execute(Player& player, Terminal& terminal, vector<string> args)  {
    terminal.AddEntry("Loading save...");
    LoadPlayer(player, "./saves/01.json");
}

UseAction::UseAction() : Action({"use"}, "use some object"){

}

void UseAction::Execute(Player& player, Terminal& terminal, std::vector<std::string> args)  {
    if (args.empty()) {
        terminal.AddEntry("Use what?");
        return;
    }

    std::string objectName = args[0];

    // 1 Procura na sala
    for (auto& obj : player.CurrentRoom->Objects) {
        if (obj->Name == objectName) {
            obj->Use(player, terminal);  // chama a ação do objeto
            return;
        }
    }

    // 2 Procura no inventário
    /// *

    terminal.AddEntry("There is no " + objectName + " in this room or inventory");
};

vector<shared_ptr<Action>> GetAllActions(){
    return {
        make_shared<LookAction>(),
        make_shared<ExitAction>(),
        make_shared<ClearAction>(),
        make_shared<MoveAction>(),
        make_shared<UseAction>(),
        make_shared<SaveGameAction>(),
        make_shared<HelpAction>()
    };
};


vector<shared_ptr<Action>> GetAllMenuActions(){
    return {
        make_shared<StartNewGameAction>(),
        make_shared<LoadGameAction>(),
        make_shared<HelpMenuAction>(),
    };
}