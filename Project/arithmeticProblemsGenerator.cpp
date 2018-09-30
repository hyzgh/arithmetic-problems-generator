/* Copyright 2018 Yuzhao Hong, Binkun Zhang */

#include <bits/stdc++.h>
#include "arithmeticProblemsGenerator.h"

/* @author hyz */
// ��charת��Ϊstring
std::string charToString(char c) {
  std::string s;
  s += c;
  return s;
}

// �ж��Ƿ���һ�������
bool isOperator(const std::string &s) {
  // �µ�UTF-8����Ϊ\xc3\xb7
  return s[0] == 'x' || s[0] == '\xc3' || s[0] == '+' || s[0] == '-';
}

// ��stringת��ΪImproperFraction
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

// ����׺���ʽת��Ϊ��׺���ʽ
std::queue<std::string> transformInfixExprToSuffixExpr(
    const std::string &InfixExpression) {
  std::stack<char> temp;
  std::queue<std::string> result;
  for (int i = 0; i < InfixExpression.length(); i++) {
    char cc = InfixExpression[i];
    if (cc == ' ') {  // ���������ո������
      continue;
    } else if (cc == '(') {  // ���������ž�ֱ����ջ
      temp.push(cc);
    } else if (cc == ')') {  // ���������ž͵���ջ����������������ֱ������������
      char c;
      do {
        c = temp.top();
        temp.pop();
        if (c != '(') {
          result.push(charToString(c));
        }
      } while (c != '(');
    } else if (cc == '+' || cc == '-') {
      // �����Ӻż���Ҳ����ջ���������������ֱ�����������Ż���ΪջΪ��
      while (!temp.empty()) {
        char c = temp.top();
        if (c != '(') {
          result.push(charToString(c));
          temp.pop();
        } else {
          break;
        }
      }
      temp.push(cc);  // Ȼ�󽫼Ӻ���ջ
    } else if (cc == 'x' || cc == '\xc3') {
      // �����������г˺ų��ţ��͵���ջ���ĳ˺ų��ţ�֪�������Ӻż��Ż��������Ż���ջΪ��
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
      // �����������֣��Ǿ�ֱ�����
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
  // ��ջ����ʣ��Ķ������
  while (!temp.empty()) {
    char c = temp.top();
    temp.pop();
    result.push(charToString(c));
  }
  return result;
}

// �����׺���ʽ�Ĵ�
ImproperFraction getSuffixExpressionAnswer(
    std::queue<std::string> suffixExpression) {
  std::stack<ImproperFraction> sta;
  while (!suffixExpression.empty()) {
    std::string s = suffixExpression.front();
    suffixExpression.pop();
    if (isOperator(s)) {
      // �����������������ȡ��ջ��Ԫ�ؽ��м���
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
      // �����������֣���ֱ�ӽ�ջ
      sta.push(stringToImproperFraction(s));
    }
  }
  return sta.top();
}

// ������׺���ʽ�Ĵ�
ImproperFraction getInfixExpressionAnswer(std::string s) {
  return getSuffixExpressionAnswer(transformInfixExprToSuffixExpr(s));
}

// �����ȷ�𰸻����𰸵�ID
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

// ȥ����ȡ�е����ಿ�֣�����źͻ��з�
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

// ������ű�������
void handleDivideEncoding(char *exercise) {
  for (int i = 0; i < strlen(exercise); i++) {
    if (exercise[i] < 0) {
      exercise[i] = '\xc3';
      exercise[++i] = '\xb7';
    }
  }
}

// �õ�ָ��Grade.txt�ļ���ָ��
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

// ����
void checkAnswer(FILE *exerciseFile, FILE *answerFile) {
  FILE *pFile = getPointerToGradeFile();
  int problemID = 0;
  char answer[256];
  char exercise[256];
  std::vector<int> wrongID;
  std::vector<int> correctID;
  // �𰸵��������ܲ�������Ŀ������
  while (fgets(answer, 256, answerFile)) {
    if (!fgets(exercise, 256, exerciseFile)) {
      break;
    }
    problemID++;
    // ȥ����ȡ�е����ಿ�֣�����źͻ��з�
    removeRedundantPart(answer, exercise);
    // ������ű�������
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

  // ������
  printID(pFile, const_cast<char*>("Correct"), correctID);
  printID(pFile, const_cast<char*>("Wrong"), wrongID);
  fclose(pFile);
  printf("Check answer done!\n");
}

// �ж���û�в���
bool noParameter(int argc) {
  return argc == 1;
}

// ����Ƿ���һ���Ϸ��Ĳ���
bool isALegalParameter(char *s) {
  return strlen(s) == 2 &&
    (s[1] == 'n' || s[1] == 'r' || s[1] == 'e' || s[1] == 'a');
}

// ����Ƿ���һ�����Ϸ��Ĳ������
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

// ������-n��-r�������Ƿ񲻺Ϸ�
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

// ����ļ��Ƿ񲻺Ϸ�
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

//����ת�����ַ���
void digToString(int num, std::string &str) {
  if (num / 10) {
    digToString(num / 10, str);
  }
  str = str + (char)(num % 10 + '0');
}

//����ת�����ַ���
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

// �������
std::string addbrackets(std::string s) {
  std::vector <std::pair <int, int> > op;  // ����������ȼ����Լ�λ��
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

// �����⼯
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
    printf("���� %d ����Ŀʧ��!��������r= %d ̫С,ֻ������ %d ����Ŀ\n", number, limit, exercise.size());
  } else {
    printf("���� %d ����Ŀ�ɹ�!\n", number);
  }
  freopen("Exercises.txt", "w", stdout);
  int cnt = 1;
  for (auto i: exercise) {
    printf("%d. ", cnt ++);
    for (int j = 0; j < i.size(); j++) {
      if (i[j] == '*') {
        printf("x");
      } else if (i[j] == '/' && i[j - 1] == ' ') {
        printf("��");
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
