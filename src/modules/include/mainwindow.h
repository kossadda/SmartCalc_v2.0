/**
 * @file mainwindow.h
 * @author kossadda (https://github.com/kossadda)
 * @brief
 * @version 1.0
 * @date 2024-09-11
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef SRC_MODULES_INCLUDE_MAINWINDOW_H_
#define SRC_MODULES_INCLUDE_MAINWINDOW_H_

#include <QTabWidget>

#include "modules/include/calculator_view.h"
#include "modules/include/top_menu.h"

class MainWindow : public TopMenu {
  Q_OBJECT

 public:
  explicit MainWindow(QWidget *parent = nullptr)
      : TopMenu(parent),
        tab{new QTabWidget{}},
        calculator{new CalculatorView{}},
        credit{new QWidget{}},
        deposit{new QWidget{}} {
    setWindowIcon(QIcon{":calculator.png"});
    setWindowTitle(QString{"SmartCalculator"});

    tab->addTab(credit, QIcon{":credit.png"}, QString{"Credit"});
    tab->addTab(calculator, QIcon{":calculator.png"}, QString{"Engineer"});
    tab->addTab(deposit, QIcon{":deposit.png"}, QString{"Deposit"});

    tab->setCurrentWidget(calculator);

    tab->setStyleSheet(QString{
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

    TopMenu::main_layout->addWidget(tab);
  }

 protected:
  void closeWindow() override { QApplication::quit(); }

 private:
  QTabWidget *tab;
  CalculatorView *calculator;
  QWidget *credit, *deposit;
};

#endif  // SRC_MODULES_INCLUDE_MAINWINDOW_H_
