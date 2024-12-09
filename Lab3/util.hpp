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

std::function<bool(const Siyuanshi &)> jump_not_zero = [](const Siyuanshi &item) -> bool{  
    if(item.caozuofu.val == "jnz") return true;
    else return false;
};

std::function<bool(const Siyuanshi &)> read_or_write = [] (const Siyuanshi &item) { 
    if (item.caozuofu.val == "W" || item.caozuofu.val == "R") return true;
    else return false;
};

std::function<bool(const Siyuanshi &)> type_x = [] (const Siyuanshi &item) { 
    if ((item.caozuofu.val == "=" || item.caozuofu.val == "!") && item.caozuoshu_right.val == "-") return true;
    else return false;
};

std::function<bool(const Siyuanshi &)> type_finish = [] (const Siyuanshi &item) {   
    if (item.caozuofu.val == "End") return true;
    else return false;
};

std::function<bool(const std::string &)> type_number = [](const std::string &item){    
    return item[0]>='0' && item[0] <= '9';
};


int func1(int var1)
{
    int i = 0;
    while (i < global_jibenkuai.size())
    {
        if (find(global_jibenkuai[i].begin(), global_jibenkuai[i].end(), var1) != global_jibenkuai[i].end())
        {
            return i;
            break;
        }
        i++;
    }
    return -1;
}

std::set<std::string> func3(std::vector<int> &kuai) 
{
    std::set<std::string> var1;  
    for (auto &i : kuai)
    {                                              
        std::string y = Siyuanshis[i].caozuoshu_right.val;
        std::string z = Siyuanshis[i].value.val;
        std::string x = Siyuanshis[i].left_caozuoshu.val;  
        if (x[0] == 'T')
        {
            huhaobiao[x].shiyongbiaozhi = -1;
            if (!huhaobiao[x].zhongjian)
            {                                 
                huhaobiao[x].Huoyue = true; 
                if (find(var1.begin(), var1.end(), x) == var1.end())
                {  
                    var1.insert(x);
                }
            }
        }
        if (y[0] == 'T')
        {
            huhaobiao[y].shiyongbiaozhi = -1;
            if (!huhaobiao[y].zhongjian)
            {
                huhaobiao[y].Huoyue = true;
                if (find(var1.begin(), var1.end(), y) == var1.end())
                {
                    var1.insert(y);
                }
            }
        }
        if (z[0] == 'T')
        {
            huhaobiao[z].shiyongbiaozhi = -1;
            if (!huhaobiao[z].zhongjian)
            {
                huhaobiao[z].Huoyue = true;
                if (find(var1.begin(), var1.end(), z) == var1.end())
                {
                    var1.insert(z);
                }
            }
        }
    }
    for (int i = kuai.size() - 1; i >= 0; i--)
    { // for i=m…1
        int var3 = kuai[i];
        if (Siyuanshis[var3].value.val[0] == 'T')
        {
            Siyuanshis[var3].value.shiyong = huhaobiao[Siyuanshis[var3].value.val].shiyongbiaozhi;  
            Siyuanshis[var3].value.Huoyue = huhaobiao[Siyuanshis[var3].value.val].Huoyue;
            huhaobiao[Siyuanshis[var3].value.val].Huoyue = false;  
            huhaobiao[Siyuanshis[var3].value.val].shiyongbiaozhi = -1;
        }
        if (Siyuanshis[var3].left_caozuoshu.val[0] == 'T')
        {
            Siyuanshis[var3].left_caozuoshu.shiyong = huhaobiao[Siyuanshis[var3].left_caozuoshu.val].shiyongbiaozhi; 
            Siyuanshis[var3].left_caozuoshu.Huoyue = huhaobiao[Siyuanshis[var3].left_caozuoshu.val].Huoyue;
            huhaobiao[Siyuanshis[var3].left_caozuoshu.val].Huoyue = true;  
            huhaobiao[Siyuanshis[var3].left_caozuoshu.val].shiyongbiaozhi = var3;
        }
        if (Siyuanshis[var3].caozuoshu_right.val[0] == 'T')
        {
            Siyuanshis[var3].caozuoshu_right.shiyong = huhaobiao[Siyuanshis[var3].caozuoshu_right.val].shiyongbiaozhi;   
            Siyuanshis[var3].caozuoshu_right.Huoyue = huhaobiao[Siyuanshis[var3].caozuoshu_right.val].Huoyue;
            huhaobiao[Siyuanshis[var3].caozuoshu_right.val].Huoyue = true;  
            huhaobiao[Siyuanshis[var3].caozuoshu_right.val].shiyongbiaozhi = var3;
        }
    }
    return var1;  
}
std::string func4(std::string var)  
{
    if (var[0] == '[')
    {
        return var;
    }
    if (huhaobiao.find(var) != huhaobiao.end() && huhaobiao[var].deltaPianYiLiang != -1)
    {
        return "[ebp-" + std::to_string(huhaobiao[var].deltaPianYiLiang) + "]";  
    }
    if (var.back() == 'i')
    {                                                          
        huhaobiao[var].deltaPianYiLiang = deltaPianYiLiang + 4;  
        deltaPianYiLiang += 4;                           
    }
    else if (var.back() == 'd')
    {                        
        huhaobiao[var].deltaPianYiLiang = deltaPianYiLiang + 8;
        deltaPianYiLiang += 8;  
    }
    return "[ebp-" + std::to_string(huhaobiao[var].deltaPianYiLiang) + "]";  
}
std::string func5(std::vector<std::string> &var2, int var3)  
{
    std::string var1;
    int maxshiyongbiaozhi = INT32_MIN; 
    int kuaisuoyin = func1(var3);  
    for (auto &jicunqi : var2)
    {                        
        bool faxianle = false; 
        for (int i = var3 + 1; i <= global_jibenkuai[kuaisuoyin].back(); i++)
        {  
            if (jicunqimiaoshufu[jicunqi].find(Siyuanshis[i].left_caozuoshu.val) != jicunqimiaoshufu[jicunqi].end())
            {  
                faxianle = true;
                if (i > maxshiyongbiaozhi)
                {
                    maxshiyongbiaozhi = i;
                    var1 = jicunqi;
                }
                break;
            }
            else if (jicunqimiaoshufu[jicunqi].find(Siyuanshis[i].caozuoshu_right.val) != jicunqimiaoshufu[jicunqi].end())
            {
                faxianle = true;
                if (i > maxshiyongbiaozhi)
                {
                    maxshiyongbiaozhi = i;
                    var1 = jicunqi;
                }
                break;
            }
        }
        if (!faxianle)
        {            
            var1 = jicunqi;  
            break;
        }
    }
    return var1;
}

