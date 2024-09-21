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
#include <sstream>
#include <string>
#include <vector>

class Date {
 public:
  using DateSize = uint16_t;

  Date() = default;
  Date(DateSize day, DateSize month, DateSize year);
  Date(const Date &other);

  static bool isYearLeap(DateSize year);
  std::size_t daysPassedInYear() const;
  std::size_t daysLeftInYear() const;
  std::size_t daysLeftInMonth() const;
  Date &addMonth(DateSize init_date);
  Date &addDays(std::size_t term);
  Date &operator=(const Date &other);
  bool operator>(const Date &other) const;
  bool operator<(const Date &other) const;
  bool operator>=(const Date &other) const;
  bool operator<=(const Date &other) const;
  bool operator==(const Date &other) const;
  bool operator!=(const Date &other) const;
  std::size_t operator-(const Date &other) const;
  DateSize day() const;
  DateSize month() const;
  DateSize year() const;
  std::string currentDate() const;

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

  bool isValidDate();
  DateCompare compareDate(const Date &other) const;
  void refreshYearDates();

  DateSize day_{};
  DateSize month_{};
  DateSize year_{};
  bool leap_{};

  std::vector<DateSize> dates_;
  // std::vector<DateSize> dates_{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30,
  // 31};
};

#endif  // SRC_MODULES_INCLUDE_CALENDAR_H_
