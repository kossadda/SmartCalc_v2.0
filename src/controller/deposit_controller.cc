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
  DepositModel::Data data{
      amount, static_cast<long double>(term), term_type, rate, tax_rate, type,
      freq,   Date(day, month, year)};

  model_->addData(data);
  model_->clear();
}

void DepositController::calculateDeposit() { model_->calculatePayments(); }

const std::vector<std::vector<std::string>>& DepositController::table()
    const noexcept {
  return model_->table();
}

const std::vector<std::vector<std::string>>& DepositController::taxTable()
    const noexcept {
  return model_->taxTable();
}

std::vector<std::string> DepositController::totalTable() const noexcept {
  return model_->totalTable();
}
