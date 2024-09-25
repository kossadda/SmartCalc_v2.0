/**
 * @file deposit_controller.h
 * @author kossadda (https://github.com/kossadda)
 * @brief
 * @version 1.0
 * @date 2024-09-25
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef SRC_MODULES_INCLUDE_DEPOSIT_CONTROLLER_H_
#define SRC_MODULES_INCLUDE_DEPOSIT_CONTROLLER_H_

#include <string>
#include <vector>

#include "modules/include/deposit_model.h"

class DepositController {
 public:
  using DepositType = DepositModel::DepositType;
  enum class TermType { YEARS, MOHTHS };

  explicit DepositController(DepositModel *model = nullptr);
  ~DepositController();

  void addDepositData(long double amount, std::size_t term, TermType term_type,
                      long double rate, DepositType type, std::size_t day,
                      std::size_t month, std::size_t year);
  void calculateDeposit();
  std::vector<std::vector<std::string>> &table() noexcept;
  long double total() const noexcept;

 private:
  DepositModel *model_;
  std::vector<std::vector<std::string>> table_;
};

#endif  // SRC_MODULES_INCLUDE_DEPOSIT_CONTROLLER_H_