std::string func6(int var3) 
{
    Siyuanshi siyuanshi = Siyuanshis[var3];       
    std::string z = siyuanshi.value.val;           
    std::string x = siyuanshi.left_caozuoshu.val; 
    std::string y = siyuanshi.caozuoshu_right.val; 
    if (!type_number(x) && x != "-")
    {  
        for (auto &jicunqi : dizhimiaoshufu[x].registerSet)
        { 
            if (jicunqimiaoshufu[jicunqi] == std::set<std::string>{x} && (x == z || !siyuanshi.left_caozuoshu.Huoyue))
            {  
                return jicunqi;
            }
        }
    }
    for (auto &jicunqi : Jicunqi)
    {  
        if (jicunqimiaoshufu[jicunqi].empty())
        {          
            return jicunqi;  
        }
    }
    std::vector<std::string> var8;
    for (auto &jicunqi : Jicunqi)
    { 
        if (!jicunqimiaoshufu[jicunqi].empty())
        { 
            var8.push_back(jicunqi);
        }
    }
    if (var8.empty())
    {  
        var8 = Jicunqi;
    }
    std::string jicunqi;
    bool faxianle = true;
    for (auto & var9 : var8)
    { 
        faxianle = true;
        for (auto &a : jicunqimiaoshufu[var9])
        {  
            if (dizhimiaoshufu[a].memory.find(a) == dizhimiaoshufu[a].memory.end())
            {
                faxianle = false;
                break;
            }
        }
        if (faxianle)
        {  
            jicunqi = var9;
            break;
        }
    }
    if (!faxianle)
    {
        jicunqi = func5(var8, var3);  
    }
    for (auto &a : jicunqimiaoshufu[jicunqi])
    {  
        if (dizhimiaoshufu[a].memory.find(a) == dizhimiaoshufu[a].memory.end() && a != z)
        {                                                          
            std::cout << "mov " << func4(a) << ", " << jicunqi << "\n";  
        }
        if (a == x || (a == y && jicunqimiaoshufu[jicunqi].find(x) != jicunqimiaoshufu[jicunqi].end()))
        {                        
            dizhimiaoshufu[a].memory = {a}; 
            dizhimiaoshufu[a].registerSet = {jicunqi};
        }
        else
        { 
            dizhimiaoshufu[a].memory = {a};
            dizhimiaoshufu[a].registerSet = {};
        }
    }
    jicunqimiaoshufu[jicunqi].clear(); 
    return jicunqi;
}
void func7(std::string var, std::set<std::string> &huoyuebianliang)
{  
    if (huoyuebianliang.find(var) == huoyuebianliang.end())
    {  
        for (auto &reg : dizhimiaoshufu[var].registerSet)
        {                  
            jicunqimiaoshufu[reg].erase(var); 
        }
        dizhimiaoshufu[var].registerSet.clear();  
    }
}
void func8(int var3, int kuaisuoyin)
{
    Siyuanshi q = Siyuanshis[var3];
    auto x = q.left_caozuoshu.val;
    auto z = q.value.val;
    auto R = func6(var3);
    std::string var6;
    if (type_number(x))
    {
        var6 = x;  
        std::cout << "mov " << R << ", " << var6 << "\n";
    }
    else
    { 
        if (jicunqimiaoshufu[R].find(x) == jicunqimiaoshufu[R].end())
        { 
            if (!dizhimiaoshufu[x].registerSet.empty())
            {                                    
                var6 = *dizhimiaoshufu[x].registerSet.begin();  
            }
            else
            {
                var6 = func4(x);  
            }
            std::cout << "mov " << R << ", " << var6 << "\n";  
        }
        if (q.caozuofu.val != "=")
        {
            std::cout << operationMapping[q.caozuofu.val] << " " << R << "\n";  
        }
        if (!type_number(x))
        {
            func7(x, huoyuebianliang[kuaisuoyin]);  
        }
    }
    jicunqimiaoshufu[R].insert(z);             
    lishixinxi[z] = q.value;       
    dizhimiaoshufu[z].registerSet.insert(R);  
    dizhimiaoshufu[z].memory.clear();    
}

