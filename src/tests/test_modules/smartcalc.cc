/**
 * @file smartcalc.cc
 * @author kossadda (https://github.com/kossadda)
 * @brief 
 * @version 1.0
 * @date 2024-08-16
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "../main_test.h"

TEST(smartcalc, arifmetic_1) {
  std::string infix = "(((1.123*213.5555-((217.12354))*1/2)/4/6*(5632.57-123.344)/(23.12346)/(4.213*(((653.13*(14.123*121.2345+2/(23.123+9*0.213))))/((237.12*21.8888))/(1.888+92.14)))))";
  Polish pol{infix};

  EXPECT_NEAR(pol.evaluate(), 134.97247948, 1e-7);
}

TEST(smartcalc, arifmetic_2) {
  std::string infix = "((2*3)-(4/2))";
  Polish pol{infix};

  EXPECT_NEAR(pol.evaluate(), 4.0, 1e-7);
}

// START_TEST(arifmetic_test_2) {
//   char *example = "((2*3)-(4/2))";
//   double my_result = calculation(example, 0);
//   double true_result = 4;
//   s21_test_print(example, my_result, true_result);
//   ck_assert_double_eq_tol(my_result, true_result, 1e-7);
// }