/**
 * @file calculator_controller.h
 * @author kossadda (https://github.com/kossadda)
 * @brief
 * @version 1.0
 * @date 2024-09-11
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef SRC_MODULES_INCLUDE_CALCULATOR_CONTROLLER_H_
#define SRC_MODULES_INCLUDE_CALCULATOR_CONTROLLER_H_

#include <string>

#include "modules/include/calculator_model.h"

class CalculatorController {
 public:
  explicit CalculatorController(CalculatorModel *model = nullptr);
  ~CalculatorController();

  bool validate(std::string infix, long double var = 0);
  void infix_to_postfix(std::string infix, long double var);
  std::string evaluate_str();
  long double evaluate_num();
  long double &variable();

 private:
  std::string replacePi(std::string infix);

  CalculatorModel *model_;
};

#endif  // SRC_MODULES_INCLUDE_CALCULATOR_CONTROLLER_H_
