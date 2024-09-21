/**
 * @file calendar.cc
 * @author kossadda (https://github.com/kossadda)
 * @brief
 * @version 1.0
 * @date 2024-09-19
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "../include/calendar.h"

Date::Date(DateSize day, DateSize month, DateSize year)
    : day_{day}, month_{month}, year_{year}, dates_{0,  31, 28, 31, 30, 31, 30,
                                                    31, 31, 30, 31, 30, 31} {
  refreshYearDates();

  if (!isValidDate()) {
    throw std::invalid_argument("Date:: invalid date");
  }
}

Date::Date(const Date &other)
    : day_{other.day_},
      month_{other.month_},
      year_{other.year_},
      leap_{other.leap_},
      dates_{other.dates_} {}

void Date::refreshYearDates() {
  leap_ = isYearLeap(year_);

  if (leap_) {
    dates_[2] = kLeapFebDays;
  } else {
    dates_[2] = kFebDays;
  }
}

bool Date::isValidDate() {
  bool valid{true};

  if (month_ > kYearMonths && day_ > dates_[month_]) {
    valid = false;
  } else if (!day_ || !month_ || !year_) {
    valid = false;
  }

  return valid;
}

bool Date::isYearLeap(DateSize year) {
  bool leap{false};

  if (!(year % kBigLeapInterval)) {
    leap = true;
  } else if (!(year % kSmallLeapInterval) && (year % kLeapExcectInterval)) {
    leap = true;
  }

  return leap;
}

std::size_t Date::daysPassedInYear() const {
  std::size_t days{day_};

  for (DateSize i{1}; i < month_; ++i) {
    days += dates_[i];
  }

  return days;
}

std::size_t Date::daysLeftInYear() const {
  return ((leap_) ? kLeapYearDays : kYearDays) - daysPassedInYear();
}

std::size_t Date::daysLeftInMonth() const { return dates_[month_] - day_; }

Date &Date::operator=(const Date &other) {
  day_ = other.day_;
  month_ = other.month_;
  year_ = other.year_;
  leap_ = other.leap_;
  dates_ = other.dates_;

  return *this;
}

Date::DateCompare Date::compareDate(const Date &other) const {
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

bool Date::operator==(const Date &other) const {
  return (compareDate(other) == DateCompare::DATE_EQUAL) ? true : false;
}

bool Date::operator!=(const Date &other) const {
  return (compareDate(other) != DateCompare::DATE_EQUAL) ? true : false;
}

bool Date::operator<(const Date &other) const {
  return (compareDate(other) == DateCompare::DATE_BEFORE) ? true : false;
}

bool Date::operator>(const Date &other) const {
  return (compareDate(other) == DateCompare::DATE_AFTER) ? true : false;
}

bool Date::operator<=(const Date &other) const {
  DateCompare comp{compareDate(other)};

  return (comp == DateCompare::DATE_BEFORE || comp == DateCompare::DATE_EQUAL)
             ? true
             : false;
}

bool Date::operator>=(const Date &other) const {
  DateCompare comp{compareDate(other)};

  return (comp == DateCompare::DATE_AFTER || comp == DateCompare::DATE_EQUAL)
             ? true
             : false;
}

std::size_t Date::operator-(const Date &other) const {
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

Date &Date::addMonth(DateSize init_date) {
  if (month_ + 1 > kYearMonths) {
    month_ = 1;
    ++year_;
    refreshYearDates();
  } else {
    ++month_;
  }

  if (init_date > dates_[month_]) {
    day_ = dates_[month_];
  } else {
    day_ = init_date;
  }

  return *this;
}

Date &Date::addDays(std::size_t term) {
  for (std::size_t i{}; i < term; ++i) {
    if (day_ + 1 > dates_[month_]) {
      day_ = 1;

      if (month_ + 1 > kYearMonths) {
        month_ = 1;
        ++year_;
        refreshYearDates();
      } else {
        ++month_;
      }
    } else {
      ++day_;
    }
  }

  return *this;
}

std::string Date::currentDate() const {
  std::stringstream ss;
  ss << day_ << '.' << month_ << '.' << year_;

  return ss.str();
}

Date::DateSize Date::day() const { return day_; }

Date::DateSize Date::month() const { return month_; }

Date::DateSize Date::year() const { return year_; }
