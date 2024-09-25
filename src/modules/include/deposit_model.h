/**
 * @file deposit_model.h
 * @author kossadda (https://github.com/kossadda)
 * @brief
 * @version 1.0
 * @date 2024-09-25
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef SRC_MODULES_INCLUDE_DEPOSIT_MODEL_H_
#define SRC_MODULES_INCLUDE_DEPOSIT_MODEL_H_

#include <cmath>
#include <utility>
#include <vector>

#include "modules/include/date.h"

class DepositModel {
 public:
  enum class Frequency {
    DAY = 0,
    MONTH = 1,
    ENDTERM = 2,
    QUARTER = 3,
    HALFYEAR = 6,
    WEEK = 7,
    YEAR = 12
  };

  enum class TermType { DAYS, MONTHS, YEARS };

  enum class DepositType { DEFAULT, CAPITALIZATION };

  struct Data {
   public:
    Data() = default;
    Data(long double amount_, long double term_, TermType term_type_,
         long double rate_, long double tax_rate_, DepositType type_,
         Frequency freq_, const Date &date_)
        : amount{amount_},
          term{term_},
          term_type{term_type_},
          rate{rate_},
          tax_rate{tax_rate_},
          type{type_},
          freq{freq_},
          date{date_} {}

    long double amount{};
    long double term{};
    TermType term_type;
    long double rate{};
    long double tax_rate{};
    DepositType type;
    Frequency freq;
    Date date;
  };

  struct Month {
   public:
    Date accrual_date;
    long double profit;
    long double balance_changing;
    long double receiving;
    long double balance;
  };

  struct Tax {
    Date::DateSize year{};
    long double income{};
    long double nontaxable{};
    long double income_deduction{};
    long double tax_amount{};
  };

  DepositModel();
  ~DepositModel();

  void addData(const Data &data) noexcept;
  void calculatePayments() noexcept;
  const std::vector<Month> &table() const noexcept;
  const std::vector<Tax> &taxTable() const noexcept;
  void clear() noexcept;
  void printTable();

 private:
  Date lastDepositDay() const noexcept;
  void addPeriod(const Date &last_day) noexcept;
  void calculatePeriod();
  void calculateTaxes(const Date &last_day);
  long double formula(std::pair<std::size_t, std::size_t> days) const noexcept;
  long double roundVal(long double value) const noexcept;

  static constexpr long double kNonTaxSum = 1.0e+6L;
  static constexpr long double kNDFLRate = 13.0L;

  Data *data_;
  Month *month_;
  Tax *tax_;
  std::vector<Month> table_;
  std::vector<Tax> tax_table_;
};

#endif  // SRC_MODULES_INCLUDE_DEPOSIT_MODEL_H_
