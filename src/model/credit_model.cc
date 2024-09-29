/**
 * @file credit_model.cc
 * @author kossadda (https://github.com/kossadda)
 * @brief
 * @version 1.0
 * @date 2024-09-20
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "include/model/credit_model.h"

namespace s21 {

CreditModel::CreditModel() : BaseModel{} { data_ = new Data; }

CreditModel::~CreditModel() { delete data_; }

void CreditModel::addData(const Data &data) noexcept {
  *data_ = data;
  data_->rate /= 100.0L;

  if (data_->term_type == TermType::YEARS) {
    data_->term *= Date::kYearMonths;
  }
}

void CreditModel::clear() noexcept { table_.clear(); }

void CreditModel::calculatePayments() noexcept {
  Date::DateSize const_day{data_->date.day()};
  long double annuity_cycle{data_->amount};
  month_->current = data_->date;
  month_->payment_date = data_->date;
  month_->balance = data_->amount;

  if (data_->type == Type::FIRST) {
    long double monthly_percent = data_->rate / Date::kYearMonths;
    month_->summary =
        roundVal(month_->balance * monthly_percent /
                 (1.0L - std::pow((1.0L + monthly_percent), -data_->term)));
  } else {
    month_->main = roundVal(month_->balance / data_->term);
  }

  while (month_->balance) {
    month_->payment_date.addCreditMonth(const_day);

    calculatePeriod();

    if ((table_.size() > 500 && month_->balance == annuity_cycle) ||
        month_->balance < 1.0e-3) {
      month_->balance = 0.0L;
    }

    month_->current = month_->payment_date;
    monthToTable();
  }
}

void CreditModel::calculatePeriod() noexcept {
  month_->percent = roundVal(formula(month_->current, month_->payment_date));

  if (data_->type == Type::FIRST) {
    static long double rest{};

    if (rest) {
      month_->percent += rest;
      rest = 0.0L;
    }

    if (month_->percent > month_->summary) {
      rest = month_->percent - month_->summary;
      month_->percent = month_->summary;
      month_->main = 0.0L;
    } else {
      if (month_->balance > month_->summary ||
          month_->balance + month_->percent > month_->summary) {
        month_->main = month_->summary - month_->percent;
      } else {
        month_->main = month_->balance;
        month_->summary = month_->main + month_->percent;
      }
    }
  } else {
    if (month_->balance < month_->main) {
      month_->main = month_->balance;
    }

    month_->summary = month_->main + month_->percent;
  }

  month_->balance -= month_->main;
}

std::vector<std::string> CreditModel::totalTable() const noexcept {
  std::vector<std::string> total;
  long double percent{};

  for (auto i : table_) percent += std::stold(i[1]);

  auto profit{toStr(percent)};
  auto debt{toStr(data_->amount)};
  auto ttotal{toStr(data_->amount + percent)};

  total.emplace_back(std::string("Interest paid\n") + profit);
  total.emplace_back(std::string("Debt paid\n") + debt);
  total.emplace_back(std::string("Total paid\n") + ttotal);

  return total;
}

}  // namespace s21
