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

#include "include/model/calculator_model.h"
#include "include/model/credit_model.h"
#include "include/model/deposit_model.h"

#define MONTHS DepositModel::TermType::MONTHS
#define DAYS DepositModel::TermType::DAYS
using Data = DepositModel::Data;
using Freq = DepositModel::Frequency;
using Type = DepositModel::DepositType;

// void testCredit(const Data &data, std::vector<long double> expected) {
//   DepositModel deposit;

//   deposit.addData(data);
//   deposit.calculatePayments();
//   std::vector<long double> result{0.0L, deposit.table().back().balance};

//   for (auto i : deposit.table()) {
//     result[0] += i.profit;
//   }

//   for (std::size_t i{}; i < expected.size(); ++i) {
//     long double res = result.at(i);
//     long double exp = expected.at(i);
//     printf("\nRes : %.2Lf\nTrue: %.2Lf\n", res, exp);
//   }
// }

void testCalculating(const std::string& infix) {
  CalculatorModel model{infix};

  std::cout << "\n" << model.evaluate() << "\n\n";

  std::cout << "\n"
            << ((model.validate()) ? "Validation success" : "Validation failed")
            << "\n\n";
}

int main() {
  std::string infix = "P";
  testCalculating(infix);
  return 0;
}
