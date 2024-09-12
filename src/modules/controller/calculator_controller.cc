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

std::string CalculatorController::infix_to_postfix(std::string infix, long double var) {
  std::string valid;

  model_.add_expression(infix, var);

  try {
    model_.to_postfix();
  } catch(const std::invalid_argument& exception) {
    valid = exception.what();
  }

  return valid;
}

bool CalculatorController::validate(std::string infix, long double var) {
  model_.add_expression(infix, var);
  return model_.validate();
}

std::string CalculatorController::evaluate() {
  std::stringstream ss;

  try {
    ss << model_.evaluate();
  } catch(const std::invalid_argument& exception) {
    ss << exception.what();
  }
  
  return ss.str();
}
