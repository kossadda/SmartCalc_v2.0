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

  std::string infix = "((3.123 / (5.12 - 23.55 + 12.01 * 11.11 * (2.93 - 1.21))) + 5.56) * 7.63";
  PolishNotation pol{infix};
  std::cout << "Result: " << pol.evaluate() << std::endl;

  return 0;
}
