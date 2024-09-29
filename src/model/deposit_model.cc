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

namespace s21 {

DepositModel::DepositModel() : BaseModel{}, data_{new Data}, tax_{new Tax} {}

DepositModel::~DepositModel() { 
  delete data_->base;
  delete data_;
  delete tax_;
}

DepositModel::Data::Data(long double amount_, long double term_, TermType term_type_, long double rate_, long double tax_rate_, Type type_, Frequency freq_, const Date &date_, std::vector<Operation> *ops_) : base{new BaseModel::Data{amount_, term_, term_type_, rate_, type_, date_}}, freq{freq_},tax_rate{tax_rate_} {
  if(ops_) {
    ops = *ops_;
  }
}

void DepositModel::addData(const Data &data) noexcept {
  *tax_ = Tax{};
  data_->base = data.base;
  data_->freq = data.freq;
  data_->tax_rate = data.tax_rate;
  data_->ops = data.ops;
  tax_->nontaxable *= data_->tax_rate;
  BaseModel::data_ = data_->base;
  BaseModel::data_->rate /= 100.0L;
}

void DepositModel::clear() noexcept {
  table_.clear();
  tax_table_.clear();
}

void DepositModel::calculatePayments() noexcept {
  month_->current = BaseModel::data_->date;
  month_->payment_date = BaseModel::data_->date;
  month_->balance = BaseModel::data_->amount;
  Date last_day{lastDepositDay()};

  while (month_->current != last_day) {
    addPeriod(last_day);

    calculatePeriod();

    calculateTaxes(last_day);

    month_->current = month_->payment_date;
  }
}

Date DepositModel::lastDepositDay() const noexcept {
  Date last_day{month_->current};
  Date::DateSize init_day{month_->current.day()};

  if (BaseModel::data_->term_type == TermType::DAYS) {
    last_day.addDays(BaseModel::data_->term);
  } else {
    std::size_t term = BaseModel::data_->term;

    if (BaseModel::data_->term_type == TermType::YEARS) {
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
    month_->payment_date = last_day;
  } else if (data_->freq == Frequency::DAY) {
    month_->payment_date.addDays(1);
  } else if (data_->freq == Frequency::WEEK) {
    month_->payment_date.addDays(7);
  } else {
    month_->payment_date.addDepositMonth(period);
  }

  if (month_->payment_date > last_day) {
    month_->payment_date = last_day;
  }
}

void DepositModel::calculatePeriod() noexcept {
  month_->percent =
      roundVal(formula(month_->current.leapDaysBetween(month_->payment_date)));

  if (BaseModel::data_->type == Type::FIRST) {
    month_->summary = 0.0L;
    month_->main = month_->percent;
  } else {
    month_->summary = month_->percent;
    month_->main = 0.0L;
    month_->balance += roundVal(month_->percent);
  }

  tax_->total_profit_ += month_->percent;
  monthToTable();
}

void DepositModel::calculateTaxes(const Date &last_day) {
  if (month_->current.year() != month_->payment_date.year() ||
      month_->payment_date == last_day) {
    if (month_->payment_date == last_day) {
      tax_->income += month_->percent;
      tax_->year = last_day.year();
    } else {
      tax_->year = month_->current.year();
    }

    if (tax_->income > tax_->nontaxable) {
      tax_->income_deduction = tax_->income - tax_->nontaxable;
      tax_->tax_amount = roundVal(tax_->income_deduction * kNDFLRate);
      tax_->total_tax_ += tax_->tax_amount;
    }

    taxToTable();

    tax_->income = 0.0L;
    tax_->income_deduction = 0.0L;
  }

  if (month_->payment_date != last_day) {
    tax_->income += month_->percent;
  } else {
    tax_->income -= month_->percent;
  }
}

void DepositModel::taxToTable() noexcept {
  std::vector<std::string> str_year;

  str_year.emplace_back(std::to_string(tax_->year));
  str_year.emplace_back(toStr(tax_->income));
  str_year.emplace_back(toStr(tax_->nontaxable));
  str_year.emplace_back(toStr(tax_->income_deduction));
  str_year.emplace_back(toStr(tax_->tax_amount));
  str_year.emplace_back("Pay by 01.12." + std::to_string(tax_->year + 1));

  tax_table_.emplace_back(str_year);
}

std::vector<std::string> DepositModel::totalTable() const noexcept {
  std::vector<std::string> total_str;
  auto eff_rate{toStr(tax_->total_profit_ / BaseModel::data_->amount * Date::kYearDays /
                      (month_->payment_date - BaseModel::data_->date) * 100.0L)};
  auto tbalance{toStr((BaseModel::data_->type == Type::SECOND)
                          ? month_->balance
                          : BaseModel::data_->amount + tax_->total_profit_)};
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

const std::vector<std::vector<std::string>> &DepositModel::taxTable()
    const noexcept {
  return tax_table_;
}

}  // namespace s21
