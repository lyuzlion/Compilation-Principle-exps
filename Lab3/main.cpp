#include <bits/stdc++.h>
#include "util.hpp"



int InitdeltaPianYiLiang = 0;                             // 符号表中变量的初始偏移量
int deltaPianYiLiang = 0;                                 // 当前符号表的偏移量
std::vector<Siyuanshi> Siyuanshis;                        // 四元式序列
std::map<std::string, Fuhaobiaoxiang> huhaobiao;        // 符号表
std::vector<std::vector<int>> global_jibenkuai;                // 基本块，blockBlocks[i]表示第i个基本块中的四元式下标形成的数组
int tempVarCount = 0;                                     // 临时变量的数量
std::map<std::string, some_struct> dizhimiaoshufu;                  // 地址描述符
std::map<std::string, std::set<std::string>> jicunqimiaoshufu;        // 寄存器描述符
std::vector<std::string> jicunqi; // 寄存器集合
std::vector<std::set<std::string>> huoyuebianliang;             // 每个基本块的活跃变量集合
std::map<std::string, Siyuanshixiang> lishixinxi;        // 历史信息
std::vector<int> labelFlag;

int func1(int index)
{
    int i = 0;
    while (i < global_jibenkuai.size())
    {
        if (find(global_jibenkuai[i].begin(), global_jibenkuai[i].end(), index) != global_jibenkuai[i].end())
        {
            return i;
            break;
        }
        i++;
    }
    return -1;
}


