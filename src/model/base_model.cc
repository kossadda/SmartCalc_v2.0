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

BaseModel::BaseModel() : data_{new Data}, month_{new Month} {}

BaseModel::~BaseModel() {
  delete data_;
  delete month_;
}

const std::vector<std::vector<std::string>> &BaseModel::table() const noexcept {
  return table_;
}

long double BaseModel::formula(
    std::pair<std::size_t, std::size_t> days) noexcept {
  long double default_sum = (month_->balance * data_->rate / 100.0L) /
                            static_cast<long double>(Date::kYearDays) *
                            static_cast<long double>(days.first);
  long double leap_sum = (month_->balance * data_->rate / 100.0L) /
                         static_cast<long double>(Date::kLeapYearDays) *
                         static_cast<long double>(days.second);
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
