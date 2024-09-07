/**
 * @file calculator_model.h
 * @author kossadda (https://github.com/kossadda)
 * @brief
 * @version 1.0
 * @date 2024-08-13
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef SRC_MODULES_CALCULATOR_INCLUDE_CALCULATOR_MODEL_H_
#define SRC_MODULES_CALCULATOR_INCLUDE_CALCULATOR_MODEL_H_

#include <cctype>
#include <cmath>
#include <iostream>
#include <regex>
#include <sstream>
#include <stack>
#include <string>

class Model {
 public:
  explicit Model(std::string infix, long double var = 0);

  long double evaluate();

 private:
  void infixToPostfix();
  int getPrecedence(char op);
  bool isOperator(char c);
  bool isFunction(char c);
  bool validate();
  void replaceSubStr(std::string from, std::string to);

  std::string infix_;
  std::string postfix_;
  std::size_t size_;
  long double variable_;
};

#endif  // SRC_MODULES_CALCULATOR_INCLUDE_CALCULATOR_MODEL_H_