void getBasicBlock() // 获取基本块
{
    std::set<std::vector<int>> blocks;          // 基本块集合
    int isEnter[Siyuanshis.size()] = {false};   // 标记每个四元式是否是基本块的入口
    isEnter[0] = true;                          // 标记qi为入口语句
    for (int i = 0; i < Siyuanshis.size(); i++) // 逆序遍历四元式
    {
        if (jump_theta(Siyuanshis[i]) || jump_not_zero(Siyuanshis[i])) // if qi 形如 (jTheta,-,-,qj)或(jnz,-,-,qj)
        {
            int index = stoi(Siyuanshis[i].value.val); // 取qj
            isEnter[index] = true;                     // 标记qj为基本块的入口
            if (i < Siyuanshis.size() - 1)
            {                          // if i<n
                isEnter[i + 1] = true; // 标记qi+1为基本块的入口
            }
            if (labelFlag[index] == 0)
            {                         // if !labelFlag[quad.block] then
                labelFlag[index] = 1; // labelFlag[quad.block]=true；
            }
        }
        else if (jump(Siyuanshis[i]))
        {                                              // else if qi形如(j,-,-,qj)
            int index = stoi(Siyuanshis[i].value.val); // 取qj
            isEnter[index] = true;                     // 标记qj为基本块的入口
            if (labelFlag[index] == 0)
            {                         // if !labelFlag[quad.block] then
                labelFlag[index] = 1; // labelFlag[quad.block]=true；
            }
        }
        else if (Siyuanshis[i].caozuofu.val == "End") // if qi形如(End,-,-,-)
        {
            isEnter[Siyuanshis.size() - 1] = true; // 标记qn为基本块的入口
        }
        else if (read_or_write(Siyuanshis[i]))
        {
            isEnter[i] = true;
        }
    }
    int i = 0;
    while (i < Siyuanshis.size()) // 顺序遍历四元式
    {
        if (isEnter[i])
        { // if qi是基本块的入口
            if (i == Siyuanshis.size() - 1)
            { // if i=n
                std::vector<int> temp;
                temp.push_back(i);
                blocks.insert(temp); // 将qi加入基本块
            }
            if (i + 1 == Siyuanshis.size())
            {
                break;
            }
            for (int j = i + 1; j < Siyuanshis.size(); j++) // 遍历qi之后的四元式
            {
                if (isEnter[j])
                {                          // if qj是基本块的入口
                    std::vector<int> temp; // qi,qi+1,...,qj-1加入基本块
                    for (int k = i; k < j; k++)
                    {
                        temp.push_back(k);
                    }
                    blocks.insert(temp);
                    i = j; // i=j
                    break;
                }
                else
                {
                    if (Siyuanshis[j].caozuofu.val[0] == 'j' || Siyuanshis[j].caozuofu.val == "ret" || Siyuanshis[j].caozuofu.val == "End")
                    {                          // if qj是停机或转移语句
                        std::vector<int> temp; // qi,qi+1,...,qj加入基本块
                        for (int k = i; k <= j; k++)
                        {
                            temp.push_back(k);
                        }
                        blocks.insert(temp);
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
    global_jibenkuai.assign(blocks.begin(), blocks.end()); // 将基本块集合转换为基本块数组
}

std::set<std::string> getflag_usageInfo(std::vector<int> &block) // 求解待用信息
{
    std::set<std::string> res; // 当前块出口处的活跃变量集合
    for (auto &i : block)
    {                                                     // flag_usage在构造时已经是非待用
        std::string x = Siyuanshis[i].left_caozuoshu.val; // 对于左右操作数和左值
        std::string y = Siyuanshis[i].caozuoshu_right.val;
        std::string z = Siyuanshis[i].value.val;
        if (x[0] == 'T')
        {
            huhaobiao[x].flag_usage = -1;
            if (!huhaobiao[x].isTemp)
            {                                 // 如果x不是临时变量
                huhaobiao[x].active = true; // x是活跃的
                if (find(res.begin(), res.end(), x) == res.end())
                { // 将x加入当前块出口处的活跃变量集合
                    res.insert(x);
                }
            }
        }
        if (y[0] == 'T')
        {
            huhaobiao[y].flag_usage = -1;
            if (!huhaobiao[y].isTemp)
            {
                huhaobiao[y].active = true;
                if (find(res.begin(), res.end(), y) == res.end())
                {
                    res.insert(y);
                }
            }
        }
        if (z[0] == 'T')
        {
            huhaobiao[z].flag_usage = -1;
            if (!huhaobiao[z].isTemp)
            {
                huhaobiao[z].active = true;
                if (find(res.begin(), res.end(), z) == res.end())
                {
                    res.insert(z);
                }
            }
        }
    }
    for (int i = block.size() - 1; i >= 0; i--)
    { // for i=m…1
        int index = block[i];
        if (Siyuanshis[index].value.val[0] == 'T')
        {
            Siyuanshis[index].value.flag_usage = huhaobiao[Siyuanshis[index].value.val].flag_usage; // 符号表中变量z的flag_usage和active赋值给四元式qi的z变量；
            Siyuanshis[index].value.active = huhaobiao[Siyuanshis[index].value.val].active;
            huhaobiao[Siyuanshis[index].value.val].active = false; // 符号表中变量z的flag_usage和active分别置为-和N；
            huhaobiao[Siyuanshis[index].value.val].flag_usage = -1;
        }
        if (Siyuanshis[index].left_caozuoshu.val[0] == 'T')
        {
            Siyuanshis[index].left_caozuoshu.flag_usage = huhaobiao[Siyuanshis[index].left_caozuoshu.val].flag_usage; // 符号表中变量x的flag_usage和active赋值给四元式qi的x变量
            Siyuanshis[index].left_caozuoshu.active = huhaobiao[Siyuanshis[index].left_caozuoshu.val].active;
            huhaobiao[Siyuanshis[index].left_caozuoshu.val].active = true; // 符号表中变量x的flag_usage和active分别置为qi和Y
            huhaobiao[Siyuanshis[index].left_caozuoshu.val].flag_usage = index;
        }
        if (Siyuanshis[index].caozuoshu_right.val[0] == 'T')
        {
            Siyuanshis[index].caozuoshu_right.flag_usage = huhaobiao[Siyuanshis[index].caozuoshu_right.val].flag_usage; // 符号表中变量y的flag_usage和active赋值给四元式qi的y变量
            Siyuanshis[index].caozuoshu_right.active = huhaobiao[Siyuanshis[index].caozuoshu_right.val].active;
            huhaobiao[Siyuanshis[index].caozuoshu_right.val].active = true; // 符号表中变量y的flag_usage和active分别置为qi和Y
            huhaobiao[Siyuanshis[index].caozuoshu_right.val].flag_usage = index;
        }
    }
    return res; // 返回当前块出口处的活跃变量集合
}

std::string getAddress(std::string var) // 获取变量的地址
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

std::string findR(std::vector<std::string> &allR, int index) // 用于Ri = （Rj∈RA）argmax（a∈jicunqimiaoshufu（Rj））min a.flag_usage；
{
    std::string res;
    int maxflag_usage = INT32_MIN; // maxflag_usage=-∞
    int blockIndex = func1(index); // blockIndex=FindBlockIndex（q）；
    for (auto &Ri : allR)
    {                          // for each Ri∈RA
        bool hasFound = false; // Ri中的变量是否在后续的四元式中使用
        for (int i = index + 1; i <= global_jibenkuai[blockIndex].back(); i++)
        { // 遍历四元式
            if (jicunqimiaoshufu[Ri].find(Siyuanshis[i].left_caozuoshu.val) != jicunqimiaoshufu[Ri].end())
            { // 同理
                hasFound = true;
                if (i > maxflag_usage)
                {
                    maxflag_usage = i;
                    res = Ri;
                }
                break;
            }
            else if (jicunqimiaoshufu[Ri].find(Siyuanshis[i].caozuoshu_right.val) != jicunqimiaoshufu[Ri].end())
            {
                hasFound = true;
                if (i > maxflag_usage)
                {
                    maxflag_usage = i;
                    res = Ri;
                }
                break;
            }
        }
        if (!hasFound)
        {             // 如果Ri中的变量在后续的四元式中没有使用
            res = Ri; // 返回Ri
            break;
        }
    }
    return res;
}

std::string getReg(int index) // 局部寄存器分配的伪代码
{
    Siyuanshi q = Siyuanshis[index];       // 四元式q
    std::string z = q.value.val;           // 左值z
    std::string x = q.left_caozuoshu.val;  // 左操作数x
    std::string y = q.caozuoshu_right.val; // 右操作数y
    if (!type_number(x) && x != "-")
    { // 如果x是变量
        for (auto &Ri : dizhimiaoshufu[x].registerSet)
        { // if 存在Ri∈dizhimiaoshufu（x）
            if (jicunqimiaoshufu[Ri] == std::set<std::string>{x} && (x == z || !q.left_caozuoshu.active))
            { // 并且jicunqimiaoshufu（Ri）={x}并且（x=z或者x.active=N）
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
        Ri = findR(RA, index); // Ri = （Rj∈RA）argmax（a∈jicunqimiaoshufu（Rj））min a.flag_usage；
    }
    for (auto &a : jicunqimiaoshufu[Ri])
    { // foreach a∈jicunqimiaoshufu（Ri）do
        if (dizhimiaoshufu[a].memory.find(a) == dizhimiaoshufu[a].memory.end() && a != z)
        {                                                               // if a不属于dizhimiaoshufu（a）并且a≠z
            std::cout << "mov " << getAddress(a) << ", " << Ri << "\n"; // 生成代码：mov a，Ri；
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
    auto R = getReg(index);
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
                x1 = getAddress(x); // x1=地址（x）；
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
    auto Rz = getReg(index); // Rz=getReg（qij）；
    std::string x1;
    if (x != "-" && !type_number(x))
    { // x' = 存在Rx∈dizhimiaoshufu（x）？Rx：x；
        if (!dizhimiaoshufu[x].registerSet.empty())
        {
            x1 = *dizhimiaoshufu[x].registerSet.begin();
        }
        else
        {
            x1 = getAddress(x);
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
            y1 = getAddress(y);
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
        if (a.second.isTemp)
        {
            a.second.flag_usage = -1;
            a.second.active = false;
            a.second.deltaPianYiLiang = -1;
        }
    }
}

void genCode()
{
    int blockIndex = 0;
    while (blockIndex < global_jibenkuai.size())
    {
        auto &block = global_jibenkuai[blockIndex];
        if (labelFlag[global_jibenkuai[blockIndex].front()] == 1)
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

                    std::cout << "(" << getAddress(Siyuanshis[j].value.val) << ")\n";
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
                        if (lishixinxi[a].active)
                        {
                            std::cout << "mov " << getAddress(a) << ", " << reg << "\n"; // 生成代码：mov a，Ra；
                        }
                    }
                }
            }
        }
        auto qini = Siyuanshis[block.back()]; // qini
        if (jump(qini))
        {                                                   // if qini形如（j，-，-，q）then
            std::cout << "jmp ?" << qini.value.val << "\n"; // 生成代码：jmp ?q；
            // genLable(stoi(qini.left.val),labelFlag); //genLabel（q，labelFlag）；
        }
        else if (jump_theta(qini))
        { // else if qini形如（jθ，x，y，q）then
            auto x = qini.left_caozuoshu.val;
            auto y = qini.caozuoshu_right.val;
            auto q = qini.value.val;
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
                y1 = getAddress(y);
            }
            if (x1 == x)
            {                                                               // if x' = x then
                x1 = getReg(block.back());                                  // x' = getReg（qini）；
                std::cout << "mov " << x1 << ", " << getAddress(x) << "\n"; // 生成代码：mov x'，x；
            }
            std::cout << "cmp " << x1 << ", " << y1 << "\n";                             // 生成代码：cmp x'，y'；
            std::cout << conditionalJumpMapping[qini.caozuofu.val] << " ?" << q << "\n"; // 生成代码：jθ ?q；
            // genLable(stoi(q),labelFlag); //genLabel（q，labelFlag）；
        }
        else if (jump_not_zero(qini))
        { // else if qini形如（jnz，x，-，q）then
            auto x = qini.left_caozuoshu.val;
            auto q = qini.value.val;
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
                x1 = getReg(block.back());
                std::cout << "mov " << x1 << ", " << getAddress(x) << "\n";
            }
            std::cout << "cmp " << x1 << ", 0" << "\n"; // 生成代码：cmp x'，0；
            std::cout << "jne" << " ?" << q << "\n";    // 生成代码：jne ?q；
        }
        else if (type_finish(qini))
        { // else if qini形如（End，-，-，-）then
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
    tempVarCount = stoi(line);

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

    labelFlag.resize(Siyuanshis.size(), 0);

    getBasicBlock();

    huoyuebianliang.resize(global_jibenkuai.size());

    i = 0;
    while (i < global_jibenkuai.size())
    {
        huoyuebianliang[i] = getflag_usageInfo(global_jibenkuai[i]);
        i++;
    }

    genCode();
    return 0;
}