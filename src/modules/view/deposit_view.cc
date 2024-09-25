/**
 * @file credit_view.cc
 * @author kossadda (https://github.com/kossadda)
 * @brief
 * @version 1.0
 * @date 2024-09-22
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "modules/include/deposit_view.h"

DepositView::DepositView(DepositController *controller) : QWidget{} {
  allocateMemory(controller);
  initView();
}

DepositView::~DepositView() {}

void DepositView::allocateMemory(DepositController *controller) {
  if (controller) {
    controller_ = controller;
  } else {
    controller_ = new DepositController{};
  }
}

void DepositView::initView() {}
