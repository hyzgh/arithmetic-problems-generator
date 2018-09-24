/* Copyright 2018 Yuzhao Hong */

#include <bits/stdc++.h>
#include "arithmeticProblemsGenerator.h"

int main(int argc, char **argv) {
  std::map<char, bool> mode;
  if(noParameter(argc)) {
    printf("No parameter input, please check your input.\n");
    return -1;
  } else if (isIllegalParameterCombination(argc, argv, mode)) {
    printf("Illegal parameter combination, please check your input.\n");
    return -1;
  } else if (mode['n']) {
    int exerciseNumber, maxNumber;
    if (isIllegalNumber(argc, argv, exerciseNumber, maxNumber)) {
      printf("Illegal number, please check your input.\n");
      return -1;
    }
    // std::cout << maxNumber << " " << exerciseNumber << std::endl;
    questionSetGenerate(maxNumber, exerciseNumber);
  } else {
    FILE *exerciseFile, *answerFile;
    if(isIllegalFile(argc, argv, exerciseFile, answerFile)) {
      printf("Illegal file, please check your input.\n");
      return -1;
    }
    checkAnswer(exerciseFile, answerFile);
  }

  return 0;
}
