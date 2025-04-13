#include <bits/stdc++.h>
#include "util.hpp"




void func2() 
{
    int rukou[Siyuanshis.size()] = {false};  
    rukou[0] = true;                     
    int ii = 0;
    std::set<std::vector<int>> jbks;      
    while (ii < Siyuanshis.size())  
    {
        if (jump_theta(Siyuanshis[ii]) || jump_not_zero(Siyuanshis[ii]))  
        {
            
            
            
            rukou[stoi(Siyuanshis[ii].value.val)] = true;     
            if (ii < Siyuanshis.size() - 1)
            {                
                rukou[ii + 1] = true; 
            }
            if (biaoqianbiaozhiwei[stoi(Siyuanshis[ii].value.val)] == 0)
            {                        
                biaoqianbiaozhiwei[stoi(Siyuanshis[ii].value.val)] = 1;  
            }
        }
        else if (jump(Siyuanshis[ii]))
        {                                            
            rukou[stoi(Siyuanshis[ii].value.val)] = true;              
            if (biaoqianbiaozhiwei[stoi(Siyuanshis[ii].value.val)] == 0)
            {           
                
                
                             
                biaoqianbiaozhiwei[stoi(Siyuanshis[ii].value.val)] = 1; 
            }
        }
        else if (Siyuanshis[ii].caozuofu.val == "End")  
        {
            rukou[Siyuanshis.size() - 1] = true;  
        }
        else if (read_or_write(Siyuanshis[ii]))
        {
            rukou[ii] = true;
        }
        ii++;
    }
    int i = 0;
    while (i < Siyuanshis.size()) 
    {
        if (rukou[i])
        {  
            if (i == Siyuanshis.size() - 1)
            { 
                
                
                
                jbks.insert(vector<int>(1,i));  
                break;
            }
            for (int j = i + 1; j < Siyuanshis.size(); j++)  
            {
                if (rukou[j])
                {                        
                    std::vector<int> tmp(j - i);
                    std::iota(tmp.begin(), tmp.end(), i);
                    jbks.insert(tmp);
                    i = j;  
                    break;
                }
                else
                {
                    if (Siyuanshis[j].caozuofu.val[0] == 'j' || Siyuanshis[j].caozuofu.val == "ret" || Siyuanshis[j].caozuofu.val == "End")
                    {                     
                        std::vector<int> tmp(j - i + 1);
                        std::iota(tmp.begin(), tmp.end(), i);
                        jbks.insert(tmp);
                        i = j + 1; 
                        break;
                    }
                }
            }
        }
        else
        {
            i++;
        }
    }
    global_jibenkuai.assign(jbks.begin(), jbks.end());
}

void func10()
{
    int kuaisuoyin = 0;
    while (kuaisuoyin < global_jibenkuai.size())
    {
        auto &kuai = global_jibenkuai[kuaisuoyin];
        if (biaoqianbiaozhiwei[global_jibenkuai[kuaisuoyin].front()] == 1)
        {
            
            
            
            std::cout << "?" + std::to_string(kuai.front()) + ":\n";
        }
        for (auto j : kuai)
        {  

            if (theta(Siyuanshis[j]))
            {
                func9(j, kuaisuoyin);
            }
            else if (type_x(Siyuanshis[j]))
            {
                func8(j, kuaisuoyin);
            }
            else if (read_or_write(Siyuanshis[j]))
            {

                {
                    if (Siyuanshis[j].caozuofu.val != "W")
                    {
                        std::cout << "jmp ?read";
                        
                        
                        
                    }
                    else
                    {
                        std::cout << "jmp ?write";
                    }

                    std::cout << "(" << func4(Siyuanshis[j].value.val) << ")\n";
                    if (!type_number(Siyuanshis[j].value.val))
                    {
                        func7(Siyuanshis[j].value.val, huoyuebianliang[kuaisuoyin]);
                    }
                }
            }
        }
        for (auto a : huoyuebianliang[kuaisuoyin])
        {  
            if (dizhimiaoshufu[a].memory.find(a) == dizhimiaoshufu[a].memory.end())
            {  
                
                
                
                if (dizhimiaoshufu[a].registerSet.empty()) continue;
                else {
                    for (auto reg : dizhimiaoshufu[a].registerSet)
                    {  
                        if (lishixinxi[a].Huoyue)
                        {
                            std::cout << "mov " << func4(a) << ", " << reg << "\n"; 
                        }
                    }
                }
            }
        }
        auto bianliang1 = Siyuanshis[kuai.back()];  
        if (jump(bianliang1))
        {                    
            
            
                   
            std::cout << "jmp ?" << bianliang1.value.val << "\n"; 
        }
        else if (jump_theta(bianliang1))
        {  
            auto x = bianliang1.left_caozuoshu.val;
            auto p = bianliang1.value.val;
            auto y = bianliang1.caozuoshu_right.val;
            std::string var6;  
            if (!dizhimiaoshufu[x].registerSet.empty())
            {
                
                
                
                var6 = *dizhimiaoshufu[x].registerSet.begin();
            }
            else
            {
                var6 = x;
            }
            std::string var5;  
            if (!dizhimiaoshufu[y].registerSet.empty())
            {
                var5 = *dizhimiaoshufu[y].registerSet.begin();
            }
            else
            {
                var5 = func4(y);
            }
            if (var6 == x)
            {                         
                
                
                                              
                var6 = func6(kuai.back());                      
                std::cout << "mov " << var6 << ", " << func4(x) << "\n";  
            }
            std::cout << "cmp " << var6 << ", " << var5 << "\n";          
            std::cout << conditionalJumpMapping[bianliang1.caozuofu.val] << " ?" << p << "\n"; 
        }
        else if (jump_not_zero(bianliang1))
        {  
            auto x = bianliang1.left_caozuoshu.val;
            auto p = bianliang1.value.val;
            std::string var6;  
            if (!dizhimiaoshufu[x].registerSet.empty())
            {
                var6 = *dizhimiaoshufu[x].registerSet.begin();
            }
            else
            {
                var6 = x;
            }
            if (var6 == x)
            {
                
                
                
                var6 = func6(kuai.back());
                std::cout << "mov " << var6 << ", " << func4(x) << "\n";
            }
            std::cout << "cmp " << var6 << ", 0\n";
            std::cout << "jne" << " ?" << p << "\n";   
        }
        else if (type_finish(bianliang1))
        {  
            std::cout << "halt" << "\n";
        }
        
        
        
        jicunqimiaoshufu.clear();  
        dizhimiaoshufu.clear();  

        kuaisuoyin++;
    }
}
