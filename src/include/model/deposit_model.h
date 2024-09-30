/**
 * @file deposit_model.h
 * @author kossadda (https://github.com/kossadda)
 * @brief Header file for the DepositModel class.
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

/// @brief Class for handling deposit models.
class DepositModel : public BaseModel {
 public:
  /// @brief Enumeration for the frequency of interest accrual.
  enum class Frequency {
    DAY = 0,
    MONTH = 1,
    ENDTERM = 2,
    QUARTER = 3,
    HALFYEAR = 6,
    WEEK = 7,
    YEAR = 12
  };

  /// @brief Enumeration for the type of operation.
  enum class OperationType { REFILL, WITHDRAWAL };

  /// @brief Structure to hold the operation data.
  struct Operation {
    Operation() = default;
    Operation(long double sum_, OperationType type_, const Date &date_);
    long double sum{};   ///< The sum of the operation.
    OperationType type;  ///< The type of the operation.
    Date date;           ///< The date of the operation.
  };

  /// @brief Structure to hold the deposit data.
  struct Data {
    Data() = default;
    Data(long double amount_, long double term_, TermType term_type_,
         long double rate_, long double tax_rate_, Type type_, Frequency freq_,
         const Date &date_, std::vector<Operation> *ops_ = nullptr);
    BaseModel::Data *base{};     ///< Pointer to the base data.
    Frequency freq;              ///< The frequency of interest accrual.
    long double tax_rate{};      ///< The tax rate.
    std::vector<Operation> ops;  ///< The list of operations.
    long double ops_percent{};   ///< The percentage of operations.
  };

  /// @brief Structure to hold the tax data.
  struct Tax {
    Date::DateSize year;               ///< The year for tax calculation.
    long double income{};              ///< The income for tax calculation.
    long double nontaxable{10000.0L};  ///< The non-taxable income.
    long double income_deduction{};    ///< The income deduction for tax calc.
    long double tax_amount{};          ///< The tax amount.
    long double total_profit_{};       ///< The total profit.
    long double total_tax_{};          ///< The total tax.
  };

  DepositModel();
  ~DepositModel();

  const std::vector<std::vector<std::string>> &taxTable() const noexcept;
  std::vector<std::string> totalTable() const noexcept override;
  void addData(const Data &data) noexcept;
  void addOperation(const Operation &op) noexcept;
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

  static constexpr long double kNDFLRate = 0.13L;  ///< The NDFL tax rate.

  Data *data_;  ///< Pointer to the deposit data.
  Tax *tax_;    ///< Pointer to the tax data.
  std::vector<std::vector<std::string>> tax_table_;  ///< Table of tax data.
};

}  // namespace s21

#endif  // SRC_INCLUDE_MODEL_DEPOSIT_MODEL_H_
