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

  enum class EarlyPayType { REDUCE_TERM, REDUCE_PAY };

  struct Data {
   public:
    Data() = default;
    Data(long double debt_, long double term_, long double rate_,
         CreditType type_, const Date &date_)
        : debt{debt_}, term{term_}, rate{rate_}, type{type_}, date{date_} {}

    long double debt{};
    long double term{};
    long double rate{};
    CreditType type;
    Date date;
  };

  struct EarlyPayment {
    EarlyPayment(EarlyPayType type_, long double sum_, const Date &date_)
        : type{type_}, sum{sum_}, date{date_} {}
        
    EarlyPayType type;
    long double sum{};
    Date date;
  };

  CreditModel();
  ~CreditModel();

  void addData(Data &data);
  void addEarlyPayments(const std::vector<EarlyPayment> &early);
  void calculatePayments();
  void clear();
  std::vector<long double> &total();
  std::vector<std::vector<long double>> &table();
  void printTable() const;

 private:
  struct Current {
   public:
    long double main{};
    long double percent{};
    long double summary{};
    long double const_main{};
  };

  void calculateAnnuity(long double paid_percent);
  void calculateDifferentiated(long double paid_percent);
  long double formula(Date &date, std::size_t month_part);
  long double roundVal(long double value);
  void addMonthToTable();

  Data *data_;
  Current *month_;
  std::vector<std::vector<long double>> table_;
  std::vector<EarlyPayment> early_;
  std::vector<long double> total_;
};

#endif  // SRC_MODULES_INCLUDE_CREDIT_MODEL_H_
