#pragma once
#include <string>
#include <vector>
#include "player.h"
#include "terminal.h"

using namespace std;



class Action {
    public:
    std::vector<std::string> Aliases;
    std::string Description;


    Action(vector<string> aliases, std::string description){
        this->Aliases = aliases;
        this->Description = description;
    }

    void virtual Execute(Player& player, Terminal& terminal, vector<string> args){

    }
};

class LookAction : public Action{

    public :
    LookAction() : Action({"look", "see"}, "look room arround"){

    }

    void Execute(Player& player, Terminal& terminal, vector<string> args) override {
        string description = player.CurrentRoom->GetDescription();
        terminal.AddEntry(description);
    }
};

class ExitAction : public Action{
    public:
    ExitAction() : Action({"exit","quit"}, "exit the game"){

    }

    void Execute(Player& player, Terminal& terminal, vector<string> args) override {
        exit(0);
    }
};

class ClearAction : public Action{
    public:
    ClearAction() : Action({"clear"}, "clear the terminal"){

    }

    void Execute(Player& player, Terminal& terminal, vector<string> args) override {
        terminal.Clear();
    }
};

class MoveAction : public Action{
    public:
    MoveAction() : Action({"move", "go"}, "move to an exit room"){

    }

    void Execute(Player& player, Terminal& terminal, vector<string> args) override {

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
};


vector<shared_ptr<Action>> GetAllActions();
vector<shared_ptr<Action>> GetAllMenuActions();


class HelpAction : public Action {
    public :
    HelpAction() : Action({"help"}, "shows all available commands"){

    }

    void Execute(Player& player, Terminal& terminal, vector<string> args) override{
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

};

class HelpMenuAction : public Action {
    public :
    HelpMenuAction() : Action({"help"}, "shows all available commands on the menu"){

    }

    void Execute(Player& player, Terminal& terminal, vector<string> args) override{
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

};

class StartNewGameAction : public Action {
    public :
    StartNewGameAction() : Action({"start"}, "start an game"){

    };

    void Execute(Player& player, Terminal& terminal, vector<string> args) override{
        player.State = GAME;
        player.world = World();
        player.CurrentRoom = player.world.rooms[1];
    }
};

class SaveGameAction : public Action {
    public :
    SaveGameAction() : Action({"save"}, "save the game"){

    }

    void Execute(Player& player, Terminal& terminal, vector<string> args) override {
        SavePlayer(player, "./saves/01.json");
    }
};

class LoadGameAction : public Action {
    public :
    LoadGameAction() : Action({"Load"}, "load the game"){

    }

    void Execute(Player& player, Terminal& terminal, vector<string> args) override {
        terminal.AddEntry("Loading save...");
        LoadPlayer(player, "./saves/01.json");
    }
};

vector<shared_ptr<Action>> GetAllActions(){
    return {
        make_shared<LookAction>(),
        make_shared<ExitAction>(),
        make_shared<ClearAction>(),
        make_shared<MoveAction>(),
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