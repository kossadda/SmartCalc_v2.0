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
  table_.clear();
  total_ = 0.0L;
}

void CreditController::calculateCredit() {
  model_->calculatePayments();

  for (const auto& i : model_->table()) {
    std::vector<std::string> str_month;

    std::ostringstream ssummary, smain, spercent, sdebt;
    ssummary << std::fixed << std::setprecision(2) << i.summary;
    smain << std::fixed << std::setprecision(2) << i.main;
    spercent << std::fixed << std::setprecision(2) << i.percent;
    sdebt << std::fixed << std::setprecision(2) << i.debt;

    str_month.push_back(i.payment_date.currentDate());
    str_month.push_back(ssummary.str());
    str_month.push_back(smain.str());
    str_month.push_back(spercent.str());
    str_month.push_back(sdebt.str());

    table_.push_back(str_month);
    total_ += i.percent;
  }
}

std::vector<std::vector<std::string>>& CreditController::table() noexcept {
  return table_;
}
