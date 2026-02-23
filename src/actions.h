#pragma once
#include <string>
#include <vector>
#include <memory>

// Forward Declarations
class Player;
class Action;
class Terminal;
class Object;
class Entity;
class Room;

using namespace std;

std::vector<shared_ptr<Action>> GetAllActions();
std::vector<shared_ptr<Action>> GetAllMenuActions();

class Action {
    public:
    std::vector<string> Aliases;
    std::string Description;

    Action(vector<string> aliases, std::string description);
    void virtual Execute(Player& player, Terminal& terminal, vector<string> args);
};

class LookAction : public Action{
    public :
    LookAction();

    void Execute(Player& player, Terminal& terminal, vector<string> args) override;
};

class ExitAction : public Action{
    public:
    ExitAction();

    void Execute(Player& player, Terminal& terminal, vector<string> args) override;
};

class ClearAction : public Action{
    public:
    ClearAction();
    void Execute(Player& player, Terminal& terminal, vector<string> args) override;
};

class MoveAction : public Action{
    public:
    MoveAction();
    void Execute(Player& player, Terminal& terminal, vector<string> args) override;
};

class HelpAction : public Action {
    public :
    HelpAction();

    void Execute(Player& player, Terminal& terminal, vector<string> args) override;
};

class HelpMenuAction : public Action {
    public :
    HelpMenuAction();

    void Execute(Player& player, Terminal& terminal, vector<string> args) override;
};

class StartNewGameAction : public Action {
    public :
    StartNewGameAction();

    void Execute(Player& player, Terminal& terminal, vector<string> args) override;
};

class SaveGameAction : public Action {
    public :
    SaveGameAction();

    void Execute(Player& player, Terminal& terminal, vector<string> args) override;
};

class LoadGameAction : public Action {
    public :
    LoadGameAction();

    void Execute(Player& player, Terminal& terminal, vector<string> args) override;
};

class UseAction : public Action {
    public :

    UseAction();

    void Execute(Player& player, Terminal& terminal, std::vector<std::string> args) override;
};
