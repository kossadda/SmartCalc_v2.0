/**
 * @file credit_controller.cc
 * @author kossadda (https://github.com/kossadda)
 * @brief Implementation of the CreditController class.
 * @version 1.0
 * @date 2024-09-23
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "include/controller/credit_controller.h"

namespace s21 {

CreditController::CreditController(CreditModel* model) {
  if (model) {
    model_ = model;
  } else {
    model_ = new CreditModel;
  }
}

CreditController::~CreditController() { delete model_; }

void CreditController::addCreditData(long double amount, std::size_t term,
                                     TermType term_type, long double rate,
                                     Type type, std::size_t day,
                                     std::size_t month,
                                     std::size_t year) noexcept {
  CreditModel::Data data(amount, term, term_type, rate, type,
                         Date(day, month, year));

  model_->addData(data);
  model_->clear();
}

void CreditController::calculateCredit() noexcept {
  model_->calculatePayments();
}

const std::vector<std::vector<std::string>>& CreditController::table()
    const noexcept {
  return model_->table();
}

std::vector<std::string> CreditController::totalTable() const noexcept {
  return model_->totalTable();
}

}  // namespace s21
