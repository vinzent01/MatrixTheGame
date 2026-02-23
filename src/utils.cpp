#include "utils.h"
void ParseInput(string input, string& command, vector<string>& args){
    stringstream ss(input);
    string word;

    ss >> command;

    while (ss >> word){
        args.push_back(word);
    }
}

float DrawMultilineText(
    const std::string& text,
    float startX,float startY, 
    float font_size, 
    Font font, 
    float max_width
)
{
    std::vector<std::string> lines;
    std::string current_line;
    float yposition = 0;

    for (size_t i = 0; i < text.size(); i++)
    {
        char c = text[i];
        current_line.push_back(c);

        float measure = MeasureText(current_line.c_str(), font_size);

        if (c == '\n'){
            yposition += font_size;
        }

        if (measure > max_width)
        {
            // remove o último caractere que estourou
            current_line.pop_back();

            lines.push_back(current_line);
            current_line.clear();
            yposition += font_size;

            // começa nova linha com o caractere que sobrou
            current_line.push_back(c);
        }
    }

    // adiciona última linha
    if (!current_line.empty()){
        lines.push_back(current_line);
        yposition += font_size;
    }

    // desenha
    for (size_t i = 0; i < lines.size(); i++)
    {
        DrawTextEx(font,lines[i].c_str(), (Vector2){startX, startY+ (i * font_size)}, font_size, 0,WHITE);
    }

    return yposition;
}


vector<string> split_lines(const string& input_str) {
    vector<string> lines;
    stringstream ss(input_str);
    string line;

    // Use getline with the newline character as the default delimiter
    while (getline(ss, line)) {
        lines.push_back(line);
    }
    return lines;
}

bool ContainsString(const std::string& s, const std::vector<std::string>& v){
    for (const auto& vectorString : v){
        if (vectorString == s)
            return true;
    }
    return false;
}

std::string LoadAsciiArt(const char * filepath) {
    std::ifstream arquivo(filepath);
    if (!arquivo) {
        std::cerr << "Não foi possível abrir o arquivo!\n";
        return "{Unknown}";
    }

    std::stringstream ss;
    std::string linha;

    while (std::getline(arquivo, linha)) {
        ss << linha << "\n"; // adiciona a linha e a quebra de linha
    }

    arquivo.close();

    return ss.str(); // retorna todo o conteúdo do arquivo
}