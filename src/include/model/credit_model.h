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

#ifndef SRC_INCLUDE_MODEL_CREDIT_MODEL_H_
#define SRC_INCLUDE_MODEL_CREDIT_MODEL_H_

#include <cmath>
#include <string>
#include <vector>

#include "include/additional/date.h"
#include "include/model/base_model.h"

namespace s21 {

class CreditModel : public BaseModel {
 public:
  CreditModel();
  ~CreditModel();

  std::vector<std::string> totalTable() const noexcept override;
  void addData(const Data &data) noexcept;
  void calculatePayments() noexcept override;
  void clear() noexcept override;

 private:
  void calculatePeriod() noexcept override;
};

}  // namespace s21

#endif  // SRC_INCLUDE_MODEL_CREDIT_MODEL_H_
