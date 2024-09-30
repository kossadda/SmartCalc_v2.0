/**
 * @file base_model.h
 * @author kossadda (https://github.com/kossadda)
 * @brief Header file for the BaseModel class.
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

/// @brief Base class for different loan models.
class BaseModel {
 public:
  /// @brief Enumeration for the term type of the loan.
  enum class TermType { YEARS, MONTHS, DAYS };

  /// @brief Enumeration for the type of the loan.
  enum class Type { FIRST, SECOND };

  /// @brief Structure to hold the data of the loan.
  struct Data {
   public:
    Data() = default;
    Data(long double amount_, long double term_, TermType term_type_,
         long double rate_, Type type_, const Date &date_);

    long double amount{};  ///< The amount of the loan.
    long double term{};    ///< The term of the loan.
    TermType term_type;    ///< The type of the term (years, months, days).
    long double rate{};    ///< The interest rate.
    Type type;             ///< The type of the loan.
    Date date;             ///< The start date of the loan.
  };

  /// @brief Structure to hold the monthly payment data.
  struct Month {
   public:
    Date payment_date;      ///< The payment date.
    Date current;           ///< The current date.
    long double summary{};  ///< The summary of the payment / balance changing
    long double main{};     ///< The main part of the payment / deposit pay
    long double percent{};  ///< The interest part of the payment.
    long double balance{};  ///< The remaining balance.
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

  Data *data_;    ///< Pointer to the loan data.
  Month *month_;  ///< Pointer to the monthly payment data.
  std::vector<std::vector<std::string>> table_;  ///< Table of payments.
};

}  // namespace s21

#endif  // SRC_INCLUDE_MODEL_BASE_MODEL_H_
