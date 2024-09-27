/**
 * @file credit_controller.cc
 * @author kossadda (https://github.com/kossadda)
 * @brief
 * @version 1.0
 * @date 2024-09-23
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "include/controller/credit_controller.h"

CreditController::CreditController(CreditModel* model) {
  if (model) {
    model_ = model;
  } else {
    model_ = new CreditModel{};
  }
}

CreditController::~CreditController() { delete model_; }

void CreditController::addCreditData(long double amount, std::size_t term,
                                     TermType term_type, long double rate,
                                     CreditType type, std::size_t day,
                                     std::size_t month, std::size_t year) {
  if (term_type == TermType::YEARS) {
    term *= Date::kYearMonths;
  }

  CreditModel::Data data{amount, static_cast<long double>(term), rate, type,
                         Date(day, month, year)};

  model_->addData(data);
  model_->clear();
}

void CreditController::calculateCredit() { model_->calculatePayments(); }

const std::vector<std::vector<std::string>>& CreditController::table()
    const noexcept {
  return model_->table();
}
