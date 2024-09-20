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

#include "./include/credit_model.h"

int main() {
  setlocale(LC_NUMERIC, "C");

  long double amount = 100000;
  long double rate = 10.2;
  Date date{20, 9, 2024};
  CreditModel::CreditType type = CreditModel::CreditType::DIFFERENTIATED;
  std::size_t term = 12;

  CreditModel model;

  model.addData(amount, rate, date, term, type);

  model.calculatePayments();

  model.printTable();

  return 0;
}
