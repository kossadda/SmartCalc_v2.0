/**
 * @file base_model.h
 * @author kossadda (https://github.com/kossadda)
 * @brief
 * @version 1.0
 * @date 2024-09-27
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef SRC_INCLUDE_MODEL_BASE_MODEL_H_
#define SRC_INCLUDE_MODEL_BASE_MODEL_H_

#include <cmath>
#include <iomanip>
#include <string>
#include <utility>
#include <vector>

#include "include/additional/date.h"

namespace s21 {

class BaseModel {
 public:
  enum class TermType { YEARS, MONTHS, DAYS };
  enum class Type { FIRST, SECOND };

  struct Data {
   public:
    Data() = default;
    Data(long double amount_, long double term_, TermType term_type_,
         long double rate_, Type type_, const Date &date_);

    long double amount{};
    long double term{};
    TermType term_type;
    long double rate{};
    Type type;
    Date date;
  };

  struct Month {
   public:
    Date payment_date;
    Date current;
    long double summary{};
    long double main{};
    long double percent{};
    long double balance{};
  };

  BaseModel();
  virtual ~BaseModel();

  static long double roundVal(long double value) noexcept;
  static std::string toStr(long double val) noexcept;

  const std::vector<std::vector<std::string>> &table() const noexcept;
  virtual std::vector<std::string> totalTable() const noexcept = 0;
  virtual void calculatePayments() noexcept = 0;
  virtual void clear() noexcept = 0;

 protected:
  void monthToTable() noexcept;
  long double formula(const Date &begin, const Date &end) noexcept;
  virtual void calculatePeriod() noexcept = 0;

  Data *data_;
  Month *month_;
  std::vector<std::vector<std::string>> table_;
};

}  // namespace s21

#endif  // SRC_INCLUDE_MODEL_BASE_MODEL_H_
