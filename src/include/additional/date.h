/**
 * @file date.h
 * @author kossadda (https://github.com/kossadda)
 * @brief Header file for the Date class.
 * @version 1.0
 * @date 2024-09-19
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef SRC_INCLUDE_ADDITIONAL_DATE_H_
#define SRC_INCLUDE_ADDITIONAL_DATE_H_

#include <iostream>
#include <sstream>
#include <cstdint>
#include <string>
#include <utility>
#include <vector>

namespace s21 {

/// @brief Class representing a date.
class Date {
 public:
  using DateSize = uint16_t;  ///< Type alias for date components.

  Date() = default;
  Date(DateSize day, DateSize month, DateSize year);
  Date(const Date &other);

  static bool isYearLeap(DateSize year) noexcept;
  std::size_t daysPassedInYear() const noexcept;
  std::size_t daysLeftInYear() const noexcept;
  Date &addCreditMonth(DateSize init_day) noexcept;
  Date &addDepositMonth(std::size_t term) noexcept;
  Date &addDays(std::size_t term) noexcept;
  std::pair<std::size_t, std::size_t> leapDaysBetween(
      const Date &end) const noexcept;

  Date &operator=(const Date &other) noexcept;
  bool operator>(const Date &other) const noexcept;
  bool operator<(const Date &other) const noexcept;
  bool operator>=(const Date &other) const noexcept;
  bool operator<=(const Date &other) const noexcept;
  bool operator==(const Date &other) const noexcept;
  bool operator!=(const Date &other) const noexcept;
  std::size_t operator-(const Date &other) const noexcept;
  Date operator+(std::size_t days) const noexcept;

  DateSize day() const noexcept;
  DateSize month() const noexcept;
  DateSize year() const noexcept;
  std::string currentDate() const noexcept;

  static const DateSize kYearMonths = 12;    ///< Number of months in a year.
  static const std::size_t kYearDays = 365;  ///< Number of days non-leap year.
  static const std::size_t kLeapYearDays = 366;  ///< Number of days leap year.

 private:
  /// @brief Enumeration for date comparison.
  enum class DateCompare { DATE_EQUAL, DATE_BEFORE, DATE_AFTER };

  bool isValidDate() const noexcept;
  DateCompare compareDate(const Date &other) const noexcept;
  DateSize daysInMonth(DateSize month) const noexcept;

  DateSize day_{};    ///< Day of the month.
  DateSize month_{};  ///< Month of the year.
  DateSize year_{};   ///< Year.
};

}  // namespace s21

#endif  // SRC_INCLUDE_ADDITIONAL_DATE_H_
