/**
 * @file main.cpp
 * @author kossadda (https://github.com/kossadda)
 * @brief Program start module
 * @version 1.0
 * @date 2024-09-08
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <QApplication>

#include "include/calculator_model.h"

int main(int argc, char *argv[]) {
  setlocale(LC_NUMERIC, "C");

  std::string infix =
      "asin(0.123*(asin(0.999)*acos(0.9995)))+(atan(34.12)*acos(0.4323))";
  Model pol{infix};

  long double exp = 1.73819952L;
  long double res = pol.evaluate();

  printf("\nRes : %.7Lf\nTrue: %.7Lf\n\n", res, exp);

  return 0;
  // QApplication a(argc, argv);
  // viewer w;
  // w.show();
  // return a.exec();
}
