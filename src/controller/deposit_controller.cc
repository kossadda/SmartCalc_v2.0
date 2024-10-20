/**
 * @file deposit_controller.cc
 * @author kossadda (https://github.com/kossadda)
 * @brief Implementation of the DepositController class.
 * @version 1.0
 * @date 2024-09-25
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "include/controller/deposit_controller.h"

namespace s21 {

DepositController::DepositController(DepositModel* model) {
  if (model) {
    model_ = model;
  } else {
    model_ = new DepositModel;
  }
}

DepositController::~DepositController() { delete model_; }

void DepositController::addDepositData(long double amount, std::size_t term,
                                       TermType term_type, long double rate,
                                       long double tax_rate, Type type,
                                       Frequency freq, std::size_t day,
                                       std::size_t month,
                                       std::size_t year) noexcept {
  DepositModel::Data data(amount, term, term_type, rate, tax_rate, type, freq,
                          Date(day, month, year));

  model_->clear();
  model_->addData(data);
}

void DepositController::calculateDeposit() noexcept {
  model_->calculatePayments();
}

void DepositController::addOperation(long double sum, OperationType type,
                                     std::size_t day, std::size_t month,
                                     std::size_t year) noexcept {
  DepositModel::Operation op{sum, type, Date(day, month, year)};
  model_->addOperation(op);
}

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

}  // namespace s21
