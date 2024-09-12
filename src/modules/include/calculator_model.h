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

#ifndef SRC_MODULES_INCLUDE_CALCULATOR_MODEL_H_
#define SRC_MODULES_INCLUDE_CALCULATOR_MODEL_H_

#include <cctype>
#include <cmath>
#include <iostream>
#include <regex>
#include <sstream>
#include <stack>
#include <string>

class CalculatorModel {
 public:
  CalculatorModel() = default;
  explicit CalculatorModel(std::string infix, long double var = 0);

  void add_expression(std::string infix, long double var);
  void to_postfix();
  bool validate();
  long double evaluate();

 private:
  std::string replaceNames(std::string infix);
  std::string replaceSubstr(std::string str, const char *from, const char *to);
  int getPrecedence(char op);
  bool isFunction(char c);
  bool isOperator(char c);
  void infixToPostfix();

  static constexpr long double kLdoubleMinVal{1.0e-15L}; 

  std::string infix_;
  std::string postfix_;
  std::size_t size_;
  long double variable_;
};

#endif  // SRC_MODULES_INCLUDE_CALCULATOR_MODEL_H_
