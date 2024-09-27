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

const std::vector<std::vector<std::string>> &DepositModel::table()
    const noexcept {
  return table_;
}

const std::vector<std::vector<std::string>> &DepositModel::taxTable()
    const noexcept {
  return tax_table_;
}

void DepositModel::calculatePayments() noexcept {
  Date last_day{lastDepositDay()};
  month_->accrual_date = data_->date;
  month_->balance = data_->amount;
  tax_->nontaxable = data_->tax_rate * kNonTaxSum / 100.0L;

  while (data_->date != last_day) {
    addPeriod(last_day);

    calculatePeriod();

    calculateTaxes(last_day);

    data_->date = month_->accrual_date;
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
      roundVal(formula(data_->date.leapDaysBetween(month_->accrual_date)));

  if (data_->type == DepositType::CAPITALIZATION) {
    month_->balance_changing = month_->profit;
    month_->receiving = 0.0L;
    month_->balance += roundVal(month_->profit);
  } else {
    month_->balance_changing = 0.0L;
    month_->receiving = month_->profit;
  }

  table_.push_back(monthToString());
}

void DepositModel::calculateTaxes(const Date &last_day) {
  if (data_->date.year() != month_->accrual_date.year() ||
      month_->accrual_date == last_day) {
    tax_->year = data_->date.year();

    if (tax_->income > tax_->nontaxable) {
      tax_->income_deduction = tax_->income - tax_->nontaxable;
      tax_->tax_amount = roundVal(tax_->income_deduction * kNDFLRate / 100.0L);
    }

    tax_table_.push_back(taxToString());

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

std::vector<std::string> DepositModel::monthToString() const noexcept {
  std::vector<std::string> str_month;

  std::ostringstream sprofit, sbal_change, sreceiving, sbalance;
  sprofit << std::fixed << std::setprecision(2) << month_->profit;
  sbal_change << std::fixed << std::setprecision(2) << month_->balance_changing;
  sreceiving << std::fixed << std::setprecision(2) << month_->receiving;
  sbalance << std::fixed << std::setprecision(2) << month_->balance;

  str_month.push_back(month_->accrual_date.currentDate());
  str_month.push_back(sprofit.str());
  str_month.push_back(sbal_change.str());
  str_month.push_back(sreceiving.str());
  str_month.push_back(sbalance.str());

  return str_month;
}

std::vector<std::string> DepositModel::taxToString() const noexcept {
  std::vector<std::string> str_year;

  std::ostringstream sincome, sincome_deduc, snontax, stax, syear, sinfo;
  syear << tax_->year;
  sincome << std::fixed << std::setprecision(2) << tax_->income;
  snontax << std::fixed << std::setprecision(2) << tax_->nontaxable;
  sincome_deduc << std::fixed << std::setprecision(2) << tax_->income_deduction;
  stax << std::fixed << std::setprecision(2) << tax_->tax_amount;
  sinfo << "Pay by 01.12." << tax_->year + 1;

  str_year.push_back(syear.str());
  str_year.push_back(sincome.str());
  str_year.push_back(snontax.str());
  str_year.push_back(sincome_deduc.str());
  str_year.push_back(stax.str());
  str_year.push_back(sinfo.str());

  return str_year;
}
