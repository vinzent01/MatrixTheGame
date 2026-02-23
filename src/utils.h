#pragma once

#include <raylib.h>
#include <string>
#include <vector>
#include <sstream>
#include "memory"
#include <fstream>
#include <iostream>

using namespace std;

void ParseInput(string input, string& command, vector<string>& args);
float DrawMultilineText(const std::string& text,float startX,float startY, float font_size, Font font, float max_width = 600);
vector<string> split_lines(const string& input_str);
bool ContainsString(const std::string& s, const std::vector<std::string>& v);


string LoadAsciiArt(const char * filepath);