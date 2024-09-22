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

#ifndef SRC_MODULES_INCLUDE_CREDIT_MODEL_H_
#define SRC_MODULES_INCLUDE_CREDIT_MODEL_H_

#include <cmath>
#include <vector>

#include "modules/include/calendar.h"

class CreditModel {
 public:
  enum class CreditType { ANNUITY, DIFFERENTIATED, NOT_CHOSEN };

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

  struct MonthPayment {
   public:
    long double summary{};
    long double main{};
    long double percent{};
    long double debt{};
  };

  CreditModel();
  ~CreditModel();

  void addData(const Data &data) noexcept;
  void calculatePayments() noexcept;
  const std::vector<MonthPayment> &table() const noexcept;
  void clear() noexcept;

 private:
  void calculateAnnuity() noexcept;
  void calculateDifferentiated() noexcept;
  long double formula(const Date &date, std::size_t month_part) const noexcept;
  long double roundVal(long double value) const noexcept;

  Data *data_;
  MonthPayment *month_;
  std::vector<MonthPayment> table_;
};

#endif  // SRC_MODULES_INCLUDE_CREDIT_MODEL_H_
