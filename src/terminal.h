#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <raylib.h>
#include "utils.h"
#include <algorithm>

using namespace std;

class Terminal{
    float font_size;

    vector<string> history;
    string currentInput;
    Font font;
    int scrollOffset = 0; 

    public:

    Terminal();

    void Start();

    void Clear();

    void AddEntry(std::string entry);
    
    void Draw(int x, int y);
    
    std::string Update();
    std::string Prompt(std::string prompt);
};
