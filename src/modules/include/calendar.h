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
  Date() = default;
  Date(std::size_t day, std::size_t month, std::size_t year);
  Date(const Date &other);

  bool isYearLeap();
  std::size_t daysPassedInYear();
  bool operator>(const Date &other);
  bool operator<(const Date &other);
  bool operator>=(const Date &other);
  bool operator<=(const Date &other);
  bool operator==(const Date &other);
  bool operator!=(const Date &other);
  std::size_t operator-(const Date &other);

  static const std::size_t kMaxYear = 10000;
  static const std::size_t kYearMonths = 12;
  static const std::size_t kYearDays = 365;
  static const std::size_t kLeapYearDays = 366;
  static const std::size_t kBigLeapInterval = 400;
  static const std::size_t kSmallLeapInterval = 4;
  static const std::size_t kLeapExcectInterval = 100;
  static const std::size_t kLeapFebDays = 29;
  static const std::size_t kFebDays = 28;

 private:
  enum DateCompare {
    DATE_EQUAL,
    DATE_BEFORE,
    DATE_AFTER
  };

  bool isValidDate();
  std::size_t daysInMonth();
  DateCompare compareDate(const Date &other);

  std::size_t day_{};
  std::size_t month_{};
  std::size_t year_{};
  bool leap_{};

  std::vector<std::size_t> dates_{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
};

#endif  // SRC_MODULES_INCLUDE_CALENDAR_H_
