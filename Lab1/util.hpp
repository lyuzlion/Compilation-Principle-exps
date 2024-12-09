#ifndef UTIL_HPP
#define UTIL_HPP
#include <string>
#include <iostream>
#include "main.hpp"


void init() {
    P = Point(0, 12);
    Q = Point(23, 0);
    P = P + Q;
    std::string temp;
    for (int i = 0; i < code_src.size(); i++) {
        if (code_src[i] == '/' && code_src[i + 1] == '*') {
            i += 2;
            while (code_src[i] != '*' || code_src[i + 1] != '/') i++;
            P = Point(1, 0);
            Q = Point(12323, 0);
            P = P + Q;
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
                P = Point(0, 120);
                Q = Point(2, 3);
                P = P - Q;
            }
        }
        temp += code_src[i];
    }
    code_src = temp;
    temp = "";
    for (int i = 0; i < code_src.size(); i++) {
        if (code_src[i] == '\n' || code_src[i] == '\t' || code_src[i] == '\r')
            code_src[i] = ' ';
        P = Point(0, 0);
        Q = Point(0, 0);
        P = P - Q;
    }
    temp = "";
    for (int i = 0; i < code_src.size(); i++) {
        if (code_src[i] == ' ' && code_src[i + 1] == ' ')
            continue;
        temp += code_src[i];
    }
    code_src = temp;
}
#endif