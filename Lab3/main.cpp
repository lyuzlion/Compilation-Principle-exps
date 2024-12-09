#include <bits/stdc++.h>
#include "util.hpp"





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


void func2() // 获取基本块
{
    int rukou[Siyuanshis.size()] = {false};   // 标记每个四元式是否是基本块的入口
    rukou[0] = true;                          // 标记qi为入口语句
    int ii = 0;
    std::set<std::vector<int>> jbks;          // 基本块集合
    while (ii < Siyuanshis.size()) // 逆序遍历四元式
    {
        if (jump_theta(Siyuanshis[ii]) || jump_not_zero(Siyuanshis[ii])) // if qi 形如 (jTheta,-,-,qj)或(jnz,-,-,qj)
        {
            rukou[stoi(Siyuanshis[ii].value.val)] = true;                     // 标记qj为基本块的入口
            if (ii < Siyuanshis.size() - 1)
            {                          // if i<n
                rukou[ii + 1] = true; // 标记qi+1为基本块的入口
            }
            if (biaoqianbiaozhiwei[stoi(Siyuanshis[ii].value.val)] == 0)
            {                         // if !biaoqianbiaozhiwei[quad.kuai] then
                biaoqianbiaozhiwei[stoi(Siyuanshis[ii].value.val)] = 1; // biaoqianbiaozhiwei[quad.kuai]=true；
            }
        }
        else if (jump(Siyuanshis[ii]))
        {                                              // else if qi形如(j,-,-,qj)
            rukou[stoi(Siyuanshis[ii].value.val)] = true;                     // 标记qj为基本块的入口
            if (biaoqianbiaozhiwei[stoi(Siyuanshis[ii].value.val)] == 0)
            {                         // if !biaoqianbiaozhiwei[quad.kuai] then
                biaoqianbiaozhiwei[stoi(Siyuanshis[ii].value.val)] = 1; // biaoqianbiaozhiwei[quad.kuai]=true；
            }
        }
        else if (Siyuanshis[ii].caozuofu.val == "End") // if qi形如(End,-,-,-)
        {
            rukou[Siyuanshis.size() - 1] = true; // 标记qn为基本块的入口
        }
        else if (read_or_write(Siyuanshis[ii]))
        {
            rukou[ii] = true;
        }
        ii++;
    }
    int i = 0;
    while (i < Siyuanshis.size()) // 顺序遍历四元式
    {
        if (rukou[i])
        { // if qi是基本块的入口
            if (i == Siyuanshis.size() - 1)
            { // if i=n
                jbks.insert(vector<int>(1,i)); // 将qi加入基本块
                break;
            }
            for (int j = i + 1; j < Siyuanshis.size(); j++) // 遍历qi之后的四元式
            {
                if (rukou[j])
                {                          // if qj是基本块的入口
                    std::vector<int> tmp(j - i);
                    std::iota(tmp.begin(), tmp.end(), i);
                    jbks.insert(tmp);
                    i = j; // i=j
                    break;
                }
                else
                {
                    if (Siyuanshis[j].caozuofu.val[0] == 'j' || Siyuanshis[j].caozuofu.val == "ret" || Siyuanshis[j].caozuofu.val == "End")
                    {                          // if qj是停机或转移语句
                        std::vector<int> tmp(j - i + 1);
                        std::iota(tmp.begin(), tmp.end(), i);
                        jbks.insert(tmp);
                        i = j + 1; // i=j+1
                        break;
                    }
                }
            }
        }
        else
        {
            i++; // i++
        }
    }
    global_jibenkuai.assign(jbks.begin(), jbks.end()); // 将基本块集合转换为基本块数组
}

