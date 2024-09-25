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
#include <vector>

#include "modules/include/date.h"

class DepositModel {
 public:
  enum class Frequency { DAY, WEEK, MONTH, QUARTER, HALFYEAR, YEAR, ENDTERM };
  enum class DepositType { DEFAULT, CAPITALIZATION };

  struct Data {
   public:
    Data() = default;
    Data(long double amount_, long double term_, long double rate_,
         Frequency freq_, DepositType type_, const Date &date_)
        : amount{amount_},
          term{term_},
          rate{rate_},
          type{type_},
          freq{freq_},
          date{date_} {}

    long double amount{};
    long double term{};
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

  DepositModel();
  ~DepositModel();

  void addData(const Data &data) noexcept;
  void calculatePayments() noexcept;
  const std::vector<Month> &table() const noexcept;
  void clear() noexcept;

 private:
  Data *data_;
  Month *month_;
  std::vector<Month> table_;
};

#endif  // SRC_MODULES_INCLUDE_DEPOSIT_MODEL_H_
