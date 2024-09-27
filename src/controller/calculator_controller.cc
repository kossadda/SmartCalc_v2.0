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

CalculatorController::CalculatorController(CalculatorModel* model) {
  if (model) {
    model_ = model;
  } else {
    model_ = new CalculatorModel{};
  }
}

CalculatorController::~CalculatorController() { delete model_; }

void CalculatorController::infix_to_postfix(std::string infix,
                                            long double var) {
  model_->add_expression(infix, var);
  model_->to_postfix();
}

bool CalculatorController::validate(std::string infix, long double var) {
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
  std::stringstream ss;

  try {
    ss << model_->evaluate();
  } catch (const std::invalid_argument& exception) {
    ss << exception.what();
  }

  return ss.str();
}

long double& CalculatorController::variable() { return model_->variable(); }
