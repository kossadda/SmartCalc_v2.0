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


#include "../modules/smartcalc.h"

int main() {
  setlocale(LC_NUMERIC, "C");
  
  std::string infix = "log(2.5-3) * ln(1000) / P";
  Polish pol{infix};

  long double exp = -5.72142719L;
  long double res = pol.evaluate();

  printf("\nRes : %.7Lf\nTrue: %.7Lf\n\n", res, exp);

  return 0;
}
