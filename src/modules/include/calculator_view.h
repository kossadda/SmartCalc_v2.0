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
  explicit CalculatorView(QWidget *parent = nullptr);

 private slots:
  // void on_ButtonMod_clicked();
  // void on_ButtonC_clicked();
  // void on_ButtonDel_clicked();
  // void on_ButtonPlot_clicked();
  // void on_ButtonEq_clicked();

 private:
  CalculatorController controller_;
  Plot *plot;
  bool valid{false};

  QFrame *button_frame;
  QGridLayout *button_grid, *main_grid;
  QPushButton *bsin, *bcos, *btan, *basin, *bacos, *batan, *bsqrt, *bmod, *blog,
      *bln, *bunar, *bscience, *bpi, *bpow, *bopenbr, *bclosebr, *bdiv, *bmul,
      *bminus, *bplus, *bvar, *bdot, *beq, *bclear, *bdel, *bzero, *bone, *btwo,
      *bthree, *bfour, *bfive, *bsix, *bseven, *beight, *bnine, *bplot;
  QLineEdit *text_expr, *var_value;
  QLabel *lvar;

  void numberButtonClicked();
  void functionButtonClicked();
  void plotWindowClosed();
  void validateExpression();
};

#endif  // SRC_MODULES_INCLUDE_CALCULATOR_VIEW_H_
