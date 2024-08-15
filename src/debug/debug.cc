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

  std::string infix = "ln(log(2.5)*cos(0.5)/(sin(1.2) + tan(0.75))) - "
      "sqrt(ln(-2.5*log(0.75)/ln(1.2)))";
  PolishNotation pol{infix};
  // std::cout << "Result: " << pol.evaluate() << std::endl;

  return 0;
}
