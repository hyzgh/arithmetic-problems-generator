/* Copyright 2018 Yuzhao Hong */
#ifndef CODE_ARITHMETIC_PROBLEMS_GENERATOR_PROJECT_ARITHMETICPROBLEMSGENERATOR_H_
#define CODE_ARITHMETIC_PROBLEMS_GENERATOR_PROJECT_ARITHMETICPROBLEMSGENERATOR_H_
#include <map>
#include <queue>
#include <vector>
#include <string>
#include "ImproperFraction.h"

// ��charת��Ϊstring
std::string charToString(char c);

// �ж��Ƿ���һ�������
bool isOperator(const std::string &s);

// ��stringת��ΪImproperFraction
ImproperFraction stringToInteger(const std::string &s);

// ����׺���ʽת��Ϊ��׺���ʽ
std::queue<std::string> transformInfixExprToSuffixExpr(
    const std::string &InfixExpression);

// �����׺���ʽ�Ĵ�
ImproperFraction getSuffixExpressionAnswer(
    std::queue<std::string> suffixExpression);

// ������׺���ʽ�Ĵ�
ImproperFraction getInfixExpressionAnswer(std::string s);

// �����ȷ�𰸻����𰸵�ID
void printID(FILE *pFile, char *s, std::vector<int> ID);

// ȥ����ȡ�е����ಿ�֣�����źͻ��з�
void removeRedundantPart(char *answer, char *exercise);

// ������ű�������
void handleDivideEncoding(char *exercise);

// �õ�ָ��Grade.txt�ļ���ָ��
FILE *getPointerToGradeFile();

// ����
void checkAnswer(FILE *exerciseFile, FILE *answerFile);

// �ж���û�в���
bool noParameter(int argc);

// ����Ƿ���һ���Ϸ��Ĳ���
bool isALegalParameter(char *s);

// ����Ƿ���һ�����Ϸ��Ĳ������
bool isIllegalParameterCombination(int argc, char **argv,
                                   std::map<char, bool> *mode);

// ������-n��-r�������Ƿ񲻺Ϸ�
bool isIllegalNumber(int argc, char **argv,
    int *exerciseNumber, int *maxNumber);

// ����ļ��Ƿ񲻺Ϸ�
bool isIllegalFile(int argc, char **argv,
    FILE **exerciseFile, FILE **answerFile);

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
