#ifndef CODE_ARITHMETIC_PROBLEMS_GENERATOR_PROJECT_ARITHMETICPROBLEMSGENERATOR_H_
#define CODE_ARITHMETIC_PROBLEMS_GENERATOR_PROJECT_ARITHMETICPROBLEMSGENERATOR_H_
/* Copyright 2018 Yuzhao Hong */
#include <bits/stdc++.h>
#include "ImproperFraction.h"

std::string charToString(char c);

// �ж��Ƿ���һ�������
bool isOperator(const std::string &s);

// ��stringת��Ϊint
int stringToInteger(const std::string &s);

//����׺���ʽת��Ϊ��׺���ʽ
std::queue<std::string> transformInfixExprToSuffixExpr(
    const std::string &InfixExpression);

// �����׺���ʽ�Ĵ�
ImproperFraction getSuffixExpressionAnswer(
    std::queue<std::string> suffixExpression);

// ������׺���ʽ�Ĵ�
ImproperFraction getInfixExpressionAnswer(std::string s);

// �����ȷ��Ŀ�ܸ�������ȷ��Ŀ��ID
void printCorrectID(FILE *pFile, std::vector<int> correctID);

// ���������Ŀ�ܸ����ʹ�����Ŀ��ID
void printWrongID(FILE *pFile, std::vector<int> wrongID);

// ע���ļ��Ϸ���Ӧ����֮ǰ���жϺ�
void checkAnswer(FILE *exerciseFile, FILE *answerFile);

// ����Ƿ���һ���Ϸ��Ĳ���
bool isALegalParameter(char *s);

// ����Ƿ���һ�����Ϸ��Ĳ������
bool isIllegalParameterCombination(int argc, char **argv,
                                   std::map<char, bool> &mode);

// ������-n��-r�������Ƿ񲻺Ϸ�
bool isIllegalNumber(int argc, char **argv,
    int &exerciseNumber, int &maxNumber);

bool isIllegalFile(int argc, char **argv,
    FILE *&exerciseFile, FILE *&answerFile);

// һ��������û��
bool noParameter(int argc);

/*@author zhangab */

// ����ת�����ַ���
void digToString(int num, std::string &str);

// ����ת�����ַ���
void fractionToString(ImproperFraction a, std::string &str);

// �������
std::string addbrackests(std::string s);

// �����⼯
void questionSetGenerate(int limit, int number);

#endif  // CODE_ARITHMETIC_PROBLEMS_GENERATOR_PROJECT_ARITHMETICPROBLEMSGENERATOR_H_
