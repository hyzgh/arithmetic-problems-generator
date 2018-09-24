/* Copyright 2018 Yuzhao Hong */
#include<bits/stdc++.h>

std::string charToString(char c);

// 判断是否是一个运算符
bool isOperator(const std::string &s);

// 将string转化为int
int stringToInteger(const std::string &s);

//将中缀表达式转化为后缀表达式
std::queue<std::string> transformInfixExprToSuffixExpr(
    const std::string &InfixExpression);

// 计算后缀表达式的答案
int getSuffixExpressionAnswer(std::queue<std::string> suffixExpression);

// 计算中缀表达式的答案
int getInfixExpressionAnswer(std::string s);

// 输出正确题目总个数和正确题目的ID
void printCorrectID(FILE *pFile, std::vector<int> correctID);

// 输出错误题目总个数和错误题目的ID
void printWrongID(FILE *pFile, std::vector<int> wrongID);

// 注意文件合法性应该在之前就判断好
void checkAnswer(FILE *exerciseFile, FILE *answerFile);

// 整数转换成字符串
void digToString (int num, string &str);

// 分数转换成字符串
void fractionToString (ImproperFraction a, string &str);

// 生成表法式
void expression_generate (ImproperFraction value,
                          int limit,
                          int last,
                          string str,
                          set<string> &questions);

// 生成题集
void questionSetGenerate (int limit, int number);