void func9(int var3, int kuaisuoyin)
{  
    Siyuanshi siyuanshi = Siyuanshis[var3];
    auto x = siyuanshi.left_caozuoshu.val;
    auto y = siyuanshi.caozuoshu_right.val;
    auto z = siyuanshi.value.val;
    auto var4 = func6(var3); 
    std::string var6;
    if (x != "-" && !type_number(x))
    { 
        if (!dizhimiaoshufu[x].registerSet.empty())
        {
            var6 = *dizhimiaoshufu[x].registerSet.begin();
        }
        else
        {
            var6 = func4(x);
        }
    }
    else
    {
        var6 = x;
    }
    std::string var5;
    if (y != "-" && !type_number(y))
    { 
        if (!dizhimiaoshufu[y].registerSet.empty())
        {
            var5 = *dizhimiaoshufu[y].registerSet.begin();
        }
        else
        {
            var5 = func4(y);
        }
    }
    else
    {
        var5 = y;
    }
    if (var6 == var4)
    {                                           
        std::cout << operationMapping[siyuanshi.caozuofu.val] << " " << var4 << ", " << var5 << "\n";  
        if (operationMapping[siyuanshi.caozuofu.val] == "cmp")
        {                                                                   
            std::cout << comparisonInstructionMapping[siyuanshi.caozuofu.val] << " " << var4 << "\n"; 
        }
        dizhimiaoshufu[x].registerSet.erase(var4); 
    }
    else
    {
        std::cout << "mov " << var4 << ", " << var6 << "\n"; 
        std::cout << operationMapping[siyuanshi.caozuofu.val] << " " << var4 << ", " << var5 << "\n";
        if (operationMapping[siyuanshi.caozuofu.val] == "cmp")
        {
            std::cout << comparisonInstructionMapping[siyuanshi.caozuofu.val] << " " << var4 << "\n";
        }
    }
    if (var5 == var4)
    { // if y' = var4
        if (!type_number(y))
        {
            dizhimiaoshufu[y].registerSet.erase(var4);  
        }
    }
    jicunqimiaoshufu[var4] = {z}; 
    lishixinxi[z] = siyuanshi.value;
    dizhimiaoshufu[z].registerSet = {var4};
    dizhimiaoshufu[z].memory.clear();
    if (!type_number(x))
    {
        func7(x, huoyuebianliang[kuaisuoyin]); 
    }
    if (!type_number(y))
    {
        func7(y, huoyuebianliang[kuaisuoyin]);  
    }
}
#endif
