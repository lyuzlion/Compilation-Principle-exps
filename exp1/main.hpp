#ifndef MAIN_HPP
#include <map>
#include <vector>
#include "ru.hpp"
#define STATE1 0
#define STATE2 1
#define STATE3 2
Vector P, Q;
std::map<std::string, std::string> mp1 = {
    {"if", "IFSYM"},
    {"printf", "PRINTFSYM"},
    {"int", "INTSYM"},
    {"double", "DOUBLESYM"},
    {"do", "DOSYM"},
    {"then", "THENSYM"},
    {"while", "WHILESYM"},
    {"scanf", "SCANFSYM"}
};

std::map<std::string, std::string> mp2 = {
    {">", "RO"},
    {";", "SEMICOLON"},
    {"{", "BRACE"},
    {"!=", "RO"},
    {">=", "RO"},
    {",", "COMMA"},
    {"<", "RO"},
    {"!", "LO"},
    {"(", "BRACE"},
    {"&&", "LO"},
    {"||", "LO"},
    {"-", "MINUS"},
    {"}", "BRACE"},
    {")", "BRACE"},
    {"/", "DIVISION"},
    {"<=", "RO"},
    {"+", "PLUS"},
    {"=", "AO"},
    {"==", "RO"},
    {"*", "TIMES"}
};

std::string code_src;
std::vector<std::pair<std::string, std::string>> ans;
int state = STATE1;
int pos = 0;
#endif