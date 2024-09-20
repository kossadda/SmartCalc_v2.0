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

  CreditModel credit;

  credit.addData(800, 12, 3, Date{22, 2, 2016}, CreditModel::CreditType::ANNUITY);
  credit.calculatePayments();
  std::vector<long double> true_res{812.99, 800, 12.99};

  credit.printTable();
  // for(std::size_t i{}; i < true_res.size(); ++i) {
  //   long double res = credit.total().at(i);
  //   long double exp = true_res.at(i);
  //   std::cout << res << ':' << exp << '\n';
  //   // EXPECT_NEAR(res, exp, 1e-3) << "\nRes : " << res << "\nTrue: " << exp << '\n';
  // }

  return 0;
}
