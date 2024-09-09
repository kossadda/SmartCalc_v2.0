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

#include <QPropertyAnimation>
#include <QWidget>

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

 private:
  Ui::CalculatorView *ui;

  void numberButtonClicked();
  void functionButtonClicked();
};

#endif  // CALCULATOR_VIEW_H
