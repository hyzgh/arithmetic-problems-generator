/* Copyright 2018 Yuzhao Hong */
#ifndef CODE_ARITHMETIC_PROBLEMS_GENERATOR_PROJECT_ARITHMETICPROBLEMSGENERATOR_H_
#define CODE_ARITHMETIC_PROBLEMS_GENERATOR_PROJECT_ARITHMETICPROBLEMSGENERATOR_H_
#include <map>
#include <queue>
#include <vector>
#include <string>
#include "ImproperFraction.h"

// 将char转化为string
std::string charToString(char c);

// 判断是否是一个运算符
bool isOperator(const std::string &s);

// 将string转化为ImproperFraction
ImproperFraction stringToInteger(const std::string &s);

// 将中缀表达式转化为后缀表达式
std::queue<std::string> transformInfixExprToSuffixExpr(
    const std::string &InfixExpression);

// 计算后缀表达式的答案
ImproperFraction getSuffixExpressionAnswer(
    std::queue<std::string> suffixExpression);

// 计算中缀表达式的答案
ImproperFraction getInfixExpressionAnswer(std::string s);

// 输出正确答案或错误答案的ID
void printID(FILE *pFile, char *s, std::vector<int> ID);

// 去除读取行的冗余部分，即序号和换行符
void removeRedundantPart(char *answer, char *exercise);

// 处理除号编码问题
void handleDivideEncoding(char *exercise);

// 得到指向Grade.txt文件的指针
FILE *getPointerToGradeFile();

// 检查答案
void checkAnswer(FILE *exerciseFile, FILE *answerFile);

// 判断有没有参数
bool noParameter(int argc);

// 检查是否是一个合法的参数
bool isALegalParameter(char *s);

// 检查是否是一个不合法的参数组合
bool isIllegalParameterCombination(int argc, char **argv,
                                   std::map<char, bool> *mode);

// 检查接在-n或-r的数字是否不合法
bool isIllegalNumber(int argc, char **argv,
    int *exerciseNumber, int *maxNumber);

// 检查文件是否不合法
bool isIllegalFile(int argc, char **argv,
    FILE **exerciseFile, FILE **answerFile);

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
