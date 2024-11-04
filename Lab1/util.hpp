#include <string>
#include <iostream>
#include "main.hpp"

void read() {
    std::string line;
    code_src.clear();
    while (std::getline(std::cin, line)) {
        code_src += line + "\n";
        line.clear();
    }
}

void init() {
    std::string temp;
    for (int i = 0; i < code_src.size(); i++) {
        if (code_src[i] == '/' && code_src[i + 1] == '*') {
            i += 2;
            while (code_src[i] != '*' || code_src[i + 1] != '/') i++;
            i += 2;
        }
        temp += code_src[i];
    }
    code_src = temp;
    temp = "";
    for (int i = 0; i < code_src.size(); i++) {
        if (code_src[i] == '/' && code_src[i + 1] == '/') {
            while (code_src[i] != '\n') {
                i++;
            }
        }
        temp += code_src[i];
    }
    code_src = temp;
    temp = "";
    for (int i = 0; i < code_src.size(); i++) {
        if (code_src[i] == '\n' || code_src[i] == '\t' || code_src[i] == '\r')
            code_src[i] = ' ';
    }
    temp = "";
    for (int i = 0; i < code_src.size(); i++) {
        if (code_src[i] == ' ' && code_src[i + 1] == ' ')
            continue;
        temp += code_src[i];
    }
    code_src = temp;
}