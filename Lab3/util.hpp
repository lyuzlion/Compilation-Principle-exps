#ifndef uitl_HPP
#define util_HPP
#include <bits/stdc++.h>
#include "main.hpp"
#include "var.hpp"
using namespace std;

std::function<bool(const Siyuanshi &)> theta = [](const Siyuanshi & item) -> bool{
    if(item.caozuoshu_right.val == "-") return false;
    if(item.caozuofu.val[0]=='+') return true;
    if(item.caozuofu.val[0]=='-') return true;
    if(item.caozuofu.val[0]=='*') return true;
    if(item.caozuofu.val[0]=='/') return true;
    if(item.caozuofu.val[0]=='=') return true;
    if(item.caozuofu.val[0]=='<') return true;
    if(item.caozuofu.val[0]=='>') return true;
    if(item.caozuofu.val[0]=='!') return true;
    if(item.caozuofu.val[0]=='&') return true;
    if(item.caozuofu.val[0]=='|') return true;
    return false;
};

std::function<bool(const Siyuanshi &)> jump_theta = [](const Siyuanshi & item) -> bool{
    if(item.caozuofu.val[0]!='j') return false;
    if(item.caozuofu.val == "j") return false;
    if(item.caozuofu.val == "jnz") return false;
    return true;
};

std::function<bool(const Siyuanshi &)> jump = [](const Siyuanshi & item) -> bool {
    if(item.caozuofu.val == "j") return true;
    else return false;
};

std::function<bool(const Siyuanshi &)> jump_not_zero = [](const Siyuanshi &item) -> bool{  //判断是否是Jnz类型的四元式，要求操作符为"jnz"
    if(item.caozuofu.val == "jnz") return true;
    else return false;
};

std::function<bool(const Siyuanshi &)> read_or_write = [] (const Siyuanshi &item) {  //判断是否是Read或Write类型的四元式，要求操作符为"W"或"R"
    if (item.caozuofu.val == "W" || item.caozuofu.val == "R") return true;
    else return false;
};

std::function<bool(const Siyuanshi &)> type_x = [] (const Siyuanshi &item) { //判断是否是只有左操作数的四元式，要求操作符为"="或"!"，并且右操作数为"-"
    if ((item.caozuofu.val == "=" || item.caozuofu.val == "!") && item.caozuoshu_right.val == "-") return true;
    else return false;
};

std::function<bool(const Siyuanshi &)> type_finish = [] (const Siyuanshi &item) {  //判断是否是End类型的四元式，要求操作符为"End"
    if (item.caozuofu.val == "End") return true;
    else return false;
};

std::function<bool(const std::string &)> type_number = [](const std::string &item){    //判断是否是数字，即UINT或UFLOAT
    return item[0]>='0' && item[0] <= '9';
};

#endif
