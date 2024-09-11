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
  model_.add_infix(infix, var);
}

bool CalculatorController::validate(std::string infix, long double var) {
  return model_.validate(infix, var);
}

std::string CalculatorController::evaluate() {
  std::stringstream ss;
  ss << model_.evaluate();

  return ss.str();
}
