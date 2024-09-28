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

#include "include/controller/calculator_controller.h"

namespace s21 {
  
CalculatorController::CalculatorController(CalculatorModel* model) {
  if (model) {
    model_ = model;
  } else {
    model_ = new CalculatorModel;
  }
}

CalculatorController::~CalculatorController() { delete model_; }

void CalculatorController::infix_to_postfix(std::string infix,
                                            long double var) noexcept {
  model_->add_expression(infix, var);
  model_->to_postfix();
}

bool CalculatorController::validate(std::string infix,
                                    long double var) noexcept {
  model_->add_expression(infix, var);

  return model_->validate();
}

long double CalculatorController::evaluate_num() {
  long double result;

  try {
    result = model_->evaluate();
  } catch (const std::invalid_argument& exception) {
    result = std::nan("");
  }

  return result;
}

std::string CalculatorController::evaluate_str() {
  std::string str;

  try {
    str = model_->evaluate_str();
  } catch (const std::invalid_argument& exception) {
    str = exception.what();
  }

  return str;
}

long double& CalculatorController::variable() noexcept {
  return model_->variable();
}

}  // namespace s21
