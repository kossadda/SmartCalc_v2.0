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

#ifndef SRC_INCLUDE_MODEL_DEPOSIT_MODEL_H_
#define SRC_INCLUDE_MODEL_DEPOSIT_MODEL_H_

#include <cmath>
#include <string>
#include <vector>

#include "include/additional/date.h"
#include "include/model/base_model.h"

namespace s21 {

class DepositModel : public BaseModel {
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

  enum class OperationType { REFILL, WITHDRAWAL };

  struct Operation {
    Operation() = default;
    Operation(long double sum_, OperationType type_, const Date &date_);
    long double sum{};
    OperationType type;
    Date date;
  };

  struct Data {
    Data() = default;
    Data(long double amount_, long double term_, TermType term_type_,
         long double rate_, long double tax_rate_, Type type_, Frequency freq_,
         const Date &date_, std::vector<Operation> *ops_ = nullptr);
    BaseModel::Data *base;
    Frequency freq;
    long double tax_rate{};
    std::vector<Operation> ops;
    long double ops_percent{};
  };

  struct Tax {
    Date::DateSize year;
    long double income{};
    long double nontaxable{10000.0L};
    long double income_deduction{};
    long double tax_amount{};
    long double total_profit_{};
    long double total_tax_{};
  };

  DepositModel();
  ~DepositModel();

  const std::vector<std::vector<std::string>> &taxTable() const noexcept;
  std::vector<std::string> totalTable() const noexcept override;
  void addData(const Data &data) noexcept;
  void calculatePayments() noexcept override;
  void clear() noexcept override;

 private:
  void calculatePeriod() noexcept override;
  Date lastDepositDay() const noexcept;
  void addPeriod(const Date &last_day) noexcept;
  void calculateTaxes(const Date &last_day);
  void calculateOperations();
  void sortOperations();
  void taxToTable() noexcept;

  static constexpr long double kNDFLRate = 0.13L;

  Data *data_;
  Tax *tax_;
  std::vector<std::vector<std::string>> tax_table_;
};

}  // namespace s21

#endif  // SRC_INCLUDE_MODEL_DEPOSIT_MODEL_H_
