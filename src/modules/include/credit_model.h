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

#include "calendar.h"

class CreditModel {
 public:
  enum class CreditType { ANNUITY, DIFFERENTIATED, NOT_CHOSEN };

  CreditModel();
  ~CreditModel();

  void addData(long double amount, std::size_t term, long double rate,
               const Date &date, CreditType type);
  void calculatePayments();
  std::vector<long double> &total();
  std::vector<std::vector<long double>> &table();
  void printTable() const;

 private:
  struct Data {
   public:
    long double debt_;
    long double term_;
    long double rate_;
    Date date_;
    CreditType type_;
  };

  struct Current {
   public:
    long double main_{};
    long double percent_{};
    long double summary_{};
    long double const_main_{};
  };

  void calculateAnnuity(long double paid_percent);
  void calculateDifferentiated(long double paid_percent);
  long double formula(Date &date, std::size_t month_part);
  long double roundVal(long double value);
  void addMonthToTable();

  Data *data_;
  Current *month_;
  std::vector<std::vector<long double>> table_;
  std::vector<long double> total_;
};

#endif  // SRC_MODULES_INCLUDE_CREDIT_MODEL_H_
