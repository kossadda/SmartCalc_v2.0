/**
 * @file main_test.cpp
 * @author kossadda (https://github.com/kossadda)
 * @brief Main module that runs testing
 * @version 1.0
 * @date 2024-08-16
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "tests/main_test.h"

/**
 * @brief Main running testing
 *
 * @param[in] argc number of arguments supplied
 * @param[in] argv array of arguments
 * @return int - overall test result
 */
int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
