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

#include <iostream>
#include <string>
#include <stack>
#include <sstream>
#include <cctype>

class PolishNotation {
 public:
  PolishNotation(std::string infix);

  double evaluate();
  
 private:
  void infixToPostfix();
  int getPrecedence(char op);
  bool isOperator(char c);
  bool validate();

  static constexpr std::string_view valid = "()^+-*/ modsinctaqrlgePx.0123456789";
  // static constexpr std::string_view 

  std::string infix_;
  std::string postfix_;
  std::size_t size_;
};

#endif // NOTATION_H_
