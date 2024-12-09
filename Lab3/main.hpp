#ifndef MAIN_HPP
#define MAIN_HPP
#include <iostream>
#include <set>
using namespace std;
struct Siyuanshixiang{ //每个四元式中的项目
    std::string val;        //该项目的值
    int flag_usage = -1;      //该项目的待用信息
    bool active = false; //该项目的活跃信息
    Siyuanshixiang(std::string val):val(val){}
    Siyuanshixiang(){}
};

struct Siyuanshi {      //四元式
    Siyuanshixiang caozuofu;   //操作符
    Siyuanshixiang left_caozuoshu;//左操作数
    Siyuanshixiang caozuoshu_right;//右操作数
    Siyuanshixiang value; //左值
    Siyuanshi(Siyuanshixiang caozuofu,Siyuanshixiang left_caozuoshu,Siyuanshixiang caozuoshu_right,Siyuanshixiang value):caozuofu(caozuofu),left_caozuoshu(left_caozuoshu),caozuoshu_right(caozuoshu_right),value(value){}
    Siyuanshi(){}
};



struct Fuhaobiaoxiang {    //符号表中的项目
    std::string name="", type="", value="";        //变量值
    int deltaPianYiLiang = -1;          //变量的偏移量
    int flag_usage = -1;           //变量的待用信息
    bool isTemp = true;     //是否是临时变量
    bool active = false;      //变量的活跃信息
    Fuhaobiaoxiang(){}
    Fuhaobiaoxiang(bool isTemp):isTemp(isTemp){}
};


struct some_struct {                                      // Aval中的项目
    std::set<std::string> registerSet; // 寄存器集合
    std::set<std::string> memory;
};


#endif