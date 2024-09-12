/**
 * @file debug.cc
 * @author kossadda (https://github.com/kossadda)
 * @brief Separate module for manual testing
 * @version 1.0
 * @date 2024-04-18
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "include/calculator_model.h"

int main() {
  setlocale(LC_NUMERIC, "C");

  std::string infix =
      "x(((ln(cos(1.5*atan(1)))/(log(x*sqrt(x))))+log((tan(1)-asin(0.25))/"
      "(ln(x)+sqrt(x)))))";
  CalculatorModel pol{infix, 50.0L};

  long double exp = -65.10591506;
  long double res = pol.evaluate();

  printf("\nRes : %.7Lf\nTrue: %.7Lf\n\n", res, exp);

  return 0;
}
