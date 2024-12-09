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
            if (biaoqianbiaozhiwei[stoi(Siyuanshis[ii].value.val)] == 0)
            {    
                biaoqianbiaozhiwei[stoi(Siyuanshis[ii].value.val)] = 1; 
            }
            rukou[stoi(Siyuanshis[ii].value.val)] = true;                     // 标记qj为基本块的入口
            if (ii < Siyuanshis.size() - 1)
            {                          // if i<n
                rukou[ii + 1] = true; // 标记qi+1为基本块的入口
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
                    std::vector<int> temp; // qi,qi+1,...,qj-1加入基本块
                    for (int k = i; k < j; k++)
                    {
                        temp.push_back(k);
                    }
                    i = j;
                    jbks.insert(temp);
                    break;
                }
                else
                {
                    if (Siyuanshis[j].caozuofu.val[0] == 'j' || Siyuanshis[j].caozuofu.val == "ret" || Siyuanshis[j].caozuofu.val == "End")
                    {                          // if qj是停机或转移语句
                        std::vector<int> temp; // qi,qi+1,...,qj加入基本块
                        for (int asdk = i; asdk <= j; asdk++)
                        {
                            temp.push_back(asdk);
                        }
                        i = j + 1;
                        jbks.insert(temp);
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
    std::set<std::string> Huoyue; // 当前块出口处的活跃变量集合
    for (auto &i : block)
    {                                                     // shiyongbiaozhi在构造时已经是非待用
        std::string x = Siyuanshis[i].left_caozuoshu.val; // 对于左右操作数和左值
        std::string y = Siyuanshis[i].caozuoshu_right.val;
        std::string z = Siyuanshis[i].value.val;
        if (x[0] == 'T')
        {
            huhaobiao[x].shiyongbiaozhi = -1;
            if (!huhaobiao[x].linshi)
            {                                 // 如果x不是临时变量
                if (find(Huoyue.begin(), Huoyue.end(), x) == Huoyue.end())
                { // 将x加入当前块出口处的活跃变量集合
                    Huoyue.insert(x);
                }
                huhaobiao[x].huoyue = true; // x是活跃的
            }
        }
        if (y[0] == 'T')
        {
            huhaobiao[y].shiyongbiaozhi = -1;
            if (!huhaobiao[y].linshi)
            {
                if (find(Huoyue.begin(), Huoyue.end(), y) == Huoyue.end())
                {
                    Huoyue.insert(y);
                }
                huhaobiao[y].huoyue = true;
            }
        }
        if (z[0] == 'T')
        {
            huhaobiao[z].shiyongbiaozhi = -1;
            if (!huhaobiao[z].linshi)
            {
                if (find(Huoyue.begin(), Huoyue.end(), z) == Huoyue.end())
                {
                    Huoyue.insert(z);
                }
                huhaobiao[z].huoyue = true;
            }
        }
    }
    for (int i = block.size() - 1; i >= 0; i--)
    {
        if (Siyuanshis[block[i]].value.val[0] == 'T')
        {
            Siyuanshis[block[i]].value.shiyong = huhaobiao[Siyuanshis[block[i]].value.val].shiyongbiaozhi; // 符号表中变量z的shiyongbiaozhi和huoyue赋值给四元式qi的z变量；
            Siyuanshis[block[i]].value.huoyue = huhaobiao[Siyuanshis[block[i]].value.val].huoyue;
            huhaobiao[Siyuanshis[block[i]].value.val].huoyue = false; // 符号表中变量z的shiyongbiaozhi和huoyue分别置为-和N；
            huhaobiao[Siyuanshis[block[i]].value.val].shiyongbiaozhi = -1;
        }
        if (Siyuanshis[block[i]].left_caozuoshu.val[0] == 'T')
        {
            Siyuanshis[block[i]].left_caozuoshu.shiyong = huhaobiao[Siyuanshis[block[i]].left_caozuoshu.val].shiyongbiaozhi; // 符号表中变量x的shiyongbiaozhi和huoyue赋值给四元式qi的x变量
            Siyuanshis[block[i]].left_caozuoshu.huoyue = huhaobiao[Siyuanshis[block[i]].left_caozuoshu.val].huoyue;
            huhaobiao[Siyuanshis[block[i]].left_caozuoshu.val].huoyue = true; // 符号表中变量x的shiyongbiaozhi和huoyue分别置为qi和Y
            huhaobiao[Siyuanshis[block[i]].left_caozuoshu.val].shiyongbiaozhi = block[i];
        }
        if (Siyuanshis[block[i]].caozuoshu_right.val[0] == 'T')
        {
            Siyuanshis[block[i]].caozuoshu_right.shiyong = huhaobiao[Siyuanshis[block[i]].caozuoshu_right.val].shiyongbiaozhi; // 符号表中变量y的shiyongbiaozhi和huoyue赋值给四元式qi的y变量
            Siyuanshis[block[i]].caozuoshu_right.huoyue = huhaobiao[Siyuanshis[block[i]].caozuoshu_right.val].huoyue;
            huhaobiao[Siyuanshis[block[i]].caozuoshu_right.val].huoyue = true; // 符号表中变量y的shiyongbiaozhi和huoyue分别置为qi和Y
            huhaobiao[Siyuanshis[block[i]].caozuoshu_right.val].shiyongbiaozhi = block[i];
        }
    }
    return Huoyue; // 返回当前块出口处的活跃变量集合
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

std::string func5(std::vector<std::string> &var1, int id) // 用于jicunqi = （Rj∈RA）argmax（a∈jicunqimiaoshufu（Rj））min a.shiyongbiaozhi；
{
    std::string Huoyue;
    int maxshiyongbiaozhi = INT32_MIN; // maxshiyongbiaozhi=-∞
    int blkid = func1(id); // blkid=FindBlockIndex（q）；
    for (auto &jicunqi : var1)
    {                          // for each jicunqi∈RA
        bool flag1 = false; // jicunqi中的变量是否在后续的四元式中使用
        for (int i = id + 1; i <= global_jibenkuai[blkid].back(); i++)
        { // 遍历四元式
            if (jicunqimiaoshufu[jicunqi].find(Siyuanshis[i].left_caozuoshu.val) != jicunqimiaoshufu[jicunqi].end())
            { // 同理
                flag1 = true;
                if (i > maxshiyongbiaozhi)
                {
                    maxshiyongbiaozhi = i;
                    Huoyue = jicunqi;
                }
                break;
            }
            else if (jicunqimiaoshufu[jicunqi].find(Siyuanshis[i].caozuoshu_right.val) != jicunqimiaoshufu[jicunqi].end())
            {
                flag1 = true;
                if (i > maxshiyongbiaozhi)
                {
                    maxshiyongbiaozhi = i;
                    Huoyue = jicunqi;
                }
                break;
            }
        }
        if (!flag1)
        {             // 如果jicunqi中的变量在后续的四元式中没有使用
            Huoyue = jicunqi; // 返回jicunqi
            break;
        }
    }
    return Huoyue;
}

std::string func6(int index) // 局部寄存器分配的伪代码
{
    Siyuanshi q = Siyuanshis[index];       // 四元式q
    std::string z = q.value.val;           // 左值z
    std::string x = q.left_caozuoshu.val;  // 左操作数x
    std::string y = q.caozuoshu_right.val; // 右操作数y
    if (!type_number(x) && x != "-")
    { // 如果x是变量
        for (auto &jicunqi : dizhimiaoshufu[x].registerSet)
        { // if 存在jicunqi∈dizhimiaoshufu（x）
            if (jicunqimiaoshufu[jicunqi] == std::set<std::string>{x} && (x == z || !q.left_caozuoshu.huoyue))
            { // 并且jicunqimiaoshufu（jicunqi）={x}并且（x=z或者x.huoyue=N）
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
    bool flag1 = true;
    for (auto &Rj : RA)
    { // if 存在Rj∈RA
        flag1 = true;
        for (auto &a : jicunqimiaoshufu[Rj])
        { 
            if (dizhimiaoshufu[a].memory.find(a) == dizhimiaoshufu[a].memory.end())
            {
                flag1 = false;
                break;
            }
        }
        if (flag1)
        { // jicunqi=Rj
            jicunqi = Rj;
            break;
        }
    }
    if (!flag1)
    {
        jicunqi = func5(RA, index); // jicunqi = （Rj∈RA）argmax（a∈jicunqimiaoshufu（Rj））min a.shiyongbiaozhi；
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

void func8(int index, int blkid)
{
    Siyuanshi p = Siyuanshis[index];
    auto x = p.left_caozuoshu.val;
    auto z = p.value.val;
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
        if (p.caozuofu.val != "=")
        {
            std::cout << operationMapping[p.caozuofu.val] << " " << R << "\n"; // 生成代码：θ R；
        }
        if (!type_number(x))
        {
            func7(x, huoyuebianliang[blkid]); // func7（x，Bi）；
        }
    }
    jicunqimiaoshufu[R].insert(z);   
    lishixinxi[z] = p.value;   
    dizhimiaoshufu[z].registerSet.insert(R);
    dizhimiaoshufu[z].memory.clear();       
}

void func9(int index, int blkid)
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
        func7(x, huoyuebianliang[blkid]); // func7（x，Bi）
    }
    if (!type_number(y))
    {
        func7(y, huoyuebianliang[blkid]); // func7（y，Bi）；
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
        Fuhaobiaoxiang tmp(false);
        std::getline(std::cin, line);
        std::stringstream ss(line);
        ss >> tmp.name;
        ss >> tmp.type;
        ss >> tmp.value;
        i++;
        ss >> tmp.deltaPianYiLiang;
        InitdeltaPianYiLiang = std::max(InitdeltaPianYiLiang, tmp.deltaPianYiLiang); // 更新符号表中变量的初始偏移量
        huhaobiao["TB" + std::to_string(i)] = tmp;                                 // 将该项目加入符号表
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

    {
        int blkid = 0;
        while (blkid < global_jibenkuai.size())
        {
            auto &block = global_jibenkuai[blkid];
            if (biaoqianbiaozhiwei[global_jibenkuai[blkid].front()] == 1)
            {
                std::cout << "?" + std::to_string(block.front()) + ":\n";
            }
            for (auto j : block)
            { // 为每个四元式生成代码

                if (theta(Siyuanshis[j]))
                {
                    func9(j, blkid);
                }
                else if (type_x(Siyuanshis[j]))
                {
                    func8(j, blkid);
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
                            func7(Siyuanshis[j].value.val, huoyuebianliang[blkid]);
                        }
                    }
                }
            }
            for (auto a : huoyuebianliang[blkid])
            { // foreach a∈huoyuebianliang（Bi）
                if (dizhimiaoshufu[a].memory.find(a) == dizhimiaoshufu[a].memory.end())
                { // 并且a不属于dizhimiaoshufu（a）do
                    if (!dizhimiaoshufu[a].registerSet.empty())
                    {
                        for (auto reg : dizhimiaoshufu[a].registerSet)
                        { // Ra=dizhimiaoshufu（a）中的寄存器；
                            if (lishixinxi[a].huoyue)
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
                auto p = bianliang1.value.val;
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
                std::cout << "jne" << " ?" << p << "\n";    // 生成代码：jne ?q；
            }
            else if (type_finish(bianliang1))
            { // else if bianliang1形如（End，-，-，-）then
                std::cout << "halt" << "\n";
            }
            jicunqimiaoshufu.clear(); // 所有寄存器描述符置空
            dizhimiaoshufu.clear(); // 所有变量的地址描述符置空

            blkid++;
        }
    }
    return 0;
}