/**
 * @file deposit_controller.cc
 * @author kossadda (https://github.com/kossadda)
 * @brief
 * @version 1.0
 * @date 2024-09-25
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "include/controller/deposit_controller.h"

DepositController::DepositController(DepositModel* model) {
  if (model) {
    model_ = model;
  } else {
    model_ = new DepositModel{};
  }
}

DepositController::~DepositController() { delete model_; }

void DepositController::addDepositData(long double amount, std::size_t term,
                                       TermType term_type, long double rate,
                                       long double tax_rate, DepositType type,
                                       Frequency freq, std::size_t day,
                                       std::size_t month, std::size_t year) {
  DepositModel::Data data{amount, static_cast<long double>(term), term_type, rate, tax_rate, type, freq, Date(day, month, year)};

  model_->addData(data);
  model_->clear();
  table_.clear();
}

void DepositController::calculateDeposit() {
  model_->calculatePayments();

  for (const auto& i : model_->table()) {
    std::vector<std::string> str_month;

    std::ostringstream sprofit, sbal_change, sreceiving, sbalance;
    sprofit << std::fixed << std::setprecision(2) << i.profit;
    sbal_change << std::fixed << std::setprecision(2) << i.balance_changing;
    sreceiving << std::fixed << std::setprecision(2) << i.receiving;
    sbalance << std::fixed << std::setprecision(2) << i.balance;

    str_month.push_back(i.accrual_date.currentDate());
    str_month.push_back(sprofit.str());
    str_month.push_back(sbal_change.str());
    str_month.push_back(sreceiving.str());
    str_month.push_back(sbalance.str());

    table_.push_back(str_month);
  }
}

std::vector<std::vector<std::string>>& DepositController::table() noexcept {
  return table_;
}
