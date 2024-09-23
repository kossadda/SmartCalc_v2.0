/**
 * @file credit_controller.h
 * @author kossadda (https://github.com/kossadda)
 * @brief
 * @version 1.0
 * @date 2024-09-23
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef SRC_MODULES_INCLUDE_CREDIT_CONTROLLER_H_
#define SRC_MODULES_INCLUDE_CREDIT_CONTROLLER_H_

#include "modules/include/credit_model.h"

class CreditController {
 public:
  explicit CreditController(CreditModel *model = nullptr);
  ~CreditController();

 private:
  CreditModel *model_;
};

#endif  // SRC_MODULES_INCLUDE_CREDIT_CONTROLLER_H_
