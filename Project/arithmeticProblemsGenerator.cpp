/* Copyright 2018 Yuzhao Hong */

#include<bits/stdc++.h>
#include"arithmeticProblemsGenerator.h"
#include"ImproperFraction.h"

// only for debug
#define ok std::cout << "ok" << std::endl;

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
  } else {
    // 直接覆盖Grade.txt
    printf("The old Grade.txt will be overwrited.\n");
    fclose(pFile);
    remove("Grade.txt");
    pFile = fopen("Grade.txt", "w");
  }

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
    answer[strlen(answer) - 1] = 0;
    exercise[strlen(exercise) - 1] = 0;
    getInfixExpressionAnswer(exercise).out();
    stringToImproperFraction(answer).out();
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
      maxNumber = 0;
      for (int j = 0; j < strlen(argv[i]); j++) {
        if (!isdigit(argv[i][j])) {
          return true;
        }
        maxNumber = maxNumber * 10 + argv[i][j] - '0';
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

/* @author zhangab */
const char oper[5] = "+-*/";

//数字转化成字符串
void digToString (int num, std::string &str) {
  if (num / 10) {
    digToString (num / 10, str);
  }
  str = str + (char)(num % 10 + '0');
}

//分数转化成字符串
void fractionToString (ImproperFraction a, std::string &str) {
  int deno = a.getdeno ();
  int mole = a.getmole ();
  int coef = mole / deno;
  mole %= deno;
  if (coef) {
    digToString (coef, str);
    if (mole) {
      str = str + '\'';
      digToString (mole, str);
      str = str + '/';
      digToString (deno, str);
    }
  } else if (mole) {
    digToString (mole, str);
    str = str + '/';
    digToString (deno, str);
  } else {
    digToString (0, str);
  }
}

// 生成表达式
void expression_generate (ImproperFraction value,
    int limit,
    int last,
    std::string str,
    std::set<std::string> &questions) {
  ImproperFraction zero = ImproperFraction(0, 1);
  if (value < zero || questions.size() > 100000) { // 小于0去除, 并且每次限制生成2w上限题目
    return ;
  }
  if (last == 0) { //插入题集
    questions.insert(str);
    return ;
  }
  if (last & 1) { // 生成数值
    std::string s = str;
    if (value != zero) {
      for (int dig = 0; dig < limit * limit; dig ++) {
        str = s;
        ImproperFraction fra = ImproperFraction (dig, limit);
        if (str.length() < 2) {
          value = fra;
        } else if (str[str.length() - 2] == '-') {
          value = value - fra;
        } else if (str[str.length() - 2] == '+') {
          value = value + fra;
        } else if (str[str.length() - 2] == '*') {
          value = value * fra;
        } else if (str[str.length() - 2] == '/' && fra != zero) {
          value = value / fra;
        } else {
          continue;
        }
        fractionToString (fra, str);
        expression_generate (value, limit, last - 1, str, questions);
      }
    } else {
      ImproperFraction fra = ImproperFraction (rand() % limit, limit);
      str = s;
      if (str.length() < 2) {
        value = fra;
      } else if (str[str.length() - 2] == '-') {
        value = value - fra;
      } else if (str[str.length() - 2] == '+') {
        value = value + fra;
      } else if (str[str.length() - 2] == '*') {
        value = value * fra;
      } else if (str[str.length() - 2] == '/' && fra != zero) {
        value = value / fra;
      } else {
        return;
      }
      fractionToString (fra, str);
      expression_generate (value, limit, last - 1, str, questions);
    }

  } else { // 生成符号
    std::string s = str;
    for (int op = 0; op < 4; op ++) {
      str = s;
      str = str + ' ';
      str = str + oper[op];
      str = str + ' ';
      expression_generate (value, limit, last - 1, str, questions);
    }
  }
}

// 添加括号
std::string addbrackets (std::string s) {
  std::vector <std::pair <int, int> > op; // 运算符的优先级，以及位置
  std::map<char, int> pri;
  pri['+'] = 1;
  pri['-'] = 1;
  pri['*'] = 2;
  pri['/'] = 2;
  for (int i = 0; i < s.length(); i ++) {
    if (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/') {
      if(s[i - 1] == ' ' && s[i + 1] == ' ') {
        op.push_back (std::pair<int, int> (pri[s[i]], i));
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
void questionSetGenerate (int limit, int number) {
  std::set <std::string> questions;
  std::vector <std::string> out;
  //一个操作符
  ImproperFraction zero = ImproperFraction(0, 1);
  expression_generate(zero, limit, 3, "", questions);
  std::set <std::string> :: iterator it;
  for (it = questions.begin(); it != questions.end(); it++) {
    std::string s = addbrackets (*it);
    out.push_back (s);
  }
  questions.clear();

  expression_generate(zero, limit, 5, "", questions);

  for (it = questions.begin(); it != questions.end(); it++) {
    std::string s = addbrackets (*it);
    out.push_back (s);
  }
  questions.clear();

  expression_generate(zero, limit, 7, "", questions);
  for (it = questions.begin(); it != questions.end(); it++) {
    std::string s = addbrackets (*it);
    out.push_back (s);
  }
  questions.clear();

  int len = out.size();
  random_shuffle (out.begin(), out.end());
  std::vector<ImproperFraction> ans; //
  freopen ("Exercise.txt", "w", stdout);
  int cnt = 1;
  while (number --) {
    printf ("%d. ", cnt ++);
    int ind = rand() % len;
    std::string s = ""; //
    for (int j = 0; j < out[ind].length(); j++) {
      if (out[ind][j] == '*') {
        std::cout << 'x';
        s = s + 'x'; //
      } else if (out[ind][j] == '/' && out[ind][j-1] == ' ') {
        std::cout << "÷";
        s = s + "÷"; //
      } else {
        std::cout << out[ind][j];
        s = s + out[ind][j]; //
      }
    }
    ans.push_back(getInfixExpressionAnswer(s)); //
    putchar('\n');
    swap(out[-- len], out[ind]);
  }
  freopen ("Answer.txt", "w", stdout); //
  for (int i = 0; i < ans.size(); i++) { //
    printf ("%d. ", i + 1);
    ans[i].out(); //
    putchar('\n'); //
  } //
}

