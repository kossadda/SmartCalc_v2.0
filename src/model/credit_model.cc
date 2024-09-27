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

  if (data.term_type == TermType::YEARS) {
    data_->term *= Date::kYearMonths;
  }
}

void CreditModel::clear() noexcept {
  table_.clear();
  total_ = 0.0L;
}

void CreditModel::calculatePayments() noexcept {
  Date::DateSize const_day{data_->date.day()};
  long double annuity_cycle{data_->amount};
  month_->current = data_->date;
  month_->payment_date = data_->date;
  month_->debt = data_->amount;

  if (data_->type == CreditType::ANNUITY) {
    long double monthly_percent = data_->rate / (100.0L * Date::kYearMonths);
    month_->summary = roundVal(
        month_->debt * monthly_percent /
        (1.0L - std::pow((1.0L + monthly_percent), data_->term * (-1))));
  } else if (data_->type == CreditType::DIFFERENTIATED) {
    month_->main = roundVal(month_->debt / data_->term);
  }

  while (month_->debt) {
    month_->payment_date.addCreditMonth(const_day);

    long double first_part{
        formula(month_->current, month_->current.daysLeftInMonth())};
    long double second_part{
        formula(month_->payment_date, month_->payment_date.day())};
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

    month_->current = month_->payment_date;
    table_.push_back(monthToString());
    total_ += month_->percent;
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

long double CreditModel::roundVal(long double value) const noexcept {
  return std::lround(value * 100.0L + 1.0e-8L) / 100.0L;
}

std::string CreditModel::toStr(long double val) const noexcept {
  std::ostringstream stream;

  stream << std::fixed << std::setprecision(2) << val;

  return stream.str();
}

std::vector<std::string> CreditModel::monthToString() const noexcept {
  std::vector<std::string> str_month;

  str_month.emplace_back(month_->payment_date.currentDate());
  str_month.emplace_back(toStr(month_->summary));
  str_month.emplace_back(toStr(month_->main));
  str_month.emplace_back(toStr(month_->percent));
  str_month.emplace_back(toStr(month_->debt));

  return str_month;
}

std::vector<std::string> CreditModel::totalTable() const noexcept {
  std::vector<std::string> total;

  auto profit{toStr(total_)};
  auto debt{toStr(data_->amount)};
  auto ttotal{toStr(data_->amount + total_)};

  total.emplace_back(std::string("Interest paid\n") + profit);
  total.emplace_back(std::string("Debt paid\n") + debt);
  total.emplace_back(std::string("Total paid\n") + ttotal);

  return total;
}

const std::vector<std::vector<std::string>> &CreditModel::table()
    const noexcept {
  return table_;
}
