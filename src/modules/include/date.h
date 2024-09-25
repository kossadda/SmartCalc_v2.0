/**
 * @file date.h
 * @author kossadda (https://github.com/kossadda)
 * @brief
 * @version 1.0
 * @date 2024-09-19
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef SRC_MODULES_INCLUDE_DATE_H_
#define SRC_MODULES_INCLUDE_DATE_H_

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <utility>

class Date {
 public:
  using DateSize = uint16_t;

  Date() = default;
  Date(DateSize day, DateSize month, DateSize year);
  Date(const Date &other);

  static bool isYearLeap(DateSize year) noexcept;
  std::size_t daysPassedInYear() const noexcept;
  std::size_t daysLeftInYear() const noexcept;
  std::size_t daysLeftInMonth() const noexcept;
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

  static const DateSize kYearMonths = 12;
  static const DateSize kLeapFebDays = 29;
  static const DateSize kFebDays = 28;
  static const std::size_t kYearDays = 365;
  static const std::size_t kLeapYearDays = 366;
  static const std::size_t kBigLeapInterval = 400;
  static const std::size_t kSmallLeapInterval = 4;
  static const std::size_t kLeapExcectInterval = 100;

 private:
  enum class DateCompare { DATE_EQUAL, DATE_BEFORE, DATE_AFTER };

  bool isValidDate() const noexcept;
  DateCompare compareDate(const Date &other) const noexcept;
  void refreshYearDates() noexcept;

  DateSize day_{};
  DateSize month_{};
  DateSize year_{};
  bool leap_{};

  std::vector<DateSize> dates_;
};

#endif  // SRC_MODULES_INCLUDE_DATE_H_
