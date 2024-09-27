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

#include "include/model/deposit_model.h"

DepositModel::DepositModel()
    : data_{new Data{}}, month_{new Month{}}, tax_{new Tax} {}

DepositModel::~DepositModel() {
  delete data_;
  delete month_;
  delete tax_;
}

void DepositModel::addData(const Data &data) noexcept { *data_ = data; }

void DepositModel::clear() noexcept {
  table_.clear();
  tax_table_.clear();
  *tax_ = Tax{};
}

void DepositModel::calculatePayments() noexcept {
  month_->current = data_->date;
  month_->accrual_date = data_->date;
  month_->balance = data_->amount;
  tax_->nontaxable = data_->tax_rate * kNonTaxSum / 100.0L;
  Date last_day{lastDepositDay()};

  while (month_->current != last_day) {
    addPeriod(last_day);

    calculatePeriod();

    calculateTaxes(last_day);

    month_->current = month_->accrual_date;
  }
}

Date DepositModel::lastDepositDay() const noexcept {
  Date last_day{month_->current};
  Date::DateSize init_day{month_->current.day()};

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

void DepositModel::addPeriod(const Date &last_day) noexcept {
  std::size_t period{static_cast<std::size_t>(data_->freq)};

  if (data_->freq == Frequency::ENDTERM) {
    month_->accrual_date = last_day;
  } else if (data_->freq == Frequency::DAY) {
    month_->accrual_date.addDays(1);
  } else if (data_->freq == Frequency::WEEK) {
    month_->accrual_date.addDays(7);
  } else {
    month_->accrual_date.addDepositMonth(period);
  }

  if (month_->accrual_date > last_day) {
    month_->accrual_date = last_day;
  }
}

void DepositModel::calculatePeriod() {
  month_->profit =
      roundVal(formula(month_->current.leapDaysBetween(month_->accrual_date)));

  if (data_->type == DepositType::CAPITALIZATION) {
    month_->balance_changing = month_->profit;
    month_->receiving = 0.0L;
    month_->balance += roundVal(month_->profit);
  } else {
    month_->balance_changing = 0.0L;
    month_->receiving = month_->profit;
  }

  tax_->total_profit_ += month_->profit;
  table_.push_back(monthToString());
}

void DepositModel::calculateTaxes(const Date &last_day) {
  if (month_->current.year() != month_->accrual_date.year() ||
      month_->accrual_date == last_day) {
    if (month_->accrual_date == last_day) {
      tax_->income += month_->profit;
    }
    tax_->year = month_->current.year();

    if (tax_->income > tax_->nontaxable) {
      tax_->income_deduction = tax_->income - tax_->nontaxable;
      tax_->tax_amount = roundVal(tax_->income_deduction * kNDFLRate / 100.0L);
      tax_->total_tax_ += tax_->tax_amount;
    }

    tax_table_.push_back(taxToString());

    tax_->income = 0.0L;
    tax_->income_deduction = 0.0L;
  }

  if (month_->accrual_date != last_day) {
    tax_->income += month_->profit;
  } else {
    tax_->income -= month_->profit;
  }
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

std::string DepositModel::toStr(long double val) const noexcept {
  std::ostringstream stream;

  stream << std::fixed << std::setprecision(2) << val;

  return stream.str();
}

std::vector<std::string> DepositModel::monthToString() const noexcept {
  std::vector<std::string> str_month;

  str_month.emplace_back(month_->accrual_date.currentDate());
  str_month.emplace_back(toStr(month_->profit));
  str_month.emplace_back(toStr(month_->balance_changing));
  str_month.emplace_back(toStr(month_->receiving));
  str_month.emplace_back(toStr(month_->balance));

  return str_month;
}

std::vector<std::string> DepositModel::taxToString() const noexcept {
  std::vector<std::string> str_year;

  str_year.emplace_back(std::to_string(tax_->year));
  str_year.emplace_back(toStr(tax_->income));
  str_year.emplace_back(toStr(tax_->nontaxable));
  str_year.emplace_back(toStr(tax_->income_deduction));
  str_year.emplace_back(toStr(tax_->tax_amount));
  str_year.emplace_back("Pay by 01.12." + std::to_string(tax_->year + 1));

  return str_year;
}

std::vector<std::string> DepositModel::totalTable() const noexcept {
  std::vector<std::string> total_str;
  auto eff_rate{toStr(tax_->total_profit_ / data_->amount * Date::kYearDays /
                      (month_->accrual_date - data_->date) * 100.0L)};
  auto tbalance{toStr((data_->type == DepositType::CAPITALIZATION)
                          ? month_->balance
                          : data_->amount + tax_->total_profit_)};
  auto tax_prof{toStr(tax_->total_profit_ - tax_->total_tax_)};
  auto tprofit{toStr(tax_->total_profit_)};
  auto ttax{toStr(tax_->total_tax_)};
  auto balance{toStr(month_->balance)};

  total_str.emplace_back(std::string("Profit\n") + tprofit);
  total_str.emplace_back(std::string("Total tax\n") + ttax);
  total_str.emplace_back(std::string("Profit with tax\n") + tax_prof);
  total_str.emplace_back(std::string("Effective rate\n") + eff_rate);
  total_str.emplace_back(std::string("Total balance\n") + tbalance);
  total_str.emplace_back(std::string("Balance\n") + balance);

  return total_str;
}

const std::vector<std::vector<std::string>> &DepositModel::table()
    const noexcept {
  return table_;
}

const std::vector<std::vector<std::string>> &DepositModel::taxTable()
    const noexcept {
  return tax_table_;
}
