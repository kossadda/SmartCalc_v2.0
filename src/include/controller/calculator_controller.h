/**
 * @file calculator_controller.h
 * @author kossadda (https://github.com/kossadda)
 * @brief Header file for the CalculatorController class.
 * @version 1.0
 * @date 2024-09-11
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef SRC_INCLUDE_CONTROLLER_CALCULATOR_CONTROLLER_H_
#define SRC_INCLUDE_CONTROLLER_CALCULATOR_CONTROLLER_H_

#include <string>

#include "include/model/calculator_model.h"

namespace s21 {

class CalculatorController {
 public:
  explicit CalculatorController(CalculatorModel *model = nullptr);
  ~CalculatorController();

  bool validate(std::string infix, long double var = 0) noexcept;
  void infix_to_postfix(std::string infix, long double var) noexcept;
  std::string evaluate_str();
  long double evaluate_num();
  long double &variable() noexcept;

 private:
  CalculatorModel *model_;
};

}  // namespace s21

#endif  // SRC_INCLUDE_CONTROLLER_CALCULATOR_CONTROLLER_H_
