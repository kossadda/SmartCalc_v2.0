/**
 * @file notation.h
 * @author kossadda (https://github.com/kossadda)
 * @brief
 * @version 1.0
 * @date 2024-08-13
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef NOTATION_H_
#define NOTATION_H_

#include <cctype>
#include <cmath>
#include <iostream>
#include <regex>
#include <sstream>
#include <stack>
#include <string>

class Polish {
 public:
  Polish(std::string infix);

  long double evaluate();

 private:
  void infixToPostfix();
  int getPrecedence(char op);
  bool isOperator(char c);
  bool isFunction(char c);
  bool validate();

  void replaceSubStr(std::string from, std::string to);

  static inline const std::string kValidCh = "()^+-*/umsctSCTQLlPxe1234567890.";

  std::string infix_;
  std::string postfix_;
  std::size_t size_;
};

#endif  // NOTATION_H_
