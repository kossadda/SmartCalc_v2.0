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

CreditModel::CreditModel() : total(3) {}
CreditModel::~CreditModel() {
  delete date_;
}

void CreditModel::addData(long double amount, long double rate, Date &date,
                         std::size_t term, CreditType type) {
  debt_ = amount;
  rate_ = rate;
  date_ = new Date{date};
  type_ = type;
  term_ = static_cast<long double>(term);
}

long double CreditModel::roundVal(long double value) {
  return std::round(value * 100.0L) / 100.0L;
}

long double CreditModel::formula(Date &date, std::size_t month_part) {
  std::size_t year_days;

  if(date.isYearLeap(date.year())) {
    year_days = Date::kLeapYearDays;
  } else {
    year_days = Date::kYearDays;
  }

  return (debt_ * rate_ / 100.0L) / year_days * month_part;
}

void CreditModel::calculatePayments() {
  Date::DateSize const_day{date_->day()};
  Date next_month{*date_};
  long double annuity_cycle = debt_;

  if (type_ == CreditType::ANNUITY) {
    long double monthly_percent = rate_ / (100.0L * Date::kYearMonths);
    monthly_ = roundVal(debt_ * monthly_percent / (1.0L - std::pow((1.0L + monthly_percent), term_ * (-1))));
  } else if (type_ == CreditType::DIFFERENTIATED) {
    main_ = roundVal(debt_ / term_);
    const_main_ = main_;
  }

  long double paid_percent{};
  while (debt_ != 0) {
    next_month.addMonth(const_day);

    long double first_part = formula(*date_, date_->daysLeftInMonth());
    long double second_part = formula(next_month, next_month.day());
    percent_ = roundVal(first_part + second_part) - paid_percent;

    if (type_ == CreditType::ANNUITY) {
      calculateAnnuity(paid_percent);
    } else if (type_ == CreditType::DIFFERENTIATED) {
      calculateDifferentiated(paid_percent);
    }

    addMonthToTable();
    *date_ = next_month;

    if (table.size() > 500 && debt_ == annuity_cycle) {
      debt_ = 0;
    }
  }
}

void CreditModel::calculateAnnuity(long double paid_percent) {
  static long double rest{};

  if (rest) {
    percent_ += rest;
    rest = 0;
  }

  if (percent_ > monthly_) {
    rest = percent_ - monthly_;
    percent_ = monthly_;
    main_ = 0;
  } else {
    if (debt_ > monthly_ || debt_ + percent_ > monthly_) {
      main_ = monthly_ - percent_;
    } else {
      main_ = debt_;
      monthly_ = main_ + percent_;
    }
  }

  debt_ -= main_;

  (void)paid_percent;
}

void CreditModel::calculateDifferentiated(long double paid_percent) {
  if(debt_ < main_) {
    main_ = debt_;
  }

  monthly_ = main_ + percent_;
  debt_ -= main_;

  (void)paid_percent;
}

void CreditModel::addMonthToTable() {
  std::vector<long double> month{monthly_, main_, percent_, debt_};
  table.emplace_back(month);
  total[0] += monthly_;
  total[1] += main_;
  total[2] += percent_;
}

void CreditModel::printTable() const {
  for(auto month : table) {
    for(auto i : month) {
      std::cout << i << " ";
    }
    std::cout << "\n"; 
  }
}
