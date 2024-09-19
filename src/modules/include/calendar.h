/**
 * @file calendar.h
 * @author kossadda (https://github.com/kossadda)
 * @brief
 * @version 1.0
 * @date 2024-09-19
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef SRC_MODULES_INCLUDE_CALENDAR_H_
#define SRC_MODULES_INCLUDE_CALENDAR_H_

#include <iostream>
#include <vector>

class Date {
 public:
  using DataSize = unsigned short;

  Date() = default;
  Date(DataSize day, DataSize month, DataSize year);
  Date(const Date &other);

  static bool isYearLeap(DataSize year);
  std::size_t daysPassedInYear() const;
  std::size_t daysLeftInYear() const;
  std::size_t daysLeftInMonth() const;
  Date &operator=(const Date &other);
  bool operator>(const Date &other) const;
  bool operator<(const Date &other) const;
  bool operator>=(const Date &other) const;
  bool operator<=(const Date &other) const;
  bool operator==(const Date &other) const;
  bool operator!=(const Date &other) const;
  std::size_t operator-(const Date &other) const;

  static const std::size_t kYearMonths = 12;
  static const std::size_t kYearDays = 365;
  static const std::size_t kLeapYearDays = 366;
  static const std::size_t kBigLeapInterval = 400;
  static const std::size_t kSmallLeapInterval = 4;
  static const std::size_t kLeapExcectInterval = 100;
  static const std::size_t kLeapFebDays = 29;
  static const std::size_t kFebDays = 28;

 private:
  enum class DateCompare {
    DATE_EQUAL,
    DATE_BEFORE,
    DATE_AFTER
  };

  bool isValidDate();
  DateCompare compareDate(const Date &other) const;

  DataSize day_{};
  DataSize month_{};
  DataSize year_{};
  bool leap_{};

  std::vector<DataSize> dates_{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
};

#endif  // SRC_MODULES_INCLUDE_CALENDAR_H_
