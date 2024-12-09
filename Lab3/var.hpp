#ifndef VAR_HPP
#define VAR_HPP
#include <bits/stdc++.h>
// 操作映射，用于指令生成
std::map<std::string, std::string> operationMapping = {
    // 算术运算符映射
    {"+", "add"},   // 加法
    {"-", "sub"},   // 减法
    {"*", "mul"},   // 乘法
    {"/", "div"},   // 除法
    // 赋值和移动
    {"=", "mov"},   // 赋值
    // 比较运算符映射
    {"<", "cmp"},   // 小于
    {">", "cmp"},   // 大于
    {"<=", "cmp"},  // 小于等于
    {">=", "cmp"},  // 大于等于
    {"==", "cmp"},  // 等于
    {"!=", "cmp"},  // 不等于
    // 逻辑运算符映射
    {"&&", "and"},  // 逻辑与
    {"||", "or"},   // 逻辑或
    {"!", "not"}    // 逻辑非
};

// 条件跳转映射，用于条件跳转指令生成
std::map<std::string, std::string> conditionalJumpMapping = {
    // 条件跳转指令映射
    {"j<", "jl"},   // 跳转如果小于
    {"j>", "jg"},   // 跳转如果大于
    {"j<=", "jle"}, // 跳转如果小于等于
    {"j>=", "jge"}, // 跳转如果大于等于
    {"j==", "je"},  // 跳转如果等于
    {"j!=", "jne"}  // 跳转如果不等于
};

// 比较指令映射，用于生成具体的比较指令
std::map<std::string, std::string> comparisonInstructionMapping = {
    // 具体的比较指令
    {"<", "setl"},  // 设置小于
    {">", "setg"},  // 设置大于
    {"<=", "setle"}, // 设置小于等于
    {">=", "setge"}, // 设置大于等于
    {"==", "sete"},  // 设置等于
    {"!=", "setne"}  // 设置不等于
};

#endif