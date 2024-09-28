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
using Type = DepositModel::Type;

void testDeposit(const Data& data, Freq freq,
                 std::vector<long double> expected) {
  DepositModel deposit;

  deposit.addData(data, 16, freq);
  deposit.calculatePayments();
  std::vector<long double> result{0.0L, std::stold(deposit.table().back()[4])};

  for (auto i : deposit.table()) {
    result[0] += std::stold(i[1]);
  }

  for (std::size_t i{}; i < expected.size(); ++i) {
    long double res = result.at(i);
    long double exp = expected.at(i);
    printf("\nRes : %.2Lf\nTrue: %.2Lf\n", res, exp);
  }
}

// #define ANN CreditModel::CreditType::ANNUITY
// #define DIF CreditModel::CreditType::DIFFERENTIATED
// #define MONTHS CreditModel::TermType::MOHTHS
// using Data = CreditModel::Data;

// void testCredit(const Data &data, std::vector<long double> expected) {
//   CreditModel credit;

//   credit.addData(data);
//   credit.calculatePayments();
//   std::vector<std::string> result{credit.totalTable()};

//   for(std::string &i : result) {
//     while(i[0] != '\n') {
//       i.erase(i.begin());
//     }
//     i.erase(i.begin());
//   }

//   for (std::size_t i{}; i < expected.size(); ++i) {
//     long double res = std::stold(result[i]);
//     long double exp = expected[i];
//     printf("\nRes : %.2Lf\nTrue: %.2Lf\n", res, exp);
//   }
// }

void testCalculating(const std::string& infix) {
  CalculatorModel model;

  model.add_expression(infix, 0);
  model.to_postfix();

  std::cout << "\n" << model.evaluate_str() << "\n\n";

  std::cout << "\n"
            << ((model.validate()) ? "Validation success" : "Validation failed")
            << "\n\n";
}

int main() {
  std::string infix = "88.3/8";
  testCalculating(infix);
}
