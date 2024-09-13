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
      "sin(-325.5324*(((2.5432*3.432)/(-1342.5+10.5324))-sin((-44325.11123/"
      "2324.234)-1.234))/(3.234-((-2.7568*1.5234)-0.5324))";
  CalculatorModel pol{infix};

  long double exp = -0.49350345L;
  long double res = pol.evaluate();

  std::cout << ((pol.validate()) ? "\nVALID\n\n" : "\nINVALID\n\n");
  // long double exp = -65.10591506;
  // long double res = pol.evaluate();

  // printf("\nRes : %.7Lf\nTrue: %.7Lf\n\n", res, exp);

  return 0;
}