std::set<std::string> func3(std::vector<int> &kuai) // 求解待用信息
{
    std::set<std::string> var1; // 当前块出口处的活跃变量集合
    for (auto &i : kuai)
    {                                                     // shiyongbiaozhi在构造时已经是非待用
        std::string y = Siyuanshis[i].caozuoshu_right.val;
        std::string z = Siyuanshis[i].value.val;
        std::string x = Siyuanshis[i].left_caozuoshu.val; // 对于左右操作数和左值
        if (x[0] == 'T')
        {
            huhaobiao[x].shiyongbiaozhi = -1;
            if (!huhaobiao[x].zhongjian)
            {                                 // 如果x不是临时变量
                huhaobiao[x].Huoyue = true; // x是活跃的
                if (find(var1.begin(), var1.end(), x) == var1.end())
                { // 将x加入当前块出口处的活跃变量集合
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
            Siyuanshis[var3].value.shiyong = huhaobiao[Siyuanshis[var3].value.val].shiyongbiaozhi; // 符号表中变量z的shiyongbiaozhi和Huoyue赋值给四元式qi的z变量；
            Siyuanshis[var3].value.Huoyue = huhaobiao[Siyuanshis[var3].value.val].Huoyue;
            huhaobiao[Siyuanshis[var3].value.val].Huoyue = false; // 符号表中变量z的shiyongbiaozhi和Huoyue分别置为-和N；
            huhaobiao[Siyuanshis[var3].value.val].shiyongbiaozhi = -1;
        }
        if (Siyuanshis[var3].left_caozuoshu.val[0] == 'T')
        {
            Siyuanshis[var3].left_caozuoshu.shiyong = huhaobiao[Siyuanshis[var3].left_caozuoshu.val].shiyongbiaozhi; // 符号表中变量x的shiyongbiaozhi和Huoyue赋值给四元式qi的x变量
            Siyuanshis[var3].left_caozuoshu.Huoyue = huhaobiao[Siyuanshis[var3].left_caozuoshu.val].Huoyue;
            huhaobiao[Siyuanshis[var3].left_caozuoshu.val].Huoyue = true; // 符号表中变量x的shiyongbiaozhi和Huoyue分别置为qi和Y
            huhaobiao[Siyuanshis[var3].left_caozuoshu.val].shiyongbiaozhi = var3;
        }
        if (Siyuanshis[var3].caozuoshu_right.val[0] == 'T')
        {
            Siyuanshis[var3].caozuoshu_right.shiyong = huhaobiao[Siyuanshis[var3].caozuoshu_right.val].shiyongbiaozhi; // 符号表中变量y的shiyongbiaozhi和Huoyue赋值给四元式qi的y变量
            Siyuanshis[var3].caozuoshu_right.Huoyue = huhaobiao[Siyuanshis[var3].caozuoshu_right.val].Huoyue;
            huhaobiao[Siyuanshis[var3].caozuoshu_right.val].Huoyue = true; // 符号表中变量y的shiyongbiaozhi和Huoyue分别置为qi和Y
            huhaobiao[Siyuanshis[var3].caozuoshu_right.val].shiyongbiaozhi = var3;
        }
    }
    return var1; // 返回当前块出口处的活跃变量集合
}

std::string func4(std::string var) // 获取变量的地址
{
    if (var[0] == '[')
    {
        return var;
    }
    if (huhaobiao.find(var) != huhaobiao.end() && huhaobiao[var].deltaPianYiLiang != -1)
    {
        return "[ebp-" + std::to_string(huhaobiao[var].deltaPianYiLiang) + "]"; // 如果变量在内存中，返回变量的地址
    }
    if (var.back() == 'i')
    {                                                         // 如果变量是整型临时变量
        huhaobiao[var].deltaPianYiLiang = deltaPianYiLiang + 4; // 更新变量的偏移量
        deltaPianYiLiang += 4;                                // 偏移量加4
    }
    else if (var.back() == 'd')
    {                          // 如果变量是double型临时变量
        huhaobiao[var].deltaPianYiLiang = deltaPianYiLiang + 8;
        deltaPianYiLiang += 8; // 偏移量加8
    }
    return "[ebp-" + std::to_string(huhaobiao[var].deltaPianYiLiang) + "]"; // 返回变量的地址
}

std::string func5(std::vector<std::string> &var2, int var3) // 用于jicunqi = （Rj∈RA）argmax（a∈jicunqimiaoshufu（Rj））min a.shiyongbiaozhi；
{
    std::string var1;
    int maxshiyongbiaozhi = INT32_MIN; // maxshiyongbiaozhi=-∞
    int kuaisuoyin = func1(var3); // kuaisuoyin=FindBlockIndex（q）；
    for (auto &jicunqi : var2)
    {                          // for each jicunqi∈RA
        bool faxianle = false; // jicunqi中的变量是否在后续的四元式中使用
        for (int i = var3 + 1; i <= global_jibenkuai[kuaisuoyin].back(); i++)
        { // 遍历四元式
            if (jicunqimiaoshufu[jicunqi].find(Siyuanshis[i].left_caozuoshu.val) != jicunqimiaoshufu[jicunqi].end())
            { // 同理
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
        {             // 如果jicunqi中的变量在后续的四元式中没有使用
            var1 = jicunqi; // 返回jicunqi
            break;
        }
    }
    return var1;
}

std::string func6(int var3) // 局部寄存器分配的伪代码
{
    Siyuanshi siyuanshi = Siyuanshis[var3];       // 四元式q
    std::string z = siyuanshi.value.val;           // 左值z
    std::string x = siyuanshi.left_caozuoshu.val;  // 左操作数x
    std::string y = siyuanshi.caozuoshu_right.val; // 右操作数y
    if (!type_number(x) && x != "-")
    { // 如果x是变量
        for (auto &jicunqi : dizhimiaoshufu[x].registerSet)
        { // if 存在jicunqi∈dizhimiaoshufu（x）
            if (jicunqimiaoshufu[jicunqi] == std::set<std::string>{x} && (x == z || !siyuanshi.left_caozuoshu.Huoyue))
            { // 并且jicunqimiaoshufu（jicunqi）={x}并且（x=z或者x.Huoyue=N）
                return jicunqi;
            }
        }
    }
    for (auto &jicunqi : jicunqi)
    { // if 存在jicunqi
        if (jicunqimiaoshufu[jicunqi].empty())
        {              // 使得jicunqimiaoshufu（jicunqi）为空
            return jicunqi; // return jicunqi；
        }
    }
    std::vector<std::string> RA;
    for (auto &jicunqi : jicunqi)
    { // RA={jicunqi|jicunqi∈R
        if (!jicunqimiaoshufu[jicunqi].empty())
        { // 并且jicunqimiaoshufu（jicunqi）中包含主存单元}；
            RA.push_back(jicunqi);
        }
    }
    if (RA.empty())
    { // if RA为空then RA=R；
        RA = jicunqi;
    }
    std::string jicunqi;
    bool faxianle = true;
    for (auto &Rj : RA)
    { // if 存在Rj∈RA
        faxianle = true;
        for (auto &a : jicunqimiaoshufu[Rj])
        { // 并且任意a∈jicunqimiaoshufu（Rj）都有a∈dizhimiaoshufu（a）
            if (dizhimiaoshufu[a].memory.find(a) == dizhimiaoshufu[a].memory.end())
            {
                faxianle = false;
                break;
            }
        }
        if (faxianle)
        { // jicunqi=Rj
            jicunqi = Rj;
            break;
        }
    }
    if (!faxianle)
    {
        jicunqi = func5(RA, var3); // jicunqi = （Rj∈RA）argmax（a∈jicunqimiaoshufu（Rj））min a.shiyongbiaozhi；
    }
    for (auto &a : jicunqimiaoshufu[jicunqi])
    { // foreach a∈jicunqimiaoshufu（jicunqi）do
        if (dizhimiaoshufu[a].memory.find(a) == dizhimiaoshufu[a].memory.end() && a != z)
        {                                                               // if a不属于dizhimiaoshufu（a）并且a≠z
            std::cout << "mov " << func4(a) << ", " << jicunqi << "\n"; // 生成代码：mov a，jicunqi；
        }
        if (a == x || (a == y && jicunqimiaoshufu[jicunqi].find(x) != jicunqimiaoshufu[jicunqi].end()))
        {                         // if a = x或者（a=y并且x∈jicunqimiaoshufu（jicunqi））
            dizhimiaoshufu[a].memory = {a}; // dizhimiaoshufu（a）={a，jicunqi}；
            dizhimiaoshufu[a].registerSet = {jicunqi};
        }
        else
        { // else dizhimiaoshufu（a）= {a}；
            dizhimiaoshufu[a].memory = {a};
            dizhimiaoshufu[a].registerSet = {};
        }
    }
    jicunqimiaoshufu[jicunqi].clear(); // jicunqimiaoshufu（jicunqi）= jicunqimiaoshufu（jicunqi）- {a}；
    return jicunqi;
}

void func7(std::string var, std::set<std::string> &huoyuebianliang)
{ // 释放寄存器
    if (huoyuebianliang.find(var) == huoyuebianliang.end())
    { // if var 不属于 huoyuebianliang（Bi）
        for (auto &reg : dizhimiaoshufu[var].registerSet)
        {                         // 并且存在reg∈dizhimiaoshufu（var）
            jicunqimiaoshufu[reg].erase(var); // jicunqimiaoshufu（reg）-={var}；
        }
        dizhimiaoshufu[var].registerSet.clear(); // dizhimiaoshufu（var）-={reg}；
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
        var6 = x; // x是数字，var6=x；
        std::cout << "mov " << R << ", " << var6 << "\n";
    }
    else
    { // x是变量
        if (jicunqimiaoshufu[R].find(x) == jicunqimiaoshufu[R].end())
        { // if x∉jicunqimiaoshufu（R）
            if (!dizhimiaoshufu[x].registerSet.empty())
            {                                      // if dizhimiaoshufu（x）≠∅
                var6 = *dizhimiaoshufu[x].registerSet.begin(); // var6=dizhimiaoshufu（x）中的寄存器；
            }
            else
            {
                var6 = func4(x); // var6=地址（x）；
            }
            std::cout << "mov " << R << ", " << var6 << "\n"; // 生成代码：mov R，var6；
        }
        if (q.caozuofu.val != "=")
        {
            std::cout << operationMapping[q.caozuofu.val] << " " << R << "\n"; // 生成代码：θ R；
        }
        if (!type_number(x))
        {
            func7(x, huoyuebianliang[kuaisuoyin]); // func7（x，Bi）；
        }
    }
    jicunqimiaoshufu[R].insert(z);             // jicunqimiaoshufu（R）+={z}；
    lishixinxi[z] = q.value;      // lishixinxi（R）=q.left；
    dizhimiaoshufu[z].registerSet.insert(R); // dizhimiaoshufu（z）+={R}；
    dizhimiaoshufu[z].memory.clear();        // dizhimiaoshufu（z）-={z}；
}

void func9(int var3, int kuaisuoyin)
{ // if qij形如（θ，x，y，z）then
    Siyuanshi siyuanshi = Siyuanshis[var3];
    auto x = siyuanshi.left_caozuoshu.val;
    auto y = siyuanshi.caozuoshu_right.val;
    auto z = siyuanshi.value.val;
    auto var4 = func6(var3); // var4=getReg（qij）；
    std::string var6;
    if (x != "-" && !type_number(x))
    { // x' = 存在Rx∈dizhimiaoshufu（x）？Rx：x；
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
    { // y' = 存在Ry∈dizhimiaoshufu（y）？Ry：y；
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
    {                                                                                     // if x' = var4 then
        std::cout << operationMapping[siyuanshi.caozuofu.val] << " " << var4 << ", " << var5 << "\n"; // 生成代码：θ var4，y'
        if (operationMapping[siyuanshi.caozuofu.val] == "cmp")
        {                                                                                   // if θ = cmp then
            std::cout << comparisonInstructionMapping[siyuanshi.caozuofu.val] << " " << var4 << "\n"; // 生成代码：cmp var4
        }
        dizhimiaoshufu[x].registerSet.erase(var4); // dizhimiaoshufu（x）-={var4}；
    }
    else
    {
        std::cout << "mov " << var4 << ", " << var6 << "\n"; // 生成代码：mov var4，x'；和θ var4，y'；
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
            dizhimiaoshufu[y].registerSet.erase(var4); // then dizhimiaoshufu（y）-={var4}；
        }
    }
    jicunqimiaoshufu[var4] = {z}; // jicunqimiaoshufu（var4） = {z}，dizhimiaoshufu（z）={var4}；
    lishixinxi[z] = siyuanshi.value;
    dizhimiaoshufu[z].registerSet = {var4};
    dizhimiaoshufu[z].memory.clear();
    if (!type_number(x))
    {
        func7(x, huoyuebianliang[kuaisuoyin]); // func7（x，Bi）
    }
    if (!type_number(y))
    {
        func7(y, huoyuebianliang[kuaisuoyin]); // func7（y，Bi）；
    }
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
        { // 为每个四元式生成代码

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
        { // foreach a∈huoyuebianliang（Bi）
            if (dizhimiaoshufu[a].memory.find(a) == dizhimiaoshufu[a].memory.end())
            { // 并且a不属于dizhimiaoshufu（a）do
                if (!dizhimiaoshufu[a].registerSet.empty())
                {
                    for (auto reg : dizhimiaoshufu[a].registerSet)
                    { // Ra=dizhimiaoshufu（a）中的寄存器；
                        if (lishixinxi[a].Huoyue)
                        {
                            std::cout << "mov " << func4(a) << ", " << reg << "\n"; // 生成代码：mov a，Ra；
                        }
                    }
                }
            }
        }
        auto bianliang1 = Siyuanshis[kuai.back()]; // bianliang1
        if (jump(bianliang1))
        {                                                   // if bianliang1形如（j，-，-，q）then
            std::cout << "jmp ?" << bianliang1.value.val << "\n"; // 生成代码：jmp ?q；
            // genLable(stoi(bianliang1.left.val),biaoqianbiaozhiwei); //genLabel（q，biaoqianbiaozhiwei）；
        }
        else if (jump_theta(bianliang1))
        { // else if bianliang1形如（jθ，x，y，q）then
            auto x = bianliang1.left_caozuoshu.val;
            auto y = bianliang1.caozuoshu_right.val;
            auto q = bianliang1.value.val;
            std::string var6; // x' = 存在Rx∈dizhimiaoshufu（x）？Rx：x；
            if (!dizhimiaoshufu[x].registerSet.empty())
            {
                var6 = *dizhimiaoshufu[x].registerSet.begin();
            }
            else
            {
                var6 = x;
            }
            std::string var5; // y' = 存在Ry∈dizhimiaoshufu（y）？Ry：y；
            if (!dizhimiaoshufu[y].registerSet.empty())
            {
                var5 = *dizhimiaoshufu[y].registerSet.begin();
            }
            else
            {
                var5 = func4(y);
            }
            if (var6 == x)
            {                                                               // if x' = x then
                var6 = func6(kuai.back());                                  // x' = getReg（bianliang1）；
                std::cout << "mov " << var6 << ", " << func4(x) << "\n"; // 生成代码：mov x'，x；
            }
            std::cout << "cmp " << var6 << ", " << var5 << "\n";                             // 生成代码：cmp x'，y'；
            std::cout << conditionalJumpMapping[bianliang1.caozuofu.val] << " ?" << q << "\n"; // 生成代码：jθ ?q；
            // genLable(stoi(q),biaoqianbiaozhiwei); //genLabel（q，biaoqianbiaozhiwei）；
        }
        else if (jump_not_zero(bianliang1))
        { // else if bianliang1形如（jnz，x，-，q）then
            auto x = bianliang1.left_caozuoshu.val;
            auto q = bianliang1.value.val;
            std::string var6; // x' = 存在Rx∈dizhimiaoshufu（x）？Rx：x；
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
            std::cout << "jne" << " ?" << q << "\n";    // 生成代码：jne ?q；
        }
        else if (type_finish(bianliang1))
        { // else if bianliang1形如（End，-，-，-）then
            std::cout << "halt" << "\n";
        }
        jicunqimiaoshufu.clear(); // 所有寄存器描述符置空
        dizhimiaoshufu.clear(); // 所有变量的地址描述符置空

        kuaisuoyin++;
    }
}

int main()
{
    jicunqi.push_back("R0");
    jicunqi.push_back("R1");
    jicunqi.push_back("R2");
    
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    std::string line;
    std::getline(std::cin, line);

    if (line == "Syntax Error")
    {
        std::cout << "halt\n";
        return 0;
    }

    int sz1, sz2;
    sz1 = stoi(line);

    line = "";

    int i = 0;
    while (i < sz1)
    {
        std::getline(std::cin, line);
        std::stringstream ss(line);
        Fuhaobiaoxiang temp(false);
        ss >> temp.name >> temp.type >> temp.value >> temp.deltaPianYiLiang;
        InitdeltaPianYiLiang = std::max(InitdeltaPianYiLiang, temp.deltaPianYiLiang); // 更新符号表中变量的初始偏移量
        huhaobiao["TB" + std::to_string(i)] = temp;                                 // 将该项目加入符号表
        i++;
    }

    std::getline(std::cin, line);

    std::getline(std::cin, line);
    sz2 = stoi(line);

    Siyuanshis.resize(sz2);
    line = "";

    i = 0;
    while (i < sz2)
    {
        std::getline(std::cin, line);
        line = line.substr(line.find(':') + 2);
        line = line.substr(1, line.find(')') - 1);
        std::stringstream ss(line);
        std::vector<std::string> tokens(4);
        int j = 0;
        while (std::getline(ss, tokens[j], ','))
        {
            j++;
        }
        Siyuanshis[i].caozuofu = tokens[0];
        Siyuanshis[i].left_caozuoshu = tokens[1];
        Siyuanshis[i].caozuoshu_right = tokens[2];
        Siyuanshis[i].value = tokens[3];
        i++;
    }

    deltaPianYiLiang = InitdeltaPianYiLiang; // 初始化当前符号表的偏移量

    biaoqianbiaozhiwei.resize(Siyuanshis.size(), 0);

    func2();

    huoyuebianliang.resize(global_jibenkuai.size());

    i = 0;
    while (i < global_jibenkuai.size())
    {
        huoyuebianliang[i] = func3(global_jibenkuai[i]);
        i++;
    }

    func10();
    return 0;
}