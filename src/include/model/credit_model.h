/**
 * @file credit_model.h
 * @author kossadda (https://github.com/kossadda)
 * @brief
 * @version 1.0
 * @date 2024-09-19
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef SRC_INCLUDE_MODEL_CREDIT_MODEL_H_
#define SRC_INCLUDE_MODEL_CREDIT_MODEL_H_

#include <cmath>
#include <iomanip>
#include <string>
#include <vector>

#include "include/additional/date.h"

class CreditModel {
 public:
  enum class CreditType { ANNUITY, DIFFERENTIATED };
  enum class TermType { YEARS, MOHTHS };

  struct Data {
   public:
    Data() = default;
    Data(long double amount_, long double term_, TermType term_type_,
         long double rate_, CreditType type_, const Date &date_)
        : amount{amount_},
          term{term_},
          term_type{term_type_},
          rate{rate_},
          type{type_},
          date{date_} {}

    long double amount{};
    long double term{};
    TermType term_type;
    long double rate{};
    CreditType type;
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

  CreditModel();
  ~CreditModel();

  void addData(const Data &data) noexcept;
  void calculatePayments() noexcept;
  void clear() noexcept;
  std::vector<std::string> totalTable() const noexcept;
  const std::vector<std::vector<std::string>> &table() const noexcept;

 private:
  void calculatePeriod() noexcept;
  long double formula(std::pair<std::size_t, std::size_t> days) const noexcept;
  long double roundVal(long double value) const noexcept;
  std::vector<std::string> monthToString() const noexcept;
  std::string toStr(long double val) const noexcept;

  Data *data_;
  Month *month_;
  std::vector<std::vector<std::string>> table_;
  long double total_{};
};

#endif  // SRC_INCLUDE_MODEL_CREDIT_MODEL_H_
