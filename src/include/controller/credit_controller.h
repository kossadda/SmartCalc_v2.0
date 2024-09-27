/**
 * @file credit_controller.h
 * @author kossadda (https://github.com/kossadda)
 * @brief
 * @version 1.0
 * @date 2024-09-23
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef SRC_INCLUDE_CONTROLLER_CREDIT_CONTROLLER_H_
#define SRC_INCLUDE_CONTROLLER_CREDIT_CONTROLLER_H_

#include <string>
#include <vector>

#include "include/model/credit_model.h"

class CreditController {
 public:
  using CreditType = CreditModel::CreditType;
  using TermType = CreditModel::TermType;

  explicit CreditController(CreditModel *model = nullptr);
  ~CreditController();

  void addCreditData(long double amount, std::size_t term, TermType term_type,
                     long double rate, CreditType type, std::size_t day,
                     std::size_t month, std::size_t year);
  void calculateCredit();
  const std::vector<std::vector<std::string>> &table() const noexcept;
  long double total() const noexcept;

 private:
  CreditModel *model_;
};

#endif  // SRC_INCLUDE_CONTROLLER_CREDIT_CONTROLLER_H_
