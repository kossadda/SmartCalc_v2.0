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

#include "../include/credit_model.h"

CreditModel::CreditModel()
    : total_(3), data_(new Data{}), month_(new Current{}) {}

CreditModel::~CreditModel() {
  delete data_;
  delete month_;
}

void CreditModel::addData(long double amount, std::size_t term,
                          long double rate, const Date &date, CreditType type) {
  data_->debt_ = amount;
  data_->rate_ = rate;
  data_->date_ = date;
  data_->type_ = type;
  data_->term_ = static_cast<long double>(term);
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

  return (data_->debt_ * data_->rate_ / 100.0L) / year_days * month_part;
}

void CreditModel::calculatePayments() {
  Date::DateSize const_day{data_->date_.day()};
  Date next_month{data_->date_};
  long double annuity_cycle = data_->debt_;

  if (data_->type_ == CreditType::ANNUITY) {
    long double monthly_percent = data_->rate_ / (100.0L * Date::kYearMonths);
    month_->summary_ = roundVal(
        data_->debt_ * monthly_percent /
        (1.0L - std::pow((1.0L + monthly_percent), data_->term_ * (-1))));
  } else if (data_->type_ == CreditType::DIFFERENTIATED) {
    month_->main_ = roundVal(data_->debt_ / data_->term_);
    month_->const_main_ = month_->main_;
  }

  long double paid_percent{};
  while (data_->debt_ != 0) {
    next_month.addMonth(const_day);

    long double first_part =
        formula(data_->date_, data_->date_.daysLeftInMonth());
    long double second_part = formula(next_month, next_month.day());
    month_->percent_ = roundVal(first_part + second_part) - paid_percent;

    if (data_->type_ == CreditType::ANNUITY) {
      calculateAnnuity(paid_percent);
    } else if (data_->type_ == CreditType::DIFFERENTIATED) {
      calculateDifferentiated(paid_percent);
    }

    addMonthToTable();
    data_->date_ = next_month;

    if (table_.size() > 500 && data_->debt_ == annuity_cycle) {
      data_->debt_ = 0;
    }
  }
}

void CreditModel::calculateAnnuity(long double paid_percent) {
  static long double rest{};

  if (rest) {
    month_->percent_ += rest;
    rest = 0;
  }

  if (month_->percent_ > month_->summary_) {
    rest = month_->percent_ - month_->summary_;
    month_->percent_ = month_->summary_;
    month_->main_ = 0;
  } else {
    if (data_->debt_ > month_->summary_ ||
        data_->debt_ + month_->percent_ > month_->summary_) {
      month_->main_ = month_->summary_ - month_->percent_;
    } else {
      month_->main_ = data_->debt_;
      month_->summary_ = month_->main_ + month_->percent_;
    }
  }

  data_->debt_ -= month_->main_;

  (void)paid_percent;
}

void CreditModel::calculateDifferentiated(long double paid_percent) {
  if (data_->debt_ < month_->main_) {
    month_->main_ = data_->debt_;
  }

  month_->summary_ = month_->main_ + month_->percent_;
  data_->debt_ -= month_->main_;

  (void)paid_percent;
}

void CreditModel::addMonthToTable() {
  std::vector<long double> month{month_->summary_, month_->main_,
                                 month_->percent_, data_->debt_};
  table_.emplace_back(month);
  total_[0] += month_->summary_;
  total_[1] += month_->main_;
  total_[2] += month_->percent_;
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
