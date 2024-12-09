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
            {                         // if !biaoqianbiaozhiwei[quad.block] then
                biaoqianbiaozhiwei[stoi(Siyuanshis[ii].value.val)] = 1; // biaoqianbiaozhiwei[quad.block]=true；
            }
        }
        else if (jump(Siyuanshis[ii]))
        {                                              // else if qi形如(j,-,-,qj)
            rukou[stoi(Siyuanshis[ii].value.val)] = true;                     // 标记qj为基本块的入口
            if (biaoqianbiaozhiwei[stoi(Siyuanshis[ii].value.val)] == 0)
            {                         // if !biaoqianbiaozhiwei[quad.block] then
                biaoqianbiaozhiwei[stoi(Siyuanshis[ii].value.val)] = 1; // biaoqianbiaozhiwei[quad.block]=true；
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

std::set<std::string> func3(std::vector<int> &block) // 求解待用信息
{
    std::set<std::string> var1; // 当前块出口处的活跃变量集合
    for (auto &i : block)
    {                                                     // shiyongbiaozhi在构造时已经是非待用
        std::string x = Siyuanshis[i].left_caozuoshu.val; // 对于左右操作数和左值
        std::string y = Siyuanshis[i].caozuoshu_right.val;
        std::string z = Siyuanshis[i].value.val;
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
    for (int i = block.size() - 1; i >= 0; i--)
    { // for i=m…1
        int index = block[i];
        if (Siyuanshis[index].value.val[0] == 'T')
        {
            Siyuanshis[index].value.shiyong = huhaobiao[Siyuanshis[index].value.val].shiyongbiaozhi; // 符号表中变量z的shiyongbiaozhi和Huoyue赋值给四元式qi的z变量；
            Siyuanshis[index].value.Huoyue = huhaobiao[Siyuanshis[index].value.val].Huoyue;
            huhaobiao[Siyuanshis[index].value.val].Huoyue = false; // 符号表中变量z的shiyongbiaozhi和Huoyue分别置为-和N；
            huhaobiao[Siyuanshis[index].value.val].shiyongbiaozhi = -1;
        }
        if (Siyuanshis[index].left_caozuoshu.val[0] == 'T')
        {
            Siyuanshis[index].left_caozuoshu.shiyong = huhaobiao[Siyuanshis[index].left_caozuoshu.val].shiyongbiaozhi; // 符号表中变量x的shiyongbiaozhi和Huoyue赋值给四元式qi的x变量
            Siyuanshis[index].left_caozuoshu.Huoyue = huhaobiao[Siyuanshis[index].left_caozuoshu.val].Huoyue;
            huhaobiao[Siyuanshis[index].left_caozuoshu.val].Huoyue = true; // 符号表中变量x的shiyongbiaozhi和Huoyue分别置为qi和Y
            huhaobiao[Siyuanshis[index].left_caozuoshu.val].shiyongbiaozhi = index;
        }
        if (Siyuanshis[index].caozuoshu_right.val[0] == 'T')
        {
            Siyuanshis[index].caozuoshu_right.shiyong = huhaobiao[Siyuanshis[index].caozuoshu_right.val].shiyongbiaozhi; // 符号表中变量y的shiyongbiaozhi和Huoyue赋值给四元式qi的y变量
            Siyuanshis[index].caozuoshu_right.Huoyue = huhaobiao[Siyuanshis[index].caozuoshu_right.val].Huoyue;
            huhaobiao[Siyuanshis[index].caozuoshu_right.val].Huoyue = true; // 符号表中变量y的shiyongbiaozhi和Huoyue分别置为qi和Y
            huhaobiao[Siyuanshis[index].caozuoshu_right.val].shiyongbiaozhi = index;
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
        deltaPianYiLiang += 4;                                // 偏移量加4
        huhaobiao[var].deltaPianYiLiang = deltaPianYiLiang; // 更新变量的偏移量
    }
    else if (var.back() == 'd')
    {                          // 如果变量是double型临时变量
        deltaPianYiLiang += 8; // 偏移量加8
        huhaobiao[var].deltaPianYiLiang = deltaPianYiLiang;
    }
    return "[ebp-" + std::to_string(huhaobiao[var].deltaPianYiLiang) + "]"; // 返回变量的地址
}

std::string func5(std::vector<std::string> &allR, int index) // 用于Ri = （Rj∈RA）argmax（a∈jicunqimiaoshufu（Rj））min a.shiyongbiaozhi；
{
    std::string var1;
    int maxshiyongbiaozhi = INT32_MIN; // maxshiyongbiaozhi=-∞
    int blockIndex = func1(index); // blockIndex=FindBlockIndex（q）；
    for (auto &Ri : allR)
    {                          // for each Ri∈RA
        bool hasFound = false; // Ri中的变量是否在后续的四元式中使用
        for (int i = index + 1; i <= global_jibenkuai[blockIndex].back(); i++)
        { // 遍历四元式
            if (jicunqimiaoshufu[Ri].find(Siyuanshis[i].left_caozuoshu.val) != jicunqimiaoshufu[Ri].end())
            { // 同理
                hasFound = true;
                if (i > maxshiyongbiaozhi)
                {
                    maxshiyongbiaozhi = i;
                    var1 = Ri;
                }
                break;
            }
            else if (jicunqimiaoshufu[Ri].find(Siyuanshis[i].caozuoshu_right.val) != jicunqimiaoshufu[Ri].end())
            {
                hasFound = true;
                if (i > maxshiyongbiaozhi)
                {
                    maxshiyongbiaozhi = i;
                    var1 = Ri;
                }
                break;
            }
        }
        if (!hasFound)
        {             // 如果Ri中的变量在后续的四元式中没有使用
            var1 = Ri; // 返回Ri
            break;
        }
    }
    return var1;
}

std::string func6(int index) // 局部寄存器分配的伪代码
{
    Siyuanshi q = Siyuanshis[index];       // 四元式q
    std::string z = q.value.val;           // 左值z
    std::string x = q.left_caozuoshu.val;  // 左操作数x
    std::string y = q.caozuoshu_right.val; // 右操作数y
    if (!type_number(x) && x != "-")
    { // 如果x是变量
        for (auto &Ri : dizhimiaoshufu[x].registerSet)
        { // if 存在Ri∈dizhimiaoshufu（x）
            if (jicunqimiaoshufu[Ri] == std::set<std::string>{x} && (x == z || !q.left_caozuoshu.Huoyue))
            { // 并且jicunqimiaoshufu（Ri）={x}并且（x=z或者x.Huoyue=N）
                return Ri;
            }
        }
    }
    for (auto &Ri : jicunqi)
    { // if 存在Ri
        if (jicunqimiaoshufu[Ri].empty())
        {              // 使得jicunqimiaoshufu（Ri）为空
            return Ri; // return Ri；
        }
    }
    std::vector<std::string> RA;
    for (auto &Ri : jicunqi)
    { // RA={Ri|Ri∈R
        if (!jicunqimiaoshufu[Ri].empty())
        { // 并且jicunqimiaoshufu（Ri）中包含主存单元}；
            RA.push_back(Ri);
        }
    }
    if (RA.empty())
    { // if RA为空then RA=R；
        RA = jicunqi;
    }
    std::string Ri;
    bool hasFound = true;
    for (auto &Rj : RA)
    { // if 存在Rj∈RA
        hasFound = true;
        for (auto &a : jicunqimiaoshufu[Rj])
        { // 并且任意a∈jicunqimiaoshufu（Rj）都有a∈dizhimiaoshufu（a）
            if (dizhimiaoshufu[a].memory.find(a) == dizhimiaoshufu[a].memory.end())
            {
                hasFound = false;
                break;
            }
        }
        if (hasFound)
        { // Ri=Rj
            Ri = Rj;
            break;
        }
    }
    if (!hasFound)
    {
        Ri = func5(RA, index); // Ri = （Rj∈RA）argmax（a∈jicunqimiaoshufu（Rj））min a.shiyongbiaozhi；
    }
    for (auto &a : jicunqimiaoshufu[Ri])
    { // foreach a∈jicunqimiaoshufu（Ri）do
        if (dizhimiaoshufu[a].memory.find(a) == dizhimiaoshufu[a].memory.end() && a != z)
        {                                                               // if a不属于dizhimiaoshufu（a）并且a≠z
            std::cout << "mov " << func4(a) << ", " << Ri << "\n"; // 生成代码：mov a，Ri；
        }
        if (a == x || (a == y && jicunqimiaoshufu[Ri].find(x) != jicunqimiaoshufu[Ri].end()))
        {                         // if a = x或者（a=y并且x∈jicunqimiaoshufu（Ri））
            dizhimiaoshufu[a].memory = {a}; // dizhimiaoshufu（a）={a，Ri}；
            dizhimiaoshufu[a].registerSet = {Ri};
        }
        else
        { // else dizhimiaoshufu（a）= {a}；
            dizhimiaoshufu[a].memory = {a};
            dizhimiaoshufu[a].registerSet = {};
        }
    }
    jicunqimiaoshufu[Ri].clear(); // jicunqimiaoshufu（Ri）= jicunqimiaoshufu（Ri）- {a}；
    return Ri;
}

void releaseReg(std::string var, std::set<std::string> &huoyuebianliang)
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

void genForOnlyX(int index, int blockIndex)
{
    Siyuanshi q = Siyuanshis[index];
    auto x = q.left_caozuoshu.val;
    auto z = q.value.val;
    auto R = func6(index);
    std::string x1;
    if (type_number(x))
    {
        x1 = x; // x是数字，x1=x；
        std::cout << "mov " << R << ", " << x1 << "\n";
    }
    else
    { // x是变量
        if (jicunqimiaoshufu[R].find(x) == jicunqimiaoshufu[R].end())
        { // if x∉jicunqimiaoshufu（R）
            if (!dizhimiaoshufu[x].registerSet.empty())
            {                                      // if dizhimiaoshufu（x）≠∅
                x1 = *dizhimiaoshufu[x].registerSet.begin(); // x1=dizhimiaoshufu（x）中的寄存器；
            }
            else
            {
                x1 = func4(x); // x1=地址（x）；
            }
            std::cout << "mov " << R << ", " << x1 << "\n"; // 生成代码：mov R，x1；
        }
        if (q.caozuofu.val != "=")
        {
            std::cout << operationMapping[q.caozuofu.val] << " " << R << "\n"; // 生成代码：θ R；
        }
        if (!type_number(x))
        {
            releaseReg(x, huoyuebianliang[blockIndex]); // releaseReg（x，Bi）；
        }
    }
    jicunqimiaoshufu[R].insert(z);             // jicunqimiaoshufu（R）+={z}；
    lishixinxi[z] = q.value;      // lishixinxi（R）=q.left；
    dizhimiaoshufu[z].registerSet.insert(R); // dizhimiaoshufu（z）+={R}；
    dizhimiaoshufu[z].memory.clear();        // dizhimiaoshufu（z）-={z}；
}

void genForTheta(int index, int blockIndex)
{ // if qij形如（θ，x，y，z）then
    Siyuanshi q = Siyuanshis[index];
    auto x = q.left_caozuoshu.val;
    auto y = q.caozuoshu_right.val;
    auto z = q.value.val;
    auto Rz = func6(index); // Rz=getReg（qij）；
    std::string x1;
    if (x != "-" && !type_number(x))
    { // x' = 存在Rx∈dizhimiaoshufu（x）？Rx：x；
        if (!dizhimiaoshufu[x].registerSet.empty())
        {
            x1 = *dizhimiaoshufu[x].registerSet.begin();
        }
        else
        {
            x1 = func4(x);
        }
    }
    else
    {
        x1 = x;
    }
    std::string y1;
    if (y != "-" && !type_number(y))
    { // y' = 存在Ry∈dizhimiaoshufu（y）？Ry：y；
        if (!dizhimiaoshufu[y].registerSet.empty())
        {
            y1 = *dizhimiaoshufu[y].registerSet.begin();
        }
        else
        {
            y1 = func4(y);
        }
    }
    else
    {
        y1 = y;
    }
    if (x1 == Rz)
    {                                                                                     // if x' = Rz then
        std::cout << operationMapping[q.caozuofu.val] << " " << Rz << ", " << y1 << "\n"; // 生成代码：θ Rz，y'
        if (operationMapping[q.caozuofu.val] == "cmp")
        {                                                                                   // if θ = cmp then
            std::cout << comparisonInstructionMapping[q.caozuofu.val] << " " << Rz << "\n"; // 生成代码：cmp Rz
        }
        dizhimiaoshufu[x].registerSet.erase(Rz); // dizhimiaoshufu（x）-={Rz}；
    }
    else
    {
        std::cout << "mov " << Rz << ", " << x1 << "\n"; // 生成代码：mov Rz，x'；和θ Rz，y'；
        std::cout << operationMapping[q.caozuofu.val] << " " << Rz << ", " << y1 << "\n";
        if (operationMapping[q.caozuofu.val] == "cmp")
        {
            std::cout << comparisonInstructionMapping[q.caozuofu.val] << " " << Rz << "\n";
        }
    }
    if (y1 == Rz)
    { // if y' = Rz
        if (!type_number(y))
        {
            dizhimiaoshufu[y].registerSet.erase(Rz); // then dizhimiaoshufu（y）-={Rz}；
        }
    }
    jicunqimiaoshufu[Rz] = {z}; // jicunqimiaoshufu（Rz） = {z}，dizhimiaoshufu（z）={Rz}；
    lishixinxi[z] = q.value;
    dizhimiaoshufu[z].registerSet = {Rz};
    dizhimiaoshufu[z].memory.clear();
    if (!type_number(x))
    {
        releaseReg(x, huoyuebianliang[blockIndex]); // releaseReg（x，Bi）
    }
    if (!type_number(y))
    {
        releaseReg(y, huoyuebianliang[blockIndex]); // releaseReg（y，Bi）；
    }
}

void clearSymbolTable()
{ // 清空符号表，这是后来加的
    deltaPianYiLiang = InitdeltaPianYiLiang;
    for (auto &a : huhaobiao)
    {
        if (a.second.zhongjian)
        {
            a.second.shiyongbiaozhi = -1;
            a.second.Huoyue = false;
            a.second.deltaPianYiLiang = -1;
        }
    }
}

void func10()
{
    int blockIndex = 0;
    while (blockIndex < global_jibenkuai.size())
    {
        auto &block = global_jibenkuai[blockIndex];
        if (biaoqianbiaozhiwei[global_jibenkuai[blockIndex].front()] == 1)
        {
            std::cout << "?" + std::to_string(block.front()) + ":\n";
        }
        for (auto j : block)
        { // 为每个四元式生成代码

            if (theta(Siyuanshis[j]))
            {
                genForTheta(j, blockIndex);
            }
            else if (type_x(Siyuanshis[j]))
            {
                genForOnlyX(j, blockIndex);
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
                        releaseReg(Siyuanshis[j].value.val, huoyuebianliang[blockIndex]);
                    }
                }
            }
        }
        for (auto a : huoyuebianliang[blockIndex])
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
        auto bianliang1 = Siyuanshis[block.back()]; // bianliang1
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
            std::string x1; // x' = 存在Rx∈dizhimiaoshufu（x）？Rx：x；
            if (!dizhimiaoshufu[x].registerSet.empty())
            {
                x1 = *dizhimiaoshufu[x].registerSet.begin();
            }
            else
            {
                x1 = x;
            }
            std::string y1; // y' = 存在Ry∈dizhimiaoshufu（y）？Ry：y；
            if (!dizhimiaoshufu[y].registerSet.empty())
            {
                y1 = *dizhimiaoshufu[y].registerSet.begin();
            }
            else
            {
                y1 = func4(y);
            }
            if (x1 == x)
            {                                                               // if x' = x then
                x1 = func6(block.back());                                  // x' = getReg（bianliang1）；
                std::cout << "mov " << x1 << ", " << func4(x) << "\n"; // 生成代码：mov x'，x；
            }
            std::cout << "cmp " << x1 << ", " << y1 << "\n";                             // 生成代码：cmp x'，y'；
            std::cout << conditionalJumpMapping[bianliang1.caozuofu.val] << " ?" << q << "\n"; // 生成代码：jθ ?q；
            // genLable(stoi(q),biaoqianbiaozhiwei); //genLabel（q，biaoqianbiaozhiwei）；
        }
        else if (jump_not_zero(bianliang1))
        { // else if bianliang1形如（jnz，x，-，q）then
            auto x = bianliang1.left_caozuoshu.val;
            auto q = bianliang1.value.val;
            std::string x1; // x' = 存在Rx∈dizhimiaoshufu（x）？Rx：x；
            if (!dizhimiaoshufu[x].registerSet.empty())
            {
                x1 = *dizhimiaoshufu[x].registerSet.begin();
            }
            else
            {
                x1 = x;
            }
            if (x1 == x)
            {
                x1 = func6(block.back());
                std::cout << "mov " << x1 << ", " << func4(x) << "\n";
            }
            std::cout << "cmp " << x1 << ", 0\n";
            std::cout << "jne" << " ?" << q << "\n";    // 生成代码：jne ?q；
        }
        else if (type_finish(bianliang1))
        { // else if bianliang1形如（End，-，-，-）then
            std::cout << "halt" << "\n";
        }
        jicunqimiaoshufu.clear(); // 所有寄存器描述符置空
        dizhimiaoshufu.clear(); // 所有变量的地址描述符置空

        blockIndex++;
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