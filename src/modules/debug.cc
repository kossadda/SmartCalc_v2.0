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
      "asin(0.123*(asin(0.999)*acos(0.9995)))+(atan(34.12)*acos(0.4323))";
  Model pol{infix};

  long double exp = 1.73819952L;
  long double res = pol.evaluate();

  printf("\nRes : %.7Lf\nTrue: %.7Lf\n\n", res, exp);

  return 0;
}
