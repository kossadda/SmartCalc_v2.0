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
#include <QWidget>

#include "modules/include/calculator_controller.h"
#include "modules/include/plot.h"

namespace Ui {
class CalculatorView;
}

class CalculatorView : public QWidget {
  Q_OBJECT

 public:
  explicit CalculatorView(QWidget *parent = nullptr);
  ~CalculatorView();

 private slots:
  void on_ButtonMod_clicked();
  void on_ButtonC_clicked();
  void on_ButtonDel_clicked();
  void on_ButtonPlot_clicked();
  void on_ButtonEq_clicked();

 private:
  CalculatorController controller_;
  Ui::CalculatorView *ui;
  Plot *plui;

  void numberButtonClicked();
  void functionButtonClicked();
  void plotWindowClosed();
};

#endif  // SRC_MODULES_INCLUDE_CALCULATOR_VIEW_H_
