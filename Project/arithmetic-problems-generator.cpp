/* Copyright 2018 Yuzhao Hong */

#include<bits/stdc++.h>

std::string charToString(char c) {
  std::string s;
  s += c;
  return s;
}

bool isOperator(const std::string &s) {
  return s[0] == 'x' || s[0] == '\xc3' || s[0] == '+' || s[0] == '-';
}

int stringToInteger(const std::string &s) {
  int ans = 0;
  for (int i = 0; i < s.length(); i++) {
    ans *= 10;
    ans += s[i] - '0';
  }
  return ans;
}

/*
 * @author hyz
 * 将中缀表达式转化为后缀表达式
 */
std::queue<std::string> transformInfixExprToSuffixExpr(
    const std::string &InfixExpression) {
  std::stack<char> temp;
  std::queue<std::string> result;
  for (int i = 0; i < InfixExpression.length(); i++) {
    char cc = InfixExpression[i];
    if (cc == ' ') {
      continue;
    } else if (cc == '(') {
      temp.push(cc);
    } else if (cc == ')') {
      char c;
      do {
        c = temp.top();
        temp.pop();
        if (c != '(') {
          result.push(charToString(c));
        }
      } while (c != '(');
    } else if (cc == '+' || cc == '-') {
      while (!temp.empty()) {
        char c = temp.top();
        if (c != '(') {
          result.push(charToString(c));
          temp.pop();
        } else {
          break;
        }
      }
      temp.push(cc);
    } else if (cc == 'x' || cc == '\xc3') {
      i += cc == '\xc3';  // ÷是非ASCI字符，其UTF-8编码为\xc3\xb7
      while (!temp.empty()) {
        char c = temp.top();
        if (c == 'x') {
          result.push(charToString(c));
          temp.pop();
        } else if (c == '\xc3') {
          result.push(charToString(c));
          temp.pop();
        }
        else {
          break;
        }
      }
      temp.push(cc);
    } else {
      std::string s;
      while (i < InfixExpression.length()) {
        char c = InfixExpression[i];
        if (isdigit(c) || c == '/' || c == '\'') {
          s += c;
          i++;
        } else {
          i--;
          break;
        }
      }
      result.push(s);
    }
  }
  while (!temp.empty()) {
    char c = temp.top();
    temp.pop();
    result.push(charToString(c));
  }
  return result;
}

/*
 * 计算后缀表达式的答案
 */
int getSuffixExpressionAnswer(std::queue<std::string> suffixExpression) {
  std::stack<int> sta;
  while (!suffixExpression.empty()) {
    std::string s = suffixExpression.front();
    suffixExpression.pop();
    if (isOperator(s)) {
      int a = sta.top();
      sta.pop();
      int b = sta.top();
      sta.pop();
      if (s[0] == 'x') {
        sta.push(a * b);
      } else if (s[0] == '\xc3') {
        sta.push(a / b);
      } else if (s[0] == '+') {
        sta.push(a + b);
      } else {
        sta.push(b - a);
      }
    } else {
      sta.push(stringToInteger(s));
    }
  }
  return sta.top();
}

/*
 * 计算中缀表达式的答案
 */
int getInfixExpressionAnswer(std::string s) {
  return getSuffixExpressionAnswer(transformInfixExprToSuffixExpr(s));
}

void printCorrectID(FILE *pFile, std::vector<int> correctID) {
  fprintf(pFile, "Correct: %lu(", correctID.size());
  if(!correctID.empty()) {
    fprintf(pFile, "%d", correctID[0]);
  }
  for(int i = 1; i < correctID.size(); i++) {
    fprintf(pFile, ", %d", correctID[i]);
  }
  fprintf(pFile, ")\n");
}

void printWrongID(FILE *pFile, std::vector<int> wrongID) {
  fprintf(pFile, "Wrong: %lu(", wrongID.size());
  if(!wrongID.empty()) {
    fprintf(pFile, "%d", wrongID[0]);
  }
  for(int i = 1; i < wrongID.size(); i++) {
    fprintf(pFile, ", %d", wrongID[i]);
  }
  fprintf(pFile, ")\n");
}

// 注意文件合法性应该在之前就判断好
void checkAnswer(FILE *exerciseFile, FILE *answerFile) {
  FILE *pFile;
  pFile = fopen("Grade.txt", "r");
  if (pFile == NULL) {
    pFile = fopen("Grade.txt", "w");
    fprintf(pFile, "%d", 100);
    fclose(pFile);
  }
  else {
    // 直接覆盖Grade.txt
    printf("The old Grade.txt will be overwrited.\n");
    fclose(pFile);
    remove("Grade.txt");

    pFile = fopen("Grade.txt", "w");

    int problemID = 0;
    char answer[256];
    char exercise[256];
    std::vector<int> wrongID;
    std::vector<int> correctID;
    // 答案的行数可能不等于题目的行数
    while(fgets(answer, 256, answerFile)) {
      if (!fgets(exercise, 256, exerciseFile)) {
        break;
      }
      problemID++;
      if (getInfixExpressionAnswer(exercise) ==  stringToInteger(answer)) {
        correctID.push_back(problemID);
      }
      else {
        wrongID.push_back(problemID);
      }
    }
    while(fgets(exercise, 256, exerciseFile)) {
      problemID++;
      wrongID.push_back(problemID);
    }

    printCorrectID(pFile, correctID);
    printWrongID(pFile, wrongID);
    fclose(pFile);
  }
}
