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

#ifndef CALCULATOR_VIEW_H
#define CALCULATOR_VIEW_H

#include <QWidget>
#include <QDebug>
#include "plot.h"

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

  private:
  Ui::CalculatorView *ui;
  Plot *plui;

  void numberButtonClicked();
  void functionButtonClicked();
  void plotWindowClosed();
};

#endif  // CALCULATOR_VIEW_H
