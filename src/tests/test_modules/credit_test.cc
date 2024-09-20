/**
 * @file credit_test.cc
 * @author kossadda (https://github.com/kossadda)
 * @brief 
 * @version 1.0
 * @date 2024-09-20
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "../main_test.h"

using Type = CreditModel::CreditType;

TEST(credit, annuity_1) {
  CreditModel credit;

  credit.addData(1000, 4, 5, Date{6, 7, 2021}, CreditModel::CreditType::ANNUITY);
  credit.calculatePayments();
  std::vector<long double> true_res{1010.57, 1000, 10.57};

  for(std::size_t i{}; i < true_res.size(); ++i) {
    long double res = credit.total().at(i);
    long double exp = true_res.at(i);
    EXPECT_NEAR(res, exp, 1e-3) << "\nRes : " << res << "\nTrue: " << exp << '\n';
  }
}

// TEST(credit, annuity_2) {
//   CreditModel credit;

//   credit.addData(800, 5, Date{22, 2, 2016}, 4, Type::ANNUITY);
//   credit.calculatePayments();
//   std::vector<long double> true_res{1010.57, 1000, 10.57};

//   for(std::size_t i{}; i < true_res.size(); ++i) {
//     long double res = credit.total().at(i);
//     long double exp = true_res.at(i);
//     EXPECT_NEAR(res, exp, 1e-3) << "\nRes : " << res << "\nTrue: " << exp << '\n';
//   }
// }
