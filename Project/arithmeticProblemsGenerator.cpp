/* Copyright 2018 Yuzhao Hong, Binkun Zhang */

#include <bits/stdc++.h>
#include "arithmeticProblemsGenerator.h"

/* @author hyz */
// 将char转化为string
std::string charToString(char c) {
  std::string s;
  s += c;
  return s;
}

// 判断是否是一个运算符
bool isOperator(const std::string &s) {
  // ÷的UTF-8编码为\xc3\xb7
  return s[0] == 'x' || s[0] == '\xc3' || s[0] == '+' || s[0] == '-';
}

// 将string转化为ImproperFraction
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

// 将中缀表达式转化为后缀表达式
std::queue<std::string> transformInfixExprToSuffixExpr(
    const std::string &InfixExpression) {
  std::stack<char> temp;
  std::queue<std::string> result;
  for (int i = 0; i < InfixExpression.length(); i++) {
    char cc = InfixExpression[i];
    if (cc == ' ') {  // 假如遇到空格就跳过
      continue;
    } else if (cc == '(') {  // 遇到左括号就直接入栈
      temp.push(cc);
    } else if (cc == ')') {  // 遇到右括号就弹出栈里面的所有运算符，直到遇到左括号
      char c;
      do {
        c = temp.top();
        temp.pop();
        if (c != '(') {
          result.push(charToString(c));
        }
      } while (c != '(');
    } else if (cc == '+' || cc == '-') {
      // 遇到加号减号也弹出栈顶的所有运算符，直到遇到左括号或者为栈为空
      while (!temp.empty()) {
        char c = temp.top();
        if (c != '(') {
          result.push(charToString(c));
          temp.pop();
        } else {
          break;
        }
      }
      temp.push(cc);  // 然后将加号入栈
    } else if (cc == 'x' || cc == '\xc3') {
      // 假如遇到所有乘号除号，就弹出栈顶的乘号除号，知道遇到加号减号或者左括号或者栈为空
      i += cc == '\xc3';
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
      // 假如遇到数字，那就直接输出
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
  // 把栈里面剩余的东西输出
  while (!temp.empty()) {
    char c = temp.top();
    temp.pop();
    result.push(charToString(c));
  }
  return result;
}

// 计算后缀表达式的答案
ImproperFraction getSuffixExpressionAnswer(
    std::queue<std::string> suffixExpression) {
  std::stack<ImproperFraction> sta;
  while (!suffixExpression.empty()) {
    std::string s = suffixExpression.front();
    suffixExpression.pop();
    if (isOperator(s)) {
      // 假如遇到运算符，就取出栈顶元素进行计算
      ImproperFraction a = sta.top();
      sta.pop();
      ImproperFraction b = sta.top();
      sta.pop();
      if (s[0] == 'x') {
        sta.push(a * b);
      } else if (s[0] == '\xc3') {
        sta.push(b / a);
      } else if (s[0] == '+') {
        sta.push(a + b);
      } else {
        sta.push(b - a);
      }
    } else {
      // 假如遇到数字，就直接进栈
      sta.push(stringToImproperFraction(s));
    }
  }
  return sta.top();
}

// 计算中缀表达式的答案
ImproperFraction getInfixExpressionAnswer(std::string s) {
  return getSuffixExpressionAnswer(transformInfixExprToSuffixExpr(s));
}

// 输出正确答案或错误答案的ID
void printID(FILE *pFile, char *s, std::vector<int> ID) {
  fprintf(pFile, "%s: %lu(", s, ID.size());
  if (!ID.empty()) {
    fprintf(pFile, "%d", ID[0]);
  }
  for (int i = 1; i < ID.size(); i++) {
    fprintf(pFile, ", %d", ID[i]);
  }
  fprintf(pFile, ")\n");
}

// 去除读取行的冗余部分，即序号和换行符
void removeRedundantPart(char *answer, char *exercise) {
    answer[strlen(answer) - 1] = 0;
    exercise[strlen(exercise) - 1] = 0;
    int p = 0;
    while (exercise[p] != ' ') {
      p++;
    }
    char temp[256];
    memcpy(temp, answer + p + 1, strlen(answer) - p);
    memcpy(answer, temp, strlen(temp) + 1);
    memcpy(temp, exercise + p + 1, strlen(exercise) - p);
    memcpy(exercise, temp, strlen(temp) + 1);
}

// 处理除号编码问题
void handleDivideEncoding(char *exercise) {
  for (int i = 0; i < strlen(exercise); i++) {
    if (exercise[i] < 0) {
      exercise[i] = '\xc3';
      exercise[++i] = '\xb7';
    }
  }
}

// 得到指向Grade.txt文件的指针
FILE *getPointerToGradeFile() {
  FILE *pFile = fopen("Grade.txt", "r");
  if (pFile == NULL) {
    pFile = fopen("Grade.txt", "w");
  } else {
    printf("The old Grade.txt will be overwrited.\n");
    fclose(pFile);
    remove("Grade.txt");
    pFile = fopen("Grade.txt", "w");
  }
  return pFile;
}

// 检查答案
void checkAnswer(FILE *exerciseFile, FILE *answerFile) {
  FILE *pFile = getPointerToGradeFile();
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
    // 去除读取行的冗余部分，即序号和换行符
    removeRedundantPart(answer, exercise);
    // 处理除号编码问题
    handleDivideEncoding(exercise);

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

  // 输出序号
  printID(pFile, const_cast<char*>("Correct"), correctID);
  printID(pFile, const_cast<char*>("Wrong"), wrongID);
  fclose(pFile);
  printf("Check answer done!\n");
}

// 判断有没有参数
bool noParameter(int argc) {
  return argc == 1;
}

// 检查是否是一个合法的参数
bool isALegalParameter(char *s) {
  return strlen(s) == 2 &&
    (s[1] == 'n' || s[1] == 'r' || s[1] == 'e' || s[1] == 'a');
}

// 检查是否是一个不合法的参数组合
bool isIllegalParameterCombination(int argc, char **argv,
    std::map<char, bool> *mode) {
  for (int i = 1; i < argc; i++) {
    if (argv[i][0] == '-' && isALegalParameter(argv[i])) {
      (*mode)[argv[i][1]] = true;
    } else if (argv[i][0] == '-') {
      return true;
    }
  }
  if (((*mode)['n'] || (*mode)['r']) && ((*mode)['e'] || (*mode)['a'])) {
    return true;
  } else if ((*mode)['n'] && (*mode)['r']) {
    return false;
  } else if ((*mode)['e'] && (*mode)['a']) {
    return false;
  }
  return true;
}

// 检查接在-n或-r的数字是否不合法
bool isIllegalNumber(int argc, char **argv,
    int *exerciseNumber, int *maxNumber) {
  for (int i = 1; i < argc; i++) {
    if (argv[i][0] == '-' && argv[i][1] == 'n') {
      if (++i == argc)
        return true;
      *exerciseNumber = 0;
      for (int j = 0; j < strlen(argv[i]); j++) {
        if (!isdigit(argv[i][j])) {
          return true;
        }
        *exerciseNumber = *exerciseNumber * 10 + argv[i][j] - '0';
      }
    } else if (argv[i][0] == '-' && argv[i][1] == 'r') {
      if (++i == argc)
        return true;
      *maxNumber = 0;
      for (int j = 0; j < strlen(argv[i]); j++) {
        if (!isdigit(argv[i][j])) {
          return true;
        }
        *maxNumber = *maxNumber * 10 + argv[i][j] - '0';
      }
    }
  }
  return *exerciseNumber <= 0 || *maxNumber <= 0;
}

// 检查文件是否不合法
bool isIllegalFile(int argc, char **argv, FILE **exerciseFile, FILE **answerFile
    ) {
  for (int i = 1; i < argc; i++) {
    if (argv[i][0] == '-' && argv[i][1] == 'e') {
      if (++i == argc)
        return true;
      if (!(*exerciseFile = fopen(argv[i], "r")))
        return true;
    } else if (argv[i][0] == '-' && argv[i][1] == 'a') {
      if (++i == argc)
        return true;
      if (!(*answerFile = fopen(argv[i], "r")))
        return true;
    }
  }
  return false;
}

/* @author zhangab */
const char oper[5] = "+-*/";

//数字转化成字符串
void digToString(int num, std::string &str) {
  if (num / 10) {
    digToString(num / 10, str);
  }
  str = str + (char)(num % 10 + '0');
}

//分数转化成字符串
void fractionToString(ImproperFraction a, std::string &str) {
  int deno = a.getdeno();
  int mole = a.getmole();
  int coef = mole / deno;
  mole %= deno;
  if (coef) {
    digToString(coef, str);
    if (mole) {
      str = str + '\'';
      digToString(mole, str);
      str = str + '/';
      digToString(deno, str);
    }
  } else if (mole) {
    digToString(mole, str);
    str = str + '/';
    digToString(deno, str);
  } else {
    digToString(0, str);
  }
}

// 添加括号
std::string addbrackets(std::string s) {
  std::vector <std::pair <int, int> > op;  // 运算符的优先级，以及位置
  std::map<char, int> pri;
  pri['+'] = 1;
  pri['-'] = 1;
  pri['*'] = 2;
  pri['/'] = 2;
  for (int i = 0; i < s.length(); i ++) {
    if (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/') {
      if (s[i - 1] == ' ' && s[i + 1] == ' ') {
        op.push_back(std::pair<int, int> (pri[s[i]], i));
      }
    }
  }
  for (int i = 1; i < (int)op.size(); i++) {
    if (op[i].first > op[i - 1].first) {
      s = '(' + s.substr(0, op[i].second - 1) + ')' +
        s.substr(op[i].second - 1, s.length() - op[i].second + 1);
      break;
    }
  }
  return s;
}

// 生成题集
void questionSetGenerate(int limit, int number) {
  srand(time(NULL));
  std::set<std::string>expressions;
  std::vector<std::string>exercise;
  std::vector<ImproperFraction>answer;
  int time = 0;
  while (expressions.size() < number && time < 1000000) {
    time++;
    int sz = expressions.size();
    int opnumber = rand() % 3 + 1;
    ImproperFraction a[5];
    ImproperFraction res = ImproperFraction(0, 1);
    const ImproperFraction zero = ImproperFraction(0, 1);
    char op[4];
    for (int i = 0; i <= opnumber; i++) {
      int deno = std::max(1, rand() % limit);
      int mole = rand() % deno;
      int coef = rand() % limit;
      a[i] = ImproperFraction(mole, deno, coef);
      if (i) {
        op[i] = oper[rand() % 4];
      }
    }
    std::string exp = "";
    bool flag = true;
    if (a[0] < a[1]) {
      std::swap(a[0], a[1]);
    }

    for (int i = 0; i <= opnumber; i++) {
      if (i) {
        if (op[i] == '+') {
          res = res + a[i];
        } else if (op[i] == '*') {
          res = res * a[i];
        } else if (op[i] == '-') {
          res = res - a[i];
        } else {
          if (a[i] == zero) {
            flag = false;
            break;
          }
          res = res / a[i];
        }
        exp = exp + ' ';
        exp = exp + op[i];
        exp = exp + ' ';
      } else {
        res = res + a[i];
      }
      fractionToString(a[i], exp);
      if (res.getdeno() < 0 || res.getmole() < 0) {
        flag = false;
        break;
      }
    }
    if (flag) {
      expressions.insert(exp);
      if (expressions.size() > sz) {
        exercise.push_back(addbrackets(exp));
        answer.push_back(res);
      }
    }
  }
  if (exercise.size() < number) {
    printf("生成 %d 道题目失败!给定参数r= %d 太小,只生成了 %d 道题目\n", number, limit, exercise.size());
  } else {
    printf("生成 %d 到题目成功!\n", number);
  }
  freopen("Exercises.txt", "w", stdout);
  int cnt = 1;
  for (auto i: exercise) {
    printf("%d. ", cnt ++);
    for (int j = 0; j < i.size(); j++) {
      if (i[j] == '*') {
        printf("x");
      } else if (i[j] == '/' && i[j - 1] == ' ') {
        printf("÷");
      } else {
        std::cout << i[j];
      }
    }
    putchar('\n');
  }
  freopen("Answers.txt", "w", stdout);
  cnt = 1;
  for (auto i: answer) {
    printf("%d. ", cnt ++);
    i.out();
    putchar('\n');
  }
}
