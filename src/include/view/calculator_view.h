/**
 * @file calculator_view.h
 * @author kossadda (https://github.com/kossadda)
 * @brief Header file for the CalculatorView class.
 * @version 1.0
 * @date 2024-09-08
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef SRC_INCLUDE_VIEW_CALCULATOR_VIEW_H_
#define SRC_INCLUDE_VIEW_CALCULATOR_VIEW_H_

#include <QDebug>
#include <QDoubleValidator>
#include <QFrame>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QWidget>

#include "include/additional/plot.h"
#include "include/controller/calculator_controller.h"

namespace s21 {

class CalculatorView : public QWidget {
  Q_OBJECT

 public:
  explicit CalculatorView(CalculatorController *controller = nullptr);
  ~CalculatorView();

 private slots:
  void plotWindowClosed() noexcept;
  void validateExpression() noexcept;
  void validateVar() noexcept;

  void modClicked() noexcept;
  void clearClicked() noexcept;
  void delClicked() noexcept;
  void eqClicked() noexcept;
  void plotClicked();
  void unarClicked();
  void numberButtonClicked() noexcept;
  void functionButtonClicked() noexcept;

 private:
  void allocateMemory(CalculatorController *controller);
  void initView();

  CalculatorController *controller_;
  Plot *plot_;
  bool valid_{false};
  bool valid_var_{true};

  QFrame *button_frame_;
  QGridLayout *button_grid_, *main_grid_;
  QPushButton *bsin_, *bcos_, *btan_, *basin_, *bacos_, *batan_, *bsqrt_,
      *bmod_, *blog_, *bln_, *bunar_, *bscience_, *bpi_, *bpow_, *bopenbr_,
      *bclosebr_, *bdiv_, *bmul_, *bminus_, *bplus_, *bvar_, *bdot_, *beq_,
      *bclear_, *bdel_, *bzero_, *bone_, *btwo_, *bthree_, *bfour_, *bfive_,
      *bsix_, *bseven_, *beight_, *bnine_, *bplot_;
  QLineEdit *expr_, *var_value_;
  QLabel *lvar_;
};

}  // namespace s21

#endif  // SRC_INCLUDE_VIEW_CALCULATOR_VIEW_H_
