/**
 * @file calculator_view.h
 * @author kossadda (https://github.com/kossadda)
 * @brief
 * @version 1.0
 * @date 2024-09-08
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef SRC_MODULES_INCLUDE_CALCULATOR_VIEW_H_
#define SRC_MODULES_INCLUDE_CALCULATOR_VIEW_H_

#include <QDebug>
#include <QDoubleValidator>
#include <QFrame>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QWidget>

#include "modules/include/calculator_controller.h"
#include "modules/include/plot.h"

class CalculatorView : public QWidget {
  Q_OBJECT

 public:
  explicit CalculatorView(CalculatorController *controller = nullptr);
  ~CalculatorView();

 private slots:
  void plotWindowClosed();
  void validateExpression();
  void validateVar();

  void modClicked();
  void clearClicked();
  void delClicked();
  void eqClicked();
  void plotClicked();
  void unarClicked();
  void numberButtonClicked();
  void functionButtonClicked();

 private:
  void allocateMemory(CalculatorController *controller);
  void initView();

  CalculatorController *controller_;
  Plot *plot;
  bool valid{false};
  bool valid_var{true};

  QFrame *button_frame;
  QGridLayout *button_grid, *main_grid;
  QPushButton *bsin, *bcos, *btan, *basin, *bacos, *batan, *bsqrt, *bmod, *blog,
      *bln, *bunar, *bscience, *bpi, *bpow, *bopenbr, *bclosebr, *bdiv, *bmul,
      *bminus, *bplus, *bvar, *bdot, *beq, *bclear, *bdel, *bzero, *bone, *btwo,
      *bthree, *bfour, *bfive, *bsix, *bseven, *beight, *bnine, *bplot;
  QLineEdit *expr, *var_value;
  QLabel *lvar;
};

#endif  // SRC_MODULES_INCLUDE_CALCULATOR_VIEW_H_
