#ifndef MAIN_HPP
#define MAIN_HPP
#include <iostream>
#include <set>
using namespace std;
struct Siyuanshixiang{
    std::string val;     
    int shiyong = -1;     
    bool Huoyue = false; 
    Siyuanshixiang(std::string val):val(val){}
    Siyuanshixiang(){}
};

struct Siyuanshi {   
    Siyuanshixiang caozuofu;  
    Siyuanshixiang left_caozuoshu;
    Siyuanshixiang caozuoshu_right;
    Siyuanshixiang value; 
    Siyuanshi(Siyuanshixiang caozuofu,Siyuanshixiang left_caozuoshu,Siyuanshixiang caozuoshu_right,Siyuanshixiang value):caozuofu(caozuofu),left_caozuoshu(left_caozuoshu),caozuoshu_right(caozuoshu_right),value(value){}
    Siyuanshi(){}
};


std::vector<std::vector<int>> global_jibenkuai;    
std::vector<std::set<std::string>> huoyuebianliang;       
std::map<std::string, Siyuanshixiang> lishixinxi;  
int InitdeltaPianYiLiang = 0;     

struct Fuhaobiaoxiang {
    std::string name="", type="", value="";   
    int deltaPianYiLiang = -1;       
    int shiyongbiaozhi = -1;       
    bool zhongjian = true;    
    bool Huoyue = false;    
    Fuhaobiaoxiang(){}
    Fuhaobiaoxiang(bool zhongjian):zhongjian(zhongjian){}
};

std::map<std::string, Fuhaobiaoxiang> huhaobiao;  
std::map<std::string, std::set<std::string>> jicunqimiaoshufu; 
int deltaPianYiLiang = 0;     

struct some_struct {                        
    std::set<std::string> registerSet; 
    std::set<std::string> memory;
};

std::vector<std::string> Jicunqi;  
std::vector<Siyuanshi> Siyuanshis;  
std::map<std::string, some_struct> dizhimiaoshufu; 
std::vector<int> biaoqianbiaozhiwei;

#endif