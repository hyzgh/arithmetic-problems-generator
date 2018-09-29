#ifndef CODE_ARITHMETIC_PROBLEMS_GENERATOR_PROJECT_ARITHMETICPROBLEMSGENERATOR_H_
#define CODE_ARITHMETIC_PROBLEMS_GENERATOR_PROJECT_ARITHMETICPROBLEMSGENERATOR_H_
/* Copyright 2018 Yuzhao Hong */
#include <bits/stdc++.h>
#include "ImproperFraction.h"

std::string charToString(char c);

// 判断是否是一个运算符
bool isOperator(const std::string &s);

// 将string转化为int
int stringToInteger(const std::string &s);

//将中缀表达式转化为后缀表达式
std::queue<std::string> transformInfixExprToSuffixExpr(
    const std::string &InfixExpression);

// 计算后缀表达式的答案
ImproperFraction getSuffixExpressionAnswer(
    std::queue<std::string> suffixExpression);

// 计算中缀表达式的答案
ImproperFraction getInfixExpressionAnswer(std::string s);

// 输出正确题目总个数和正确题目的ID
void printCorrectID(FILE *pFile, std::vector<int> correctID);

// 输出错误题目总个数和错误题目的ID
void printWrongID(FILE *pFile, std::vector<int> wrongID);

// 注意文件合法性应该在之前就判断好
void checkAnswer(FILE *exerciseFile, FILE *answerFile);

// 检查是否是一个合法的参数
bool isALegalParameter(char *s);

// 检查是否是一个不合法的参数组合
bool isIllegalParameterCombination(int argc, char **argv,
                                   std::map<char, bool> &mode);

// 检查接在-n或-r的数字是否不合法
bool isIllegalNumber(int argc, char **argv,
    int &exerciseNumber, int &maxNumber);

bool isIllegalFile(int argc, char **argv,
    FILE *&exerciseFile, FILE *&answerFile);

// 一个参数都没有
bool noParameter(int argc);

/*@author zhangab */

// 整数转换成字符串
void digToString(int num, std::string &str);

// 分数转换成字符串
void fractionToString(ImproperFraction a, std::string &str);

// 添加括号
std::string addbrackests(std::string s);

// 生成题集
void questionSetGenerate(int limit, int number);

#endif  // CODE_ARITHMETIC_PROBLEMS_GENERATOR_PROJECT_ARITHMETICPROBLEMSGENERATOR_H_
