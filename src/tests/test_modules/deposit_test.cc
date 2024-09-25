/**
 * @file deposit_test.cc
 * @author kossadda (https://github.com/kossadda)
 * @brief 
 * @version 1.0
 * @date 2024-09-25
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "../main_test.h"

#define MONTHS DepositModel::TermType::MONTHS
#define DAYS DepositModel::TermType::DAYS
using Data = DepositModel::Data;
using Freq = DepositModel::Frequency;
using Type = DepositModel::DepositType;

void testCredit(const Data &data, std::vector<long double> expected) {
  DepositModel deposit;

  deposit.addData(data);
  deposit.calculatePayments();
  std::vector<long double> result{0.0L, deposit.table().back().balance};
  
  for(auto i : deposit.table()) {
    result[0] += i.profit;
  }

  for (std::size_t i{}; i < expected.size(); ++i) {
    long double res = result.at(i);
    long double exp = expected.at(i);
    EXPECT_NEAR(res, exp, 1e-3) << "\nRes : " << res << "\nTrue: " << exp << '\n';
  }
}

TEST(deposit, by_day_1) {
  Data data{10000, 12, MONTHS, 15, 16, Type::DEFAULT, Freq::DAY, Date{1, 1, 2020}};
  testCredit(data, {1500.61, 10000});
}
