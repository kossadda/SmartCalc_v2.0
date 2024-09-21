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

  credit.addData(9862.12, 7, 13.77, Date{9, 9, 2000},
                 CreditModel::CreditType::ANNUITY);
  credit.calculatePayments();
  std::vector<long double> true_res{10318.04, 9862.12, 455.92};

  // credit.printTable();

  for (std::size_t i{}; i < true_res.size(); ++i) {
    long double res = credit.total().at(i);
    long double exp = true_res.at(i);
    std::cout << res << ':' << exp << '\n';
    // EXPECT_NEAR(res, exp, 1e-3) << "\nRes : " << res << "\nTrue: " << exp
    // << '\n';
  }

  return 0;
}
