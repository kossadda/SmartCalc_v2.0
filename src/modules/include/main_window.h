/**
 * @file main_window.h
 * @author kossadda (https://github.com/kossadda)
 * @brief
 * @version 1.0
 * @date 2024-09-11
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef SRC_MODULES_INCLUDE_MAIN_WINDOW_H_
#define SRC_MODULES_INCLUDE_MAIN_WINDOW_H_

#include <QTabWidget>

#include "modules/include/calculator_view.h"
#include "modules/include/credit_view.h"
#include "modules/include/top_menu.h"

class MainWindow : public TopMenu {
  Q_OBJECT

 public:
  MainWindow();

 protected:
  void closeWindow() override { QApplication::quit(); }

 private:
  QTabWidget *tab_;
  CalculatorModel *calculator_model_;
  CalculatorController *calculator_controller_;
  CalculatorView *calculator_view_;
  CreditModel *credit_model_;
  CreditController *credit_controller_;
  CreditView *credit_view_;
  // DepositModel *deposit_model_;
  // DepositController *deposit_controller_;
  // DepositView *deposit_view_;
};

#endif  // SRC_MODULES_INCLUDE_MAIN_WINDOW_H_
