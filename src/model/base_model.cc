/**
 * @file base_model.cc
 * @author kossadda (https://github.com/kossadda)
 * @brief Implementation of the BaseModel class.
 * @version 1.0
 * @date 2024-09-27
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "include/model/base_model.h"

namespace s21 {

/// @brief Constructs a BaseModel object.
BaseModel::BaseModel() : month_{new Month} {}

/// @brief Destructs the BaseModel object.
BaseModel::~BaseModel() { delete month_; }

/**
 * @brief Constructs a Data object with the given parameters.
 * @param amount_ The amount of the loan.
 * @param term_ The term of the loan.
 * @param term_type_ The type of the term (years, months, days).
 * @param rate_ The interest rate.
 * @param type_ The type of the loan.
 * @param date_ The start date of the loan.
 */
BaseModel::Data::Data(long double amount_, long double term_,
                      TermType term_type_, long double rate_, Type type_,
                      const Date &date_)
    : amount{amount_},
      term{term_},
      term_type{term_type_},
      rate{rate_},
      type{type_},
      date{date_} {}

/**
 * @brief Returns the table of payments.
 * @return A constant reference to the table of payments.
 */
const std::vector<std::vector<std::string>> &BaseModel::table() const noexcept {
  return table_;
}

/**
 * @brief Calculates the interest for a given period.
 * @param begin The start date of the period.
 * @param end The end date of the period.
 * @return The calculated interest.
 */
long double BaseModel::formula(const Date &begin, const Date &end) noexcept {
  std::pair<std::size_t, std::size_t> days{begin.leapDaysBetween(end)};

  long double base_sum = month_->balance * data_->rate;
  long double default_sum = base_sum / Date::kYearDays * days.first;
  long double leap_sum = base_sum / Date::kLeapYearDays * days.second;

  return default_sum + leap_sum;
}

/**
 * @brief Rounds a value to two decimal places.
 * @param value The value to round.
 * @return The rounded value.
 */
long double BaseModel::roundVal(long double value) noexcept {
  return std::lround(value * 100.0L + 1.0e-8L) / 100.0L;
}

/**
 * @brief Converts a long double value to a string with two decimal places.
 * @param val The value to convert.
 * @return The string representation of the value.
 */
std::string BaseModel::toStr(long double val) noexcept {
  std::ostringstream stream;

  stream << std::fixed << std::setprecision(2) << val;

  return stream.str();
}

/**
 * @brief Adds a month's data to the table.
 */
void BaseModel::monthToTable() noexcept {
  std::vector<std::string> str_month;

  str_month.emplace_back(month_->current.currentDate());
  str_month.emplace_back(toStr(month_->percent));
  str_month.emplace_back(toStr(month_->main));
  str_month.emplace_back(toStr(month_->summary));
  str_month.emplace_back(toStr(month_->balance));

  table_.emplace_back(str_month);
}

}  // namespace s21
