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

#ifndef SRC_INCLUDE_MODEL_CALCULATOR_MODEL_H_
#define SRC_INCLUDE_MODEL_CALCULATOR_MODEL_H_

#include <cmath>
#include <iomanip>
#include <regex>
#include <string>

namespace s21 {

class CalculatorModel {
 public:
  CalculatorModel() = default;

  void add_expression(std::string infix, long double var) noexcept;
  void to_postfix() noexcept;
  bool validate() const noexcept;
  long double evaluate();
  std::string evaluate_str();
  long double &variable() noexcept;

 private:
  std::string replaceNames(std::string infix) const noexcept;
  std::string replaceSubstr(std::string str, const char *from,
                            const char *to) const;
  int getPrecedence(char op);
  bool isFunction(char c) const noexcept;
  bool isOperator(char c) const noexcept;

  static constexpr long double kLdoubleMinVal{1.0e-15L};

  std::string infix_;
  std::string postfix_;
  std::size_t size_;
  long double variable_;
};

}  // namespace s21

#endif  // SRC_INCLUDE_MODEL_CALCULATOR_MODEL_H_
