/**
 * @file main_window.cc
 * @author kossadda (https://github.com/kossadda)
 * @brief Implementation of the MainWindow class.
 * @version 1.0
 * @date 2024-09-23
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "include/view/main_window.h"

namespace s21 {

MainWindow::MainWindow() : BaseWindow() {
  initMVC();
  initView();
}

void MainWindow::initMVC() {
  calculator_model_ = new CalculatorModel;
  calculator_controller_ = new CalculatorController{calculator_model_};
  calculator_view_ = new CalculatorView{calculator_controller_};

  credit_model_ = new CreditModel;
  credit_controller_ = new CreditController{credit_model_};
  credit_view_ = new CreditView{credit_controller_};

  deposit_model_ = new DepositModel;
  deposit_controller_ = new DepositController{deposit_model_};
  deposit_view_ = new DepositView{deposit_controller_};
}

void MainWindow::initView() {
  setWindowIcon(QIcon{":main.png"});
  setWindowTitle(QString{"SmartCalculator"});
  image_label_->setPixmap(QPixmap{":main.png"});

  tab_ = new QTabWidget;

  tab_->setStyleSheet(QString{
      "QTabWidget { background-color: rgb(255, 255, 255); }"
      "QTabWidget::pane { border-top: 1px solid rgba(40, 100, 180, 0.7); }"
      "QTabWidget::tab-bar { left: 22px; }"
      "QTabBar::tab { background: rgb(40, 40, 40);"
      "color: rgb(255, 255, 255);"
      "border: 1px solid rgba(40, 100, 180, 0.7);"
      "border-top-left-radius: 10px;"
      "border-top-right-radius: 10px;"
      "min-width: 23ex;"
      "padding: 7px;"
      "font-size: 13px;"
      "font-weight: bold; }"
      "QTabBar::tab:selected { border: 1px solid rgba(40, 100, 180, 1.0);"
      "font-size: 14px; }"
      "QTabBar::tab:!selected { margin-top: 10px; }"});

  tab_->addTab(calculator_view_, QIcon{":calculator.png"}, QString{"Engineer"});
  tab_->addTab(credit_view_, QIcon{":credit.png"}, QString{"Credit"});
  tab_->addTab(deposit_view_, QIcon{":deposit.png"}, QString{"Deposit"});
  tab_->setCurrentWidget(calculator_view_);
  setlocale(LC_NUMERIC, "C");

  BaseWindow::main_layout_->addWidget(tab_);
}

void MainWindow::closeWindow() { QApplication::quit(); }

}  // namespace s21
