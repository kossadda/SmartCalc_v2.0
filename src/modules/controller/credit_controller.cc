/**
 * @file credit_controller.cc
 * @author kossadda (https://github.com/kossadda)
 * @brief
 * @version 1.0
 * @date 2024-09-23
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "modules/include/credit_controller.h"

CreditController::CreditController(CreditModel* model) {
  if (model) {
    model_ = model;
  } else {
    model_ = new CreditModel{};
  }
}

CreditController::~CreditController() { delete model_; }

// std::vector<std::vector<std::string>> CreditController::table() const noexcept {
  // std::vector<std::vector<std::string>> m_table;

  // for(auto i : model_->table()) {
    // m_table.push_back({i.summary, i.main, i.percent, i.debt});
  // }

  // return m_table;
// }
