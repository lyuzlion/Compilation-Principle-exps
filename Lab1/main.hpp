#ifndef MAIN_HPP
#include <map>
#include <vector>
#define INIT 0
#define READING_WORD 1
#define READING_NUMBER 2

const std::map<std::string, std::string> keywords = {
    {"int", "INTSYM"},
    {"double", "DOUBLESYM"},
    {"scanf", "SCANFSYM"},
    {"printf", "PRINTFSYM"},
    {"if", "IFSYM"},
    {"then", "THENSYM"},
    {"while", "WHILESYM"},
    {"do", "DOSYM"}};

const std::map<std::string, std::string> symbols = {
    {"=", "AO"},
    {"==", "RO"},
    {">", "RO"},
    {">=", "RO"},
    {"<", "RO"},
    {"<=", "RO"},
    {"||", "LO"},
    {"&&", "LO"},
    {"!", "LO"},
    {"!=", "RO"},
    {"+", "PLUS"},
    {"-", "MINUS"},
    {"*", "TIMES"},
    {"/", "DIVISION"},
    {",", "COMMA"},
    {"(", "BRACE"},
    {")", "BRACE"},
    {"{", "BRACE"},
    {"}", "BRACE"},
    {";", "SEMICOLON"}};

std::string code_src;
std::vector<std::pair<std::string, std::string>> ans;
int state = INIT;
int pos = 0;
#endif