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

#include "modules/include/credit_controller.h"

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
#include <iomanip>

void CreditController::calculateCredit() {
  model_->calculatePayments();

  for (const auto& i : model_->table()) {
    std::vector<std::string> str_month;

    std::ostringstream summary_stream, main_stream, percent_stream, debt_stream;
    summary_stream << std::fixed << std::setprecision(2) << i.summary;
    main_stream << std::fixed << std::setprecision(2) << i.main;
    percent_stream << std::fixed << std::setprecision(2) << i.percent;
    debt_stream << std::fixed << std::setprecision(2) << i.debt;

    str_month.push_back(i.payment_date.currentDate());
    str_month.push_back(summary_stream.str());
    str_month.push_back(main_stream.str());
    str_month.push_back(percent_stream.str());
    str_month.push_back(debt_stream.str());

    table_.push_back(str_month);
    total_ += i.percent;
  }
}

std::vector<std::vector<std::string>>& CreditController::table() noexcept {
  return table_;
}
