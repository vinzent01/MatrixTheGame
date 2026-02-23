#include "terminal.h"


Terminal::Terminal(){
    font_size = 24;
    font = LoadFont("mozart.ttf");
}

void Terminal::Start(){

}

void Terminal::Clear(){
    history.clear();
}

void Terminal::AddEntry(std::string entry){
    vector<string> lines = split_lines(entry);
    for (auto line : lines){
        history.push_back(line);
    }
}

std::string Terminal::Update(){

    int key = GetCharPressed();
    while (key > 0)
    {
        if (key >= 32 && key <= 125)
            currentInput.push_back((char)key);

        key = GetCharPressed();
    }

    if (IsKeyPressed(KEY_BACKSPACE) && !currentInput.empty())
        currentInput.pop_back();

    if (IsKeyPressed(KEY_ENTER))
    {
        history.push_back("> " + currentInput);
        std::string output = currentInput;
        currentInput.clear();
        return output;
    }

    int totalLines = history.size();
    scrollOffset += GetMouseWheelMove();
    scrollOffset = clamp(scrollOffset, 0, totalLines);

    return "";
}

void Terminal::Draw(int x, int y)
{
    int linesVisible = (GetScreenHeight() - y - font_size*3) / font_size;

    int total = history.size();
    int start = std::max(0, total - linesVisible - scrollOffset);
    int end   = std::min(total, start + linesVisible);

    for(int i = start; i < end; i++){
        DrawTextEx(font, history[i].c_str(), { (float)x, (float)y }, font_size, 0, GREEN);
        y += font_size;
    }

    // prompt
    y += font_size;
    DrawTextEx(font, "> ", {10,(float)y}, font_size,0,YELLOW);
    DrawTextEx(font, currentInput.c_str(), {30,(float)y}, font_size,0,YELLOW);
}



std::string Terminal::Prompt(std::string prompt){
    if (prompt != ""){
        AddEntry(prompt);
    }

    std::string output = "";

    while (output == "")
    {

        if (WindowShouldClose()){
            std::exit(0);
            break;
        }

        output = Update();

        BeginDrawing();
            float delta = GetFrameTime();
            float y = 0;

            ClearBackground(BLACK);            

            Draw(10,10);

        EndDrawing();
    }
    return output;
}
