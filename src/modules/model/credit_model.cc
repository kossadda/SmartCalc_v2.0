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

#include "modules/include/credit_model.h"

CreditModel::CreditModel() : data_{new Data{}}, month_{new Month{}} {}

CreditModel::~CreditModel() {
  delete data_;
  delete month_;
}

void CreditModel::addData(const Data &data) noexcept {
  data_->amount = data.amount;
  data_->term = data.term;
  data_->rate = data.rate;
  data_->type = data.type;
  data_->date = data.date;
}

void CreditModel::clear() noexcept { table_.clear(); }

const std::vector<CreditModel::Month> &CreditModel::table() const noexcept {
  return table_;
}

long double CreditModel::roundVal(long double value) const noexcept {
  return std::round(value * 100.0L) / 100.0L;
}

long double CreditModel::formula(const Date &date,
                                 std::size_t month_part) const noexcept {
  long double year_days;

  if (date.isYearLeap(date.year())) {
    year_days = static_cast<long double>(Date::kLeapYearDays);
  } else {
    year_days = static_cast<long double>(Date::kYearDays);
  }

  return (month_->debt * data_->rate / 100.0L) / year_days * month_part;
}

void CreditModel::calculatePayments() noexcept {
  Date::DateSize const_day{data_->date.day()};
  Date next_month{data_->date};
  long double annuity_cycle{data_->amount};
  month_->debt = data_->amount;

  if (data_->type == CreditType::ANNUITY) {
    long double monthly_percent = data_->rate / (100.0L * Date::kYearMonths);
    month_->summary = roundVal(
        month_->debt * monthly_percent /
        (1.0L - std::pow((1.0L + monthly_percent), data_->term * (-1))));
  } else if (data_->type == CreditType::DIFFERENTIATED) {
    month_->main = roundVal(month_->debt / data_->term);
  }

  while (month_->debt != 0.0L) {
    next_month.addCreditMonth(const_day);

    long double first_part{formula(data_->date, data_->date.daysLeftInMonth())};
    long double second_part{formula(next_month, next_month.day())};
    month_->percent = roundVal(first_part + second_part);

    if (data_->type == CreditType::ANNUITY) {
      calculateAnnuity();
    } else if (data_->type == CreditType::DIFFERENTIATED) {
      calculateDifferentiated();
    }

    if ((table_.size() > 500 && month_->debt == annuity_cycle) ||
        month_->debt < 1.0e-3) {
      month_->debt = 0.0L;
    }

    data_->date = next_month;
    month_->payment_date = data_->date;
    table_.push_back(*month_);
  }
}

void CreditModel::calculateAnnuity() noexcept {
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
    if (month_->debt > month_->summary ||
        month_->debt + month_->percent > month_->summary) {
      month_->main = month_->summary - month_->percent;
    } else {
      month_->main = month_->debt;
      month_->summary = month_->main + month_->percent;
    }
  }

  month_->debt -= month_->main;
}

void CreditModel::calculateDifferentiated() noexcept {
  if (month_->debt < month_->main) {
    month_->main = month_->debt;
  }

  month_->summary = month_->main + month_->percent;
  month_->debt -= month_->main;
}
