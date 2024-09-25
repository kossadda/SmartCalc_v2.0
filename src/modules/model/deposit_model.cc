/**
 * @file deposit_model.cc
 * @author kossadda (https://github.com/kossadda)
 * @brief
 * @version 1.0
 * @date 2024-09-25
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "modules/include/deposit_model.h"

DepositModel::DepositModel()
    : data_{new Data{}}, month_{new Month{}}, tax_{new Tax} {}

DepositModel::~DepositModel() {
  delete data_;
  delete month_;
  delete tax_;
}

void DepositModel::addData(const Data &data) noexcept {
  data_->amount = data.amount;
  data_->term = data.term;
  data_->term_type = data.term_type;
  data_->rate = data.rate;
  data_->tax_rate = data.tax_rate;
  data_->type = data.type;
  data_->freq = data.freq;
  data_->date = data.date;
}

void DepositModel::clear() noexcept {
  table_.clear();
  tax_table_.clear();
}

const std::vector<DepositModel::Month> &DepositModel::table() const noexcept {
  return table_;
}

const std::vector<DepositModel::Tax> &DepositModel::taxTable() const noexcept {
  return tax_table_;
}

void DepositModel::calculatePayments() noexcept {
  Date last_day{lastDepositDay()};
  Date end_period{data_->date};
  tax_->nontaxable = data_->tax_rate * kNonTaxSum / 100.0L;

  while (data_->date != last_day) {
    addPeriod(&end_period, last_day);

    calculatePeriod(end_period);

    calculateTaxes(end_period, last_day);
  }
}

Date DepositModel::lastDepositDay() const noexcept {
  Date last_day{data_->date};
  Date::DateSize init_day{data_->date.day()};

  if (data_->term_type == TermType::DAYS) {
    last_day.addDays(data_->term);
  } else {
    std::size_t term = data_->term;

    if (data_->term_type == TermType::YEARS) {
      term *= Date::kYearMonths;
    }

    for (std::size_t i{}; i < term; ++i) {
      last_day.addCreditMonth(init_day);
    }
  }

  return last_day;
}

void DepositModel::addPeriod(Date *end_period, const Date &last_day) noexcept {
  std::size_t period{static_cast<std::size_t>(data_->freq)};

  if (data_->freq == Frequency::ENDTERM) {
    *end_period = last_day;
  } else if (data_->freq == Frequency::DAY || data_->freq == Frequency::WEEK) {
    end_period->addDays(period);
  } else {
    end_period->addDepositMonth(period);
  }

  if (*end_period > last_day) {
    *end_period = last_day;
  }
}

void DepositModel::calculatePeriod(const Date &end_period) {
  month_->profit = roundVal(formula(data_->date.leapDaysBetween(end_period)));

  if (data_->type == DepositType::CAPITALIZATION) {
    month_->balance_changing = month_->profit;
    month_->receiving = 0.0L;
    month_->balance += month_->profit;
  } else {
    month_->balance_changing = 0.0L;
    month_->receiving = month_->profit;
  }

  table_.push_back(*month_);
}

void DepositModel::calculateTaxes(const Date &end_period,
                                  const Date &last_day) {
  if (data_->date.year() != end_period.year() || end_period == last_day) {
    tax_->year = data_->date.year();

    if (tax_->income > tax_->nontaxable) {
      tax_->income_deduction = tax_->income - tax_->nontaxable;
      tax_->tax_amount = roundVal(tax_->income_deduction * kNDFLRate / 100.0L);
    }

    tax_table_.push_back(*tax_);

    tax_->income = 0.0L;
    tax_->income_deduction = 0.0L;
  }

  tax_->income += month_->profit;
}

long double DepositModel::formula(
    std::pair<std::size_t, std::size_t> days) const noexcept {
  long double default_sum = (month_->balance * data_->rate / 100.0L) /
                            static_cast<long double>(Date::kYearDays) *
                            static_cast<long double>(days.first);
  long double leap_sum = (month_->balance * data_->rate / 100.0L) /
                         static_cast<long double>(Date::kLeapYearDays) *
                         static_cast<long double>(days.second);
  return default_sum + leap_sum;
}

long double DepositModel::roundVal(long double value) const noexcept {
  return std::round(value * 100.0L) / 100.0L;
}
