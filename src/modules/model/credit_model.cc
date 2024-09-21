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

CreditModel::CreditModel()
    : data_(new Data{}), month_(new Current{}), total_(3) {}

CreditModel::~CreditModel() {
  delete data_;
  delete month_;
}

void CreditModel::addData(Data &data, const std::vector<EarlyPayment> &early) {
  data_->date = data.date;
  data_->debt = data.debt;
  data_->rate = data.rate;
  data_->term = data.term;
  data_->type = data.type;
  early_ = early;
}

long double CreditModel::roundVal(long double value) {
  return std::round(value * 100.0L) / 100.0L;
}

long double CreditModel::formula(Date &date, std::size_t month_part) {
  std::size_t year_days;

  if (date.isYearLeap(date.year())) {
    year_days = Date::kLeapYearDays;
  } else {
    year_days = Date::kYearDays;
  }

  return (data_->debt * data_->rate / 100.0L) / year_days * month_part;
}

void CreditModel::calculatePayments() {
  Date::DateSize const_day{data_->date.day()};
  Date next_month{data_->date};
  long double annuity_cycle = data_->debt;

  if (data_->type == CreditType::ANNUITY) {
    long double monthly_percent = data_->rate / (100.0L * Date::kYearMonths);
    month_->summary = roundVal(
        data_->debt * monthly_percent /
        (1.0L - std::pow((1.0L + monthly_percent), data_->term * (-1))));
  } else if (data_->type == CreditType::DIFFERENTIATED) {
    month_->main = roundVal(data_->debt / data_->term);
    month_->const_main = month_->main;
  }

  long double paid_percent{};
  while (data_->debt != 0) {
    next_month.addMonth(const_day);

    long double first_part =
        formula(data_->date, data_->date.daysLeftInMonth());
    long double second_part = formula(next_month, next_month.day());
    month_->percent = roundVal(first_part + second_part) - paid_percent;

    if (data_->type == CreditType::ANNUITY) {
      calculateAnnuity(paid_percent);
    } else if (data_->type == CreditType::DIFFERENTIATED) {
      calculateDifferentiated(paid_percent);
    }

    addMonthToTable();
    data_->date = next_month;

    if (table_.size() > 500 && data_->debt == annuity_cycle) {
      data_->debt = 0;
    }
  }
}

void CreditModel::calculateAnnuity(long double paid_percent) {
  static long double rest{};

  if (rest) {
    month_->percent += rest;
    rest = 0;
  }

  if (month_->percent > month_->summary) {
    rest = month_->percent - month_->summary;
    month_->percent = month_->summary;
    month_->main = 0;
  } else {
    if (data_->debt > month_->summary ||
        data_->debt + month_->percent > month_->summary) {
      month_->main = month_->summary - month_->percent;
    } else {
      month_->main = data_->debt;
      month_->summary = month_->main + month_->percent;
    }
  }

  data_->debt -= month_->main;

  (void)paid_percent;
}

void CreditModel::calculateDifferentiated(long double paid_percent) {
  if (data_->debt < month_->main) {
    month_->main = data_->debt;
  }

  month_->summary = month_->main + month_->percent;
  data_->debt -= month_->main;

  (void)paid_percent;
}

void CreditModel::addMonthToTable() {
  std::vector<long double> month{month_->summary, month_->main, month_->percent,
                                 data_->debt};
  table_.emplace_back(month);
  total_[0] += month_->summary;
  total_[1] += month_->main;
  total_[2] += month_->percent;
}

void CreditModel::printTable() const {
  for (auto month : table_) {
    for (auto i : month) {
      std::cout << i << " ";
    }
    std::cout << "\n";
  }
}

std::vector<long double> &CreditModel::total() { return total_; }

std::vector<std::vector<long double>> &CreditModel::table() { return table_; }
