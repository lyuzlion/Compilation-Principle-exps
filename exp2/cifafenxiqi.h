#ifndef _LEXER_H
#define _LEXER_H
#include<bits/stdc++.h>
#include"struct.h"
using namespace std;
#define Zhuangtai string
#define INIT "1"
#define READING_WORD "2"
#define READING_NUMBER "3"

class Cifafenxiqi
{
public:
    list<Type> Huodesuoyououken(string &shuru,list<string> &shuhebianhao);
private:
    Zhuangtai zhuangtai = INIT;
    int xianzaiweizhi = 0;
    const map<string, Type> endfuhaos = {
        {"int", INTSYM},
        {">=", GE},
        {"then", THENSYM},
        {"scanf", SCANFSYM},
        {"<", LESS},
        {"=", EQU},
        {"||", OR},
        {"==", EQUEQU},
        {"while", WHILESYM},
        {"(", LBRACE1},
        {",", COMMA},
        {">", GREATER},
        {"-", MINUS},
        {"do", DOSYM},
        {"&&", AND},
        {";", SEMICOLON},
        {"{", LBRACE2},
        {"<=", LE},
        {"+", PLUS},
        {"*", TIMES},
        {"if", IFSYM},
        {"printf", PRINTFSYM},
        {"!", NOT},
        {")", RBRACE1},
        {"!=", NOTEQU},
        {"}", RBRACE2},
        {"double", DOUBLESYM},
        {"/", DIVISION},
    };
    

    string huodetouken(string &shuru);
    pair<string, Type> jiexitouken(string &token);
    void yuchuli(string &shuru);
};
#endif