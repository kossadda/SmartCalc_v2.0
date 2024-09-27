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

#ifndef SRC_INCLUDE_CONTROLLER_DEPOSIT_CONTROLLER_H_
#define SRC_INCLUDE_CONTROLLER_DEPOSIT_CONTROLLER_H_

#include <string>
#include <vector>

#include "include/model/deposit_model.h"

class DepositController {
 public:
  using DepositType = DepositModel::DepositType;
  using Frequency = DepositModel::Frequency;
  using TermType = DepositModel::TermType;

  explicit DepositController(DepositModel *model = nullptr);
  ~DepositController();

  void addDepositData(long double amount, std::size_t term, TermType term_type,
                      long double rate, long double tax_rate, DepositType type,
                      Frequency freq, std::size_t day, std::size_t month,
                      std::size_t year);
  void calculateDeposit();
  const std::vector<std::vector<std::string>> &table() const noexcept;
  const std::vector<std::vector<std::string>> &taxTable() const noexcept;
  std::vector<std::string> totalTable() const noexcept;

 private:
  DepositModel *model_;
};

#endif  // SRC_INCLUDE_CONTROLLER_DEPOSIT_CONTROLLER_H_
