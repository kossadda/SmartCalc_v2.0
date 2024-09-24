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

#ifndef SRC_MODULES_INCLUDE_CREDIT_CONTROLLER_H_
#define SRC_MODULES_INCLUDE_CREDIT_CONTROLLER_H_

#include "modules/include/credit_model.h"

class CreditController {
 public:
  using CreditType = CreditModel::CreditType;
  enum class TermType { YEARS, MOHTHS };

  explicit CreditController(CreditModel *model = nullptr);
  ~CreditController();

  void addCreditData(long double amount, std::size_t term, TermType term_type, long double rate, CreditType type, std::size_t day, std::size_t month, std::size_t year);
  void calculateCredit();
  std::vector<std::vector<std::string>> &table() noexcept;
  long double total() const noexcept;

 private:
  CreditModel *model_;
  std::vector<std::vector<std::string>> table_;
  long double total_{};
};

#endif  // SRC_MODULES_INCLUDE_CREDIT_CONTROLLER_H_
