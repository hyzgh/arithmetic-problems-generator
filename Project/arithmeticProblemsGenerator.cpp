/* Copyright 2018 Yuzhao Hong */

#include<bits/stdc++.h>
#include"arithmeticProblemsGenerator.h"
#include"ImproperFraction.h"

std::string charToString(char c) {
  std::string s;
  s += c;
  return s;
}

bool isOperator(const std::string &s) {
  return s[0] == 'x' || s[0] == '\xc3' || s[0] == '+' || s[0] == '-';
}

ImproperFraction stringToImproperFraction(const std::string &s) {
  int mole = 0;
  int deno = 0;
  int coef = 0;
  bool denoFlag = false;
  for (int i = 0; i < s.length(); i++) {
    if (s[i] == '\'') {
      coef = mole;
      mole = 0;
    } else if (s[i] == '/') {
      denoFlag = true;
    } else if (denoFlag) {
      deno = deno * 10 + s[i] - '0';
    } else {
      mole = mole * 10 + s[i] - '0';
    }
  }
  if (denoFlag)
    return ImproperFraction(mole, deno, coef);
  else
    return ImproperFraction(mole, 1, 0);
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
        } else {
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
ImproperFraction getSuffixExpressionAnswer(
    std::queue<std::string> suffixExpression) {
  std::stack<ImproperFraction> sta;
  while (!suffixExpression.empty()) {
    std::string s = suffixExpression.front();
    suffixExpression.pop();
    if (isOperator(s)) {
      ImproperFraction a = sta.top();
      sta.pop();
      ImproperFraction b = sta.top();
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
      sta.push(stringToImproperFraction(s));
    }
  }
  return sta.top();
}

/*
 * 计算中缀表达式的答案
 */
ImproperFraction getInfixExpressionAnswer(std::string s) {
  return getSuffixExpressionAnswer(transformInfixExprToSuffixExpr(s));
}

void printCorrectID(FILE *pFile, std::vector<int> correctID) {
  fprintf(pFile, "Correct: %lu(", correctID.size());
  if (!correctID.empty()) {
    fprintf(pFile, "%d", correctID[0]);
  }
  for (int i = 1; i < correctID.size(); i++) {
    fprintf(pFile, ", %d", correctID[i]);
  }
  fprintf(pFile, ")\n");
}

void printWrongID(FILE *pFile, std::vector<int> wrongID) {
  fprintf(pFile, "Wrong: %lu(", wrongID.size());
  if (!wrongID.empty()) {
    fprintf(pFile, "%d", wrongID[0]);
  }
  for (int i = 1; i < wrongID.size(); i++) {
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
  } else {
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
    while (fgets(answer, 256, answerFile)) {
      if (!fgets(exercise, 256, exerciseFile)) {
        break;
      }
      problemID++;
      if (getInfixExpressionAnswer(exercise) == stringToImproperFraction(answer)
          ) {
        correctID.push_back(problemID);
      } else {
        wrongID.push_back(problemID);
      }
    }
    while (fgets(exercise, 256, exerciseFile)) {
      problemID++;
      wrongID.push_back(problemID);
    }

    printCorrectID(pFile, correctID);
    printWrongID(pFile, wrongID);
    fclose(pFile);
    printf("Done!\n");
  }
}

bool noParameter(int argc) {
  return argc == 1;
}

bool isALegalParameter(char *s) {
  return strlen(s) == 2 &&
    (s[1] == 'n' || s[1] == 'r' || s[1] == 'e' || s[1] == 'a');
}

bool isIllegalParameterCombination(int argc, char **argv,
                                   std::map<char, bool> &mode) {
  for (int i = 1; i < argc; i++) {
    if (argv[i][0] == '-' && isALegalParameter(argv[i])) {
      mode[argv[i][1]] = true;
    } else if (argv[i][0] == '-') {
      return true;
    }
  }
  if ((mode['n'] || mode['r']) && (mode['e'] || mode['a'])) {
    return true;
  } else if (mode['n'] && mode['r']) {
    return false;
  } else if (mode['e'] && mode['a']) {
    return false;
  }
  return true;
}

bool isIllegalNumber(int argc, char **argv,
                     int &exerciseNumber, int &maxNumber) {
  for (int i = 1; i < argc; i++) {
    if (argv[i][0] == '-' && argv[i][1] == 'n') {
      if (++i == argc)
        return true;
      exerciseNumber = 0;
      for (int j = 0; j < strlen(argv[i]); j++) {
        if (!isdigit(argv[i][j])) {
          return true;
        }
        exerciseNumber = exerciseNumber * 10 + argv[i][j] - '0';
      }
    } else if (argv[i][0] == '-' && argv[i][1] == 'r') {
      if (++i == argc)
        return true;
      exerciseNumber = 0;
      for (int j = 0; j < strlen(argv[i]); j++) {
        if (!isdigit(argv[i][j])) {
          return true;
        }
        exerciseNumber = exerciseNumber * 10 + argv[i][j] - '0';
      }
    }
  }
  return false;
}

bool isIllegalFile(int argc, char **argv, FILE *&exerciseFile, FILE *&answerFile
    ) {
  for (int i = 1; i < argc; i++) {
    if (argv[i][0] == '-' && argv[i][1] == 'e') {
      if (++i == argc)
        return true;
      if (!(exerciseFile = fopen(argv[i], "r")))
        return true;
    } else if (argv[i][0] == '-' && argv[i][1] == 'a') {
      if (++i == argc)
        return true;
      if (!(answerFile = fopen(argv[i], "r")))
        return true;
    }
  }
  return false;
}
