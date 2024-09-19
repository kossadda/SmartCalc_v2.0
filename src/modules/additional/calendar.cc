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

Date::Date(DataSize day, DataSize month, DataSize year)
    : day_{day}, month_{month}, year_{year} {
  leap_ = isYearLeap(year_);
  dates_[2] = (leap_) ? kLeapFebDays : kFebDays;

  if (!isValidDate()) {
    throw std::invalid_argument("Date:: invalid date");
  }
}

Date::Date(const Date &other)
    : day_{other.day_},
      month_{other.month_},
      year_{other.year_},
      leap_{other.leap_} {}

bool Date::isValidDate() {
  bool valid{true};

  if (month_ > kYearMonths && day_ > dates_[month_]) {
    valid = false;
  } else if(!day_ || !month_ || !year_) {
    valid = false;
  }

  return valid;
}

bool Date::isYearLeap(DataSize year) {
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

  for(DataSize i{1}; i < month_; ++i) {
    days += dates_[i];
  }

  return days;
}

std::size_t Date::daysLeftInYear() const {
  return ((leap_) ? kLeapYearDays : kYearDays) - daysPassedInYear();
}

std::size_t Date::daysLeftInMonth() const {
  return dates_[month_] - day_;
}

Date& Date::operator=(const Date &other) {
  day_ = other.day_;
  month_ = other.month_;
  year_ = other.year_;
  leap_ = other.leap_;
}

Date::DateCompare Date::compareDate(const Date &other) const {
  DateCompare compare{DateCompare::DATE_EQUAL};

  if(year_ < other.year_) {
    compare = DateCompare::DATE_BEFORE;
  } else if(year_ > other.year_) {
    compare = DateCompare::DATE_AFTER;
  }

  if(compare == DateCompare::DATE_EQUAL) {
    if(month_ < other.month_) {
      compare = DateCompare::DATE_BEFORE;
    } else if(month_ > other.month_) {
      compare = DateCompare::DATE_AFTER;
    }
  }

  if(compare == DateCompare::DATE_EQUAL) {
    if(day_ < other.day_) {
      compare = DateCompare::DATE_BEFORE;
    } else if(day_ > other.day_) {
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

  return (comp == DateCompare::DATE_BEFORE || comp == DateCompare::DATE_EQUAL) ? true : false;
}

bool Date::operator>=(const Date &other) const {
  DateCompare comp{compareDate(other)};

  return (comp == DateCompare::DATE_AFTER || comp == DateCompare::DATE_EQUAL) ? true : false;
}

std::size_t Date::operator-(const Date &other) const {
  std::size_t diff{};

  if(year_ == other.year_) {
    diff = daysPassedInYear() - other.daysPassedInYear();
  } else {
    diff = daysPassedInYear() + other.daysLeftInYear();

    for(DataSize i = other.year_ + 1; i != year_; ++i) {
      diff += isYearLeap(i) ? kLeapYearDays : kYearDays;
    }
  }

  return diff;
}
