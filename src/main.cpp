#include <string>
#include <vector>
#include <raylib.h>
#include "utils.h"
#include "terminal.h"
#include "player.h"
#include "actions.h"

using namespace std;


int main(){

    InitWindow(800,800,"Matrix The Game");
    SetTraceLogLevel(LOG_NONE);

    float screenWidth = GetScreenWidth();
    float screenHeight = GetScreenHeight();

    Terminal terminal;

    terminal.AddEntry(LoadAsciiArt("./arts/logo.txt")+ "\n");
    terminal.AddEntry("Type (help) for help.");

    auto exit = false;
    auto first_entrance = true;

    Player player;

    
    while (exit == false)
    {
        vector<shared_ptr<Action>> actions;

        if (player.State == MENU){
            actions = GetAllMenuActions();
        }
        else if (player.State == GAME){
            actions = GetAllActions();
        }

        string prompt = terminal.Prompt("");
        string command = "";
        vector<string> args;



        ParseInput(prompt,command,args);        
        
        for (auto& action : actions){
            if (ContainsString(command, action->Aliases)){
                action->Execute(player, terminal, args);
            }
        }

        if (player.State == GAME && first_entrance ){
            
            LookAction lookAction;
            lookAction.Execute(player, terminal, {});
            first_entrance = false;
        }

        terminal.AddEntry("\n");
    }

    return 0;
}