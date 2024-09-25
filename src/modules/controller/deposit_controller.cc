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

#include "modules/include/deposit_controller.h"

DepositController::DepositController(DepositModel* model) {
  if (model) {
    model_ = model;
  } else {
    model_ = new DepositModel{};
  }
}

DepositController::~DepositController() {}
