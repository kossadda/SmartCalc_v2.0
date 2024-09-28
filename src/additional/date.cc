/**
 * @file date.cc
 * @author kossadda (https://github.com/kossadda)
 * @brief
 * @version 1.0
 * @date 2024-09-19
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "include/additional/date.h"

namespace s21 {

Date::Date(DateSize day, DateSize month, DateSize year)
    : day_{day}, month_{month}, year_{year} {
  if (!isValidDate()) {
    throw std::invalid_argument("Date:: invalid date");
  }
}

Date::Date(const Date &other)
    : day_{other.day_}, month_{other.month_}, year_{other.year_} {}

Date::DateSize Date::daysInMonth(DateSize month) const noexcept {
  DateSize days[]{31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  if (isYearLeap(year_)) days[1] = 29;

  return days[month - 1];
}

bool Date::isValidDate() const noexcept {
  bool valid{true};

  if (month_ > kYearMonths && day_ > daysInMonth(month_)) {
    valid = false;
  } else if (!day_ || !month_ || !year_) {
    valid = false;
  }

  return valid;
}

bool Date::isYearLeap(DateSize year) noexcept {
  const std::size_t kBigLeapInterval = 400;
  const std::size_t kSmallLeapInterval = 4;
  const std::size_t kLeapExcectInterval = 100;
  bool leap{false};

  if (!(year % kBigLeapInterval)) {
    leap = true;
  } else if (!(year % kSmallLeapInterval) && (year % kLeapExcectInterval)) {
    leap = true;
  }

  return leap;
}

std::size_t Date::daysPassedInYear() const noexcept {
  std::size_t days{day_};

  for (DateSize i{1}; i < month_; ++i) {
    days += daysInMonth(i);
  }

  return days;
}

std::size_t Date::daysLeftInYear() const noexcept {
  return ((isYearLeap(year_)) ? kLeapYearDays : kYearDays) - daysPassedInYear();
}

Date &Date::operator=(const Date &other) noexcept {
  day_ = other.day_;
  month_ = other.month_;
  year_ = other.year_;

  return *this;
}

Date::DateCompare Date::compareDate(const Date &other) const noexcept {
  DateCompare compare{DateCompare::DATE_EQUAL};

  if (year_ < other.year_) {
    compare = DateCompare::DATE_BEFORE;
  } else if (year_ > other.year_) {
    compare = DateCompare::DATE_AFTER;
  }

  if (compare == DateCompare::DATE_EQUAL) {
    if (month_ < other.month_) {
      compare = DateCompare::DATE_BEFORE;
    } else if (month_ > other.month_) {
      compare = DateCompare::DATE_AFTER;
    }
  }

  if (compare == DateCompare::DATE_EQUAL) {
    if (day_ < other.day_) {
      compare = DateCompare::DATE_BEFORE;
    } else if (day_ > other.day_) {
      compare = DateCompare::DATE_AFTER;
    }
  }

  return compare;
}

bool Date::operator==(const Date &other) const noexcept {
  return (compareDate(other) == DateCompare::DATE_EQUAL) ? true : false;
}

bool Date::operator!=(const Date &other) const noexcept {
  return (compareDate(other) != DateCompare::DATE_EQUAL) ? true : false;
}

bool Date::operator<(const Date &other) const noexcept {
  return (compareDate(other) == DateCompare::DATE_BEFORE) ? true : false;
}

bool Date::operator>(const Date &other) const noexcept {
  return (compareDate(other) == DateCompare::DATE_AFTER) ? true : false;
}

bool Date::operator<=(const Date &other) const noexcept {
  DateCompare comp{compareDate(other)};

  return (comp == DateCompare::DATE_BEFORE || comp == DateCompare::DATE_EQUAL)
             ? true
             : false;
}

bool Date::operator>=(const Date &other) const noexcept {
  DateCompare comp{compareDate(other)};

  return (comp == DateCompare::DATE_AFTER || comp == DateCompare::DATE_EQUAL)
             ? true
             : false;
}

std::size_t Date::operator-(const Date &other) const noexcept {
  std::size_t diff{};

  if (year_ == other.year_) {
    diff = daysPassedInYear() - other.daysPassedInYear();
  } else {
    diff = daysPassedInYear() + other.daysLeftInYear();

    for (DateSize i = other.year_ + 1; i != year_; ++i) {
      diff += isYearLeap(i) ? kLeapYearDays : kYearDays;
    }
  }

  return diff;
}

Date Date::operator+(std::size_t days) const noexcept {
  return Date{*this}.addDays(days);
}

Date &Date::addCreditMonth(DateSize init_day) noexcept {
  if (month_ + 1 > kYearMonths) {
    month_ = 1;
    ++year_;
  } else {
    ++month_;
  }

  if (init_day > daysInMonth(month_)) {
    day_ = daysInMonth(month_);
  } else {
    day_ = init_day;
  }

  return *this;
}

Date &Date::addDepositMonth(std::size_t term) noexcept {
  Date temp{*this};
  std::size_t days_turn{};

  for (std::size_t i{}; i < term; ++i) {
    days_turn += temp.daysInMonth(temp.month_);
    ++temp.month_;

    if (temp.month_ > kYearMonths) {
      ++temp.year_;
      temp.month_ = 1;
    }
  }

  addDays(days_turn);

  return *this;
}

Date &Date::addDays(std::size_t term) noexcept {
  for (std::size_t i{}; i < term; ++i) {
    if (day_ + 1 > daysInMonth(month_)) {
      day_ = 1;

      if (month_ + 1 > kYearMonths) {
        month_ = 1;
        ++year_;
      } else {
        ++month_;
      }
    } else {
      ++day_;
    }
  }

  return *this;
}

std::pair<std::size_t, std::size_t> Date::leapDaysBetween(
    const Date &end) const noexcept {
  std::size_t default_days{};
  std::size_t leap_days{};

  if (year_ != end.year_) {
    if (isYearLeap(year_)) {
      leap_days += daysLeftInYear();
    } else {
      default_days += daysLeftInYear();
    }

    if (isYearLeap(end.year_)) {
      leap_days += end.daysPassedInYear();
    } else {
      default_days += end.daysPassedInYear();
    }

    for (Date::DateSize i(year_ + 1); i < end.year_; ++i) {
      if (isYearLeap(i)) {
        leap_days += kLeapYearDays;
      } else {
        default_days += kYearDays;
      }
    }
  } else {
    if (isYearLeap(year_)) {
      leap_days += end - *this;
    } else {
      default_days += end - *this;
    }
  }

  return {default_days, leap_days};
}

std::string Date::currentDate() const noexcept {
  std::stringstream ss;

  if (day_ < 10) {
    ss << '0';
  }

  ss << day_ << '.';

  if (month_ < 10) {
    ss << '0';
  }

  ss << month_ << '.' << year_;

  return ss.str();
}

Date::DateSize Date::day() const noexcept { return day_; }

Date::DateSize Date::month() const noexcept { return month_; }

Date::DateSize Date::year() const noexcept { return year_; }

}  // namespace s21
