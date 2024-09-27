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

  struct Data {
   public:
    Data() = default;
    Data(long double amount_, long double term_, long double rate_,
         CreditType type_, const Date &date_)
        : amount{amount_}, term{term_}, rate{rate_}, type{type_}, date{date_} {}

    long double amount{};
    long double term{};
    long double rate{};
    CreditType type;
    Date date;
  };

  struct Month {
   public:
    Date payment_date;
    long double summary{};
    long double main{};
    long double percent{};
    long double debt{};
  };

  CreditModel();
  ~CreditModel();

  void addData(const Data &data) noexcept;
  void calculatePayments() noexcept;
  const std::vector<std::vector<std::string>> &table() const noexcept;
  void clear() noexcept;

 private:
  void calculateAnnuity() noexcept;
  void calculateDifferentiated() noexcept;
  long double formula(const Date &date, std::size_t month_part) const noexcept;
  long double roundVal(long double value) const noexcept;
  std::vector<std::string> monthToString() const noexcept;

  Data *data_;
  Month *month_;
  std::vector<std::vector<std::string>> table_;
};

#endif  // SRC_INCLUDE_MODEL_CREDIT_MODEL_H_
