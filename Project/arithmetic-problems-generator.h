/* Copyright 2018 Yuzhao Hong */
#include<bits/stdc++.h>

std::string charToString(char c);

// �ж��Ƿ���һ�������
bool isOperator(const std::string &s);

// ��stringת��Ϊint
int stringToInteger(const std::string &s);

//����׺���ʽת��Ϊ��׺���ʽ
std::queue<std::string> transformInfixExprToSuffixExpr(
    const std::string &InfixExpression);

// �����׺���ʽ�Ĵ�
int getSuffixExpressionAnswer(std::queue<std::string> suffixExpression);

// ������׺���ʽ�Ĵ�
int getInfixExpressionAnswer(std::string s);

// �����ȷ��Ŀ�ܸ�������ȷ��Ŀ��ID
void printCorrectID(FILE *pFile, std::vector<int> correctID);

// ���������Ŀ�ܸ����ʹ�����Ŀ��ID
void printWrongID(FILE *pFile, std::vector<int> wrongID);

// ע���ļ��Ϸ���Ӧ����֮ǰ���жϺ�
void checkAnswer(FILE *exerciseFile, FILE *answerFile);

// ����ת�����ַ���
void digToString (int num, string &str);

// ����ת�����ַ���
void fractionToString (ImproperFraction a, string &str);

// ���ɱ�ʽ
void expression_generate (ImproperFraction value,
                          int limit,
                          int last,
                          string str,
                          set<string> &questions);

// �����⼯
void questionSetGenerate (int limit, int number);
