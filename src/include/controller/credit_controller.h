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

namespace s21 {

class CreditController {
 public:
  using Type = CreditModel::Type;
  using TermType = CreditModel::TermType;

  explicit CreditController(CreditModel *model = nullptr);
  ~CreditController();

  void addCreditData(long double amount, std::size_t term, TermType term_type,
                     long double rate, Type type, std::size_t day,
                     std::size_t month, std::size_t year) noexcept;
  void calculateCredit() noexcept;
  const std::vector<std::vector<std::string>> &table() const noexcept;
  std::vector<std::string> totalTable() const noexcept;

 private:
  CreditModel *model_;
};

}  // namespace s21

#endif  // SRC_INCLUDE_CONTROLLER_CREDIT_CONTROLLER_H_
