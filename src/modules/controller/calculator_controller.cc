/**
 * @file calculator_controller.cc
 * @author kossadda (https://github.com/kossadda)
 * @brief
 * @version 1.0
 * @date 2024-09-11
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "modules/include/calculator_controller.h"

void CalculatorController::infix_to_postfix(std::string infix,
                                            long double var) {
  model_.add_expression(replacePi(infix), var);
  model_.to_postfix();
}

bool CalculatorController::validate(std::string infix, long double var) {
  model_.add_expression(replacePi(infix), var);

  return model_.validate();
}

long double CalculatorController::evaluate_num() {
  long double result;

  try {
    result = model_.evaluate();
  } catch (const std::invalid_argument& exception) {
    result = std::nan("");
  }

  return result;
}

std::string CalculatorController::evaluate_str() {
  std::stringstream ss;

  try {
    ss << model_.evaluate();
  } catch (const std::invalid_argument& exception) {
    ss << exception.what();
  }

  return ss.str();
}

std::string CalculatorController::replacePi(std::string infix) {
  std::string pi{"π"};
  std::string replacement{"P"};
  size_t pos{};

  while ((pos = infix.find(pi, pos)) != std::string::npos) {
    infix.replace(pos, pi.length(), replacement);
    pos += replacement.length();
  }

  return infix;
}
