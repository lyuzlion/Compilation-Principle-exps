#include <iostream>
#include <map>
#include <list>
#include <string>
#include <vector>
#include <utility>
#include "main.hpp"
#include "util.hpp"

std::list<std::pair<std::string, std::string>> output;

std::string getToken() {
    std::string token;
    state = INIT;
    while (code_src[currentPos] == ' ' && currentPos < code_src.size())
        currentPos++;
    while (currentPos < code_src.size()) {
        switch (state) {
        case INIT:
            if (isalpha(code_src[currentPos])) {
                state = READING_WORD;
                token += code_src[currentPos];
            } else if (isdigit(code_src[currentPos]) || code_src[currentPos] == '.') {
                state = READING_NUMBER;
                token += code_src[currentPos];
            } else if (std::string("=><!").find(code_src[currentPos]) != std::string::npos) {
                token += code_src[currentPos];
                currentPos++;
                if (code_src[currentPos] == '=') {
                    token += code_src[currentPos];
                    currentPos++;
                }
                return token;
            } else if (std::string("&|").find(code_src[currentPos]) != std::string::npos) {
                token += code_src[currentPos];
                currentPos++;
                if (code_src[currentPos] == code_src[currentPos - 1]) {
                    token += code_src[currentPos];
                    currentPos++;
                }
                return token;
            } else if (std::string("{};(),+-*/").find(code_src[currentPos]) != std::string::npos) {
                token += code_src[currentPos];
                currentPos++;
                return token;
            } else {
                std::cout << "Unrecognizable characters.";
                exit(0);
            }
            currentPos++;
            break;
        case READING_WORD:
            if (std::isalpha(code_src[currentPos]) || std::isdigit(code_src[currentPos])) token += code_src[currentPos];
            else return token;
            currentPos++;
            break;
        case READING_NUMBER:
            if (std::isdigit(code_src[currentPos]) || code_src[currentPos] == '.')
                token += code_src[currentPos];
            else return token;
            currentPos++;
            break;
        default:
            break;
        }
    }
    return token;
}

void parserToken(std::string &token)
{
    std::pair<std::string, std::string> temp;
    temp.first = token;

    if (keywords.find(token) != keywords.end())
        temp.second = keywords.at(token);
    else if (symbols.find(token) != symbols.end())
        temp.second = symbols.at(token);
    else if (std::isalpha(token[0]))
        temp.second = "IDENT";
    else if (std::isdigit(token[0]) || token[0] == '.') {
        if (token[0] == '.' || token[token.size() - 1] == '.') {
            std::cout << "Malformed number: Decimal point at the beginning or end of a floating point number.";
            exit(0);
        }
        if (token[0] == '0') {
            if (token.size() > 1) {
                if (token[1] != '.') {
                    std::cout << "Malformed number: Leading zeros in an integer.";
                    exit(0);
                }
            }
        }
        bool hasDot = false;
        for (int i = 0; i < token.size(); i++) {
            if (token[i] == '.') {
                if (hasDot) {
                    std::cout << "Malformed number: More than one decimal point in a floating point number.";
                    exit(0);
                }
                hasDot = true;
            } else if (!std::isdigit(token[i])) {
                std::cout << "Malformed number: Non-digit character in a number.";
                exit(0);
            }
        }
        if (hasDot) temp.second = "DOUBLE";
        else temp.second = "INT";
    }
    output.push_back(temp);
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);
    
    read();
    
    init();
    
    while (true) {
        std::string token = getToken();
        if (token == "") break;
        parserToken(token);
    }

    for (const auto& [first, second] : output) {
        std::cout << first << " " << second << std::endl;
    }
    return 0;
}