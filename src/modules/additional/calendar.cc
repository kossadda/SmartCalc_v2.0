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

Date::Date(std::size_t day, std::size_t month, std::size_t year)
    : day_{day}, month_{month}, year_{year} {
  leap_ = isYearLeap();

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

  if (month_ > kYearMonths && day_ > daysInMonth() && year_ > kMaxYear) {
    valid = false;
  } else if(!day_ || !month_ || !year_) {
    valid = false;
  }

  return valid;
}

bool Date::isYearLeap() {
  bool leap{false};

  if (!(year_ % kBigLeapInterval)) {
    leap = true;
  } else if (!(year_ % kSmallLeapInterval) && (year_ % kLeapExcectInterval)) {
    leap = true;
  }

  dates_[2] = (leap) ? kLeapFebDays : kFebDays;

  return leap;
}

std::size_t Date::daysInMonth() {
  leap_ = isYearLeap();

  return dates_[month_];
}

std::size_t Date::daysPassedInYear() {
  std::size_t days{day_};

  for(std::size_t i{1}; i < month_; ++i) {
    days += dates_[i];
  }

  return days;
}

Date::DateCompare Date::compareDate(const Date &other) {
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

bool Date::operator==(const Date &other) {
  return (compareDate(other) == DateCompare::DATE_EQUAL) ? true : false;
}

bool Date::operator!=(const Date &other) {
  return (compareDate(other) != DateCompare::DATE_EQUAL) ? true : false;
}

bool Date::operator<(const Date &other) {
  return (compareDate(other) == DateCompare::DATE_BEFORE) ? true : false;
}

bool Date::operator>(const Date &other) {
  return (compareDate(other) == DateCompare::DATE_AFTER) ? true : false;
}

bool Date::operator<=(const Date &other) {
  DateCompare comp{compareDate(other)};

  return (comp == DateCompare::DATE_BEFORE || comp == DateCompare::DATE_EQUAL) ? true : false;
}

bool Date::operator>=(const Date &other) {
  DateCompare comp{compareDate(other)};

  return (comp == DateCompare::DATE_AFTER || comp == DateCompare::DATE_EQUAL) ? true : false;
}

std::size_t Date::operator-(const Date &other) {
  std::size_t diff{};

  if(year_ == other.year_) {
    diff = daysPassedInYear();
  }

  return diff;
}
