#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <utility>
#include "util.hpp"

std::string get_token() {
    state = STATE1;
    std::string token;
    while (pos < code_src.size() && code_src[pos] == ' ') pos++;
    while (pos < code_src.size()) {
        if (state == STATE1) {
            if (isalpha(code_src[pos])) {
                token += code_src[pos];
                state = STATE2;
                
            } else if (isdigit(code_src[pos]) || code_src[pos] == '.') {
                token += code_src[pos];
                state = STATE3;
            } else if (std::string("=><!").find(code_src[pos]) != std::string::npos) {
                token += code_src[pos++];
                if (code_src[pos] == '=') {
                    token += code_src[pos++];
                }
                return token;
            } else if (std::string("&|").find(code_src[pos]) != std::string::npos) {
                token += code_src[pos];
                pos++;
                if (code_src[pos] == code_src[pos - 1]) {
                    token += code_src[pos++];
                }
                return token;
            } else if (std::string("{};(),+-*/").find(code_src[pos]) != std::string::npos) {
                token += code_src[pos];
                pos++;
                return token;
            } else {
                std::cout << "Unrecognizable characters.";
                exit(0);
            }
            pos++;
        } else if (state == STATE2) {
            if (std::isalpha(code_src[pos]) || std::isdigit(code_src[pos])) {
                token += code_src[pos];
            }else return token;
            pos++;
        } else if (state == STATE3) {
            if (std::isdigit(code_src[pos]) || code_src[pos] == '.') {
                token += code_src[pos];
            }
            else return token;
        }
    }
    return token;
}

void parser_token(std::string &token) {
    std::pair<std::string, std::string> temp;
    temp.first = token;
    if (mp1.find(token) != mp1.end()) {
        
        temp.second = mp1.at(token);
    } else if (mp2.find(token) != mp2.end()) {
        
        temp.second = mp2.at(token);
    } else if (std::isalpha(token[0])) {
        
        temp.second = "IDENT";
    } else if (std::isdigit(token[0]) || token[0] == '.') {
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
        bool flag = false;
        for (int i = 0; i < token.size(); i++) {
            if (token[i] == '.') {
                if (flag) {
                    std::cout << "Malformed number: More than one decimal point in a floating point number.";
                    exit(0);
                }
                flag = true;
            } else if (!std::isdigit(token[i])) {
                std::cout << "Malformed number: Non-digit character in a number.";
                exit(0);
            }
        }
        if (flag) temp.second = "DOUBLE";
        else temp.second = "INT";
    }
    ans.push_back(temp);
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);
    
    std::string line;
    code_src.clear();
    while (std::getline(std::cin, line)) {
        code_src += line + "\n";
        line.clear();
    }
    
    init();
    
    while (true) {
        std::string token = get_token();
        if (token == "") break;
        parser_token(token);
    }
    for (const auto& [fi, se] : ans) {
        std::cout << fi << " " << se << std::endl;
    }
    return 0;
}