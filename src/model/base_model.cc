/**
 * @file base_model.cc
 * @author kossadda (https://github.com/kossadda)
 * @brief
 * @version 1.0
 * @date 2024-09-27
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "include/model/base_model.h"

namespace s21 {

BaseModel::BaseModel() : month_{new Month} {}

BaseModel::~BaseModel() {
  delete month_;
}

BaseModel::Data::Data(long double amount_, long double term_,
                      TermType term_type_, long double rate_, Type type_,
                      const Date &date_)
    : amount{amount_},
      term{term_},
      term_type{term_type_},
      rate{rate_},
      type{type_},
      date{date_} {}

const std::vector<std::vector<std::string>> &BaseModel::table() const noexcept {
  return table_;
}

long double BaseModel::formula(
    std::pair<std::size_t, std::size_t> days) noexcept {
  long double base_sum = month_->balance * data_->rate;
  long double default_sum = base_sum / Date::kYearDays * days.first;
  long double leap_sum = base_sum / Date::kLeapYearDays * days.second;
  return default_sum + leap_sum;
}

long double BaseModel::roundVal(long double value) noexcept {
  return std::lround(value * 100.0L + 1.0e-8L) / 100.0L;
}

std::string BaseModel::toStr(long double val) noexcept {
  std::ostringstream stream;

  stream << std::fixed << std::setprecision(2) << val;

  return stream.str();
}

void BaseModel::monthToTable() noexcept {
  std::vector<std::string> str_month;

  str_month.emplace_back(month_->payment_date.currentDate());
  str_month.emplace_back(toStr(month_->percent));
  str_month.emplace_back(toStr(month_->main));
  str_month.emplace_back(toStr(month_->summary));
  str_month.emplace_back(toStr(month_->balance));

  table_.emplace_back(str_month);
}

}  // namespace s21
